/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this work to deal in this work without restriction (including the rights
 * to use, modify, distribute, sublicense, and/or sell copies).
 *
 *
 * About this library:
 *
 * This library defines a simple struct with a length and a pointer to byte.  
 * You can use it in place of, or alongside, traditional C null-terminated 
 * char*'s and the <string.h> functions.  The advantages of "lengthed" strings 
 * over null-terminated strings are well known: they can store binary data, they 
 * can sometimes be faster, and they can often be safer with regard to buffer 
 * overflow errors.  For example, see zcat(), which is safer than <string.h>'s 
 * strcat() or strncat(), and even than alternatives such as OpenBSD's 
 * strlcat().
 *
 * For a very useful survey of the security issues and various approaches, 
 * please see David Wheeler's article, "Secure programmer: Countering buffer 
 * overflows":
 * http://www-106.ibm.com/developerworks/linux/library/l-sp4.html
 *
 *
 * About macros:
 *
 * Many of these functions have macro versions, which are named the same name as 
 * the function but in ALL UPPERCASE letters.  The macro version may be faster 
 * (unless your C compiler was clever enough to efficiently inline the function 
 * version), but it suffers from "the macro problem" that the argument 
 * expressions get evaluated more than once, which means that if any of the 
 * arguments have side-effects those side-effects will occur more than once.  
 * For example, suppose that `zs' is an array of zstrs.  Then if you write:
 * int i = 0;
 * int eq = zeq(zs[i++], zs[i++])
 * it will compare the first and second elements of the array, but if you write:
 * int i = 0;
 * int eq = Z_EQ(zs[i++], zs[i++])
 * then the preprocessor will expand it to:
 * int i = 0;
 * int eq = ((zs[i++].len==zs[i++].len)&&(!memcmp(zs[i++].buf, zs[i++].buf, zs[i++].len)))
 * which isn't right at all!
 *
 * The macro versions also omit the assertion checking that the function 
 * versions have.  In general, you probably ought to just use the function 
 * version until you have identified a particular performance hotspot that could 
 * benefit from saving another couple of CPU cycles, and then use the macro 
 * version there, being careful to avoid side-effects in the argument 
 * expressions of the macro.
 *
 * (By the way, if the NDEBUG flag is unset, then libzstr will use the 
 * function versions even if you specified the all-uppercase name of the macro 
 * version.)
 *
 *
 * About memory exhaustion:
 *
 * What should your program do if it tries to allocate more memory and is told 
 * by the operating system that there is no more memory available?  Unless you 
 * have some unusual requirements and an exceptionally clever recovery scheme, 
 * the right thing to do is probably to print an error message and exit.  If you 
 * define the flag Z_EXHAUST_EXIT before #including the "zutil.h" header file, 
 * then libzstr will do just that whenever it gets memory allocation failure.  
 * If you do not define that flag, then libzstr will return a "null" value of 
 * some sort when it gets memory allocation failure.  The specifics of that 
 * behavior are given in the documentation of each function that can incur 
 * memory allocation failure.
 *
 * (Note: see the TODO file which suggests a nicer way to handle memory
 * exhaustion.)
 */
#ifndef _INCL_zstr_h
#define _INCL_zstr_h

static int const zstr_vermaj = 0;
static int const zstr_vermin = 9;
static int const zstr_vermicro = 8;
static char const* const zstr_vernum = "0.9.8";

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "zutil.h" /* http://zooko.com/repos/libzutil */

/**
 * A zstr is simply an unsigned int length and a pointer to a buffer of 
 * unsigned chars.
 */
typedef struct {
	size_t len; /* the length of the string (not counting the null-terminating character) */
	zbyte* buf; /* pointer to the first byte */
} zstr;

/**
 * A czstr is simply an unsigned int length and a pointer to a buffer of 
 * const unsigned chars.
 */
typedef struct {
	size_t len; /* the length of the string (not counting the null-terminating character) */
	const zbyte* buf; /* pointer to the first byte */
} czstr;

   /** commonly used functions */

/**
 * Returns a czstr pointing to the first occurrence of z2 in z1, or the NULL
 * czstr if none.  If z2.len == 0, then return z1.
 */
czstr
zstrstr(czstr z1, czstr z2);

/**
 * Add z2 onto the end of z1, reallocating z1 to be big enough.
 *
 * @param z1 this will be realloc'ed which means you cannot use it after 
 *     calling zcat()!  Use the return value instead.
 * @param z2 the string to be appended onto the end of z1
 *
 * @return the new z1
 *
 * On  malloc failure (if not Z_EXHAUST_EXIT) then it will return a zstr with 
 * its .buf member set to NULL and its .len member set to 0.  In that case z1 
 * is completely unchanged (and can safely be used as if this function had not 
 * been called).
 */
zstr
zcat(zstr z1, czstr z2);

/**
 * Copy z2 and return copy in newly allocated zstr.
 * It is okay if z1 is missing its null-terminating character.  Whether z1 has
 * a null-terminating character or not, the newly returned zstr will have one.
 *
 * @param z1
 *
 * @return the new zstr
 *
 * On  malloc failure (if not Z_EXHAUST_EXIT) then it will return a zstr with 
 * its .buf member set to NULL and its .len member set to 0.
 */
zstr
zdup(czstr z1);

/**
 * Copy z1's data and length into z2.  Note that this will corrupt
 * your memory if you haven't already ensured that the amount of
 * memory allocated in z2 is greater than then len of z1 plus one byte
 * for the null-terminating char.
 */
void
zcopy(czstr z1, zstr z2);

/**
 * @return the length of the zstr, in bytes, not counting the null terminating 
 *     character.
 *
 * Or you can just write "z.len".
 */
size_t
zstrlen(czstr z);

/**
 * @return 1 if the strings are identical, else 0
 */
int
zeq(czstr z1, czstr z2);
int
ZEQ(czstr z1, czstr z2);

/**
 * @return <0 if z1<z2, 0 if z1==z2, or >0 if z1>z2 (same as strcmp())
 */
int
zcmp(czstr z1, czstr z2);

/**
 * @return pointer to the first occurence of b in z or NULL if none
 */
const zbyte*
zchr(czstr z, zbyte b);
const zbyte*
ZCHR(czstr z, zbyte b);

/**
 * @return pointer to the n´th occurence of b in z or NULL if there are not 
 *     n of them
 */
const zbyte*
zchrn(czstr z, zbyte b, unsigned n);

/**
 * The human-readable representation is: if a byte is a printable ASCII character other than `\', 
 * then just show it.  If it is a '\', then show double backslash: '\\'.  Else 
 * the byte is not a printable ASCII character, so show its value in lowercase 
 * hexadecimal notation with a preceding backslash, e.g. `\xFF'.
 * (This is like the Python human-readable representation.)
 *
 * @return a newly allocated zstr containing a human-readable representation 
 *     of z.
 */
zstr
repr(czstr z);

/**
 * @return a zstr pointing to cs.
 *
 * @precondition cs must not be NULL.
 */
zstr
cs_as_z(char* cs);
zstr
CS_AS_Z(char* cs);

/**
 * (You should use cs_as_cz() instead of cs_as_z() if the argument is a string 
 * literal.)
 *
 * @return a czstr pointing to cs.
 *
 * @precondition cs must not be NULL.
 */
czstr
cs_as_cz(const char* cs);
czstr
CS_AS_CZ(const char* cs);

/**
 * @return a cs pointing to a czstr's buffer.  (It could be NULL.)
 */
const char*
cz_as_cs(czstr cz);
const char*
CZ_AS_CS(czstr cz);

/**
 * @return a czstr of z (shallow copy).
 */
czstr
cz(zstr z);

/**
 * Allocates space, copies the contents of cs and returns a zstr pointing to 
 * the result.
 *
 * On  malloc failure (if not Z_EXHAUST_EXIT) then it will return a zstr with 
 * its .buf member set to NULL and its .len member set to 0.
 *
 * @precondition cs must not be NULL.
 */
zstr 
new_z_from_cs(const char* cs);

/**
 * Allocates space.
 *
 * On  malloc failure (if not Z_EXHAUST_EXIT) then it will return a zstr with 
 * its .buf member set to NULL and its .len member set to 0.
 */
zstr 
new_z(size_t len);

/**
 * Allocates space, copies the first len bytes of cs and returns a zstr 
 * pointing to the result.
 *
 * On  malloc failure (if not Z_EXHAUST_EXIT) then it will return a zstr with 
 * its .buf member set to NULL and its .len member set to 0.
 *
 * @precondition cs must not be NULL.
 * @precondition len must not be 0.
 */
zstr 
new_z_from_cs_and_len(const char* cs, size_t len);

/**
 * Free the memory used by the zstr.
 *
 * Alternately you could write free(z.buf).
 *
 * @precondition z.buf must not be NULL.: z.buf != NULL
 *
 * (This precondition is here only to help you find memory mismanagement in 
 * your code.)
 */
void
free_z(zstr z);

/**
 * Read all remaining data from a stream (until EOF) into a zstr.  This does 
 * nothing with the fp argument except call fread(), feof(), and ferror() on it, 
 * therefore it reads from whereever fp is currently set to the end of fp.  It 
 * does not fclose() fp after it is done.
 *
 * This invokes realloc() multiple times as needed along the way.
 *
 * @precondition fp must not be NULL.
 */
zstr z_slurp_stream(FILE* fp);

/**
 * Read 4 byte length from a stream (until EOF) and store it in the len field of
 * a newly-allocated zstr, then read len bytes into the buf field.  This does
 * nothing with the fp argument except call fread(), and ferror() on it,
 * therefore it reads from whereever fp is currently set to the end of fp.  It
 * does not fclose() fp after it is done.
 *
 * @precondition fp must not be NULL.
 */
zstr z_decode(FILE* fp);

/**
 * Takes a czstr and an open stream, encodes the len in big-endian format, writes
 * that and buf to the stream.
 */
void z_encode(czstr cz, FILE* fp);

/**
 * Write the contents of cz to a stream.  This just calls 
 * fwrite(cz.buf, sizeof(zbyte), cz.len, fp).
 *
 * @precondition fp must not be NULL.
 */
void cz_to_stream(czstr cz, FILE* fp);

/**
 * A simple internal consistency check.  First, it verifies that cz.len is 0 
 * only if cz.buf is NULL or if cz.buf contains a zero-length string (that is a 
 * buffer of size 1 containing the null-terminating character).  Second, it 
 * verifies that strlen(cz.buf) is always <= cz.len (which is true because 
 * we always append a null-terminating char).  If either of these aren't true 
 * then it raises an error with runtime_assert().  Else, it returns 1.
 */
int cz_check(czstr cz);

/*** macro definitions ***/

typedef union { zstr z; czstr c; } z_union_zstr_czstr;

#ifdef NDEBUG
#define zstrlen(z) ((z).len)
#define Z_EQ(z1, z2) (((z1).len==(z2).len)&&(!memcmp((z1).buf, (z2).buf, (z1).len)))
#define CS_AS_Z(cs) ((zstr){ strlen(cs), cs };)
#define CS_AS_CZ(cs) ((czstr){ strlen((cs)), (zbyte*)(cs) })
#define free_z(z) (free((void*)(z).buf))
#define cz_as_cs(cz) ((const char*)(cz.buf))
#define CZ_AS_CS(cz) ((const char*)(cz.buf))
/* Please avert your gaze.  We are now going to trick the compiler into converting a zstr directly into a czstr by dint of casting into a union and then taking its czstr element. */
#define cz(z) ((z_union_zstr_czstr){ z }).c
#define zchr(cz, b) memchr((cz).buf, b, (cz).len)
#define ZCHR(cz, b) memchr((cz).buf, b, (cz).len)

#endif /* #ifdef NDEBUG */

#endif /* #ifndef _INCL_zstr_h */
