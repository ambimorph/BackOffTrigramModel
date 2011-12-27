/**
 * copyright 2002-2006 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_zutil_h
#define __INCL_zutil_h

#ifdef __cplusplus
extern "C" {
#endif

#include "bool.h"

extern int const zutil_vermaj; /* 1 */
extern int const zutil_vermin; /* 0 */
extern int const zutil_vermicro; /* 0 */
extern char const* const zutil_vernum; /* "1.0.0" */

/**
 * This is guaranteed by standard C to be at least large enough to store at 
 * least 8 bits.  It is allowed to be larger.
 */
typedef unsigned char zbyte;

/**
 * Decode two bytes into an unsigned short.  bs points to a buffer which must
 * have (at least) two elements; the first two elements of bs contain the
 * encoding of the unsigned short in big-endian format.
 */
unsigned short uint16_decode(const zbyte* bs);
unsigned short UINT16_DECODE(const zbyte* bs);

/**
 * Decode four bytes into an unsigned int.  bs points to a buffer which must 
 * have (at least) four elements; the first four elements of bs contain the 
 * encoding of the unsigned integer in big-endian format.
 */
unsigned long uint32_decode(const zbyte* bs);
unsigned long UINT32_DECODE(const zbyte* bs);

/**
 * Decode eight bytes into an unsigned int.  bs points to a buffer which must 
 * have (at least) eight elements; the first eight elements of bs contain the 
 * encoding of the unsigned integer in big-endian format.
 */
unsigned long long uint64_decode(const zbyte* bs);
unsigned long long UINT64_DECODE(const zbyte* bs);

/**
 * Encode an unsigned short into two zbytes in big-endian format.  Aborts
 * (via runtime_assert()) if the value is too large to encode into 16 bits
 * (that is, if it is >= 2^16).
 *
 * @param lu: the value to encode
 * @param bs: pointer to the first byte of an array of at least two zbytes
 */
void uint16_encode(unsigned short hu, zbyte* bs);

/**
 * Encode an unsigned int into four zbytes in big-endian format.  Aborts (via 
 * runtime_assert()) if the value is too large to encode into 32 bits (that is, 
 * if it is >= 2^32).
 *
 * @param lu: the value to encode
 * @param bs: pointer to the first byte of an array of at least four zbytes
 */
void uint32_encode(unsigned long lu, zbyte* bs);

/**
 * Encode an unsigned int into eight zbytes in big-endian format.  Aborts (via 
 * runtime_assert()) if the value is too large to encode into 64 bits (that is, 
 * if it is >= 2^64).
 *
 * @param lu: the value to encode
 * @param bs: pointer to the first byte of an array of at least eight zbytes
 */
void uint64_encode(unsigned long long llu, zbyte* bs);

/*
Returns ceil(x/y): the smallest integer which is greater than or equal to x/y.

divceil(x, y) is better than (x+(y-1))/y because the latter can overflow in 
the addition.  Also divceil() is usually faster.

Unfortunately the macro version of divceil() suffers from "the macro 
problem" -- if its argument expressions have side effects, the side effects 
happen twice.
*/
unsigned int divceil(unsigned int n, unsigned int d);
unsigned long ldivceil(unsigned long n, unsigned long d);

unsigned int DIVCEIL(unsigned int n, unsigned int d);
unsigned long LDIVCEIL(unsigned long n, unsigned long d);

/*
Returns the smallest integer which is a multiple of k and which is at least m.

Exits with an error (via runtime_assert()) if the result overflows the return 
type.
*/
unsigned int nextmult(unsigned int k, unsigned int m);
unsigned long lnextmult(unsigned long k, unsigned long m);

unsigned int NEXTMULT(unsigned int k, unsigned int m);
unsigned long LNEXTMULT(unsigned long k, unsigned long m);

/*
Returns true iff the value (x+y) cannot be stored in a char.
 */
bool add_would_overflow_char(char x, char y);
bool ADD_WOULD_OVERFLOW_CHAR(char x, char y);

/*
Returns true iff the value (x+y) cannot be stored in an unsigned char.
 */
bool add_would_overflow_uchar(unsigned char x, unsigned char y);
bool ADD_WOULD_OVERFLOW_UCHAR(unsigned char x, unsigned char y);

/*
Returns true iff the value (x+y) cannot be stored in a signed char.
 */
bool add_would_overflow_schar(signed char x, signed char y);
bool ADD_WOULD_OVERFLOW_SCHAR(signed char x, signed char y);

/*
Returns true iff the value (x+y) cannot be stored in a short.
 */
bool add_would_overflow_shrt(short x, short y);
bool ADD_WOULD_OVERFLOW_SHRT(short x, short y);

/*
Returns true iff the value (x+y) cannot be stored in an unsigned short.
 */
bool add_would_overflow_ushrt(unsigned short x, unsigned short y);
bool ADD_WOULD_OVERFLOW_USHRT(unsigned short x, unsigned short y);

/*
Returns true iff the value (x+y) cannot be stored in an int.
 */
bool add_would_overflow_int(int x, int y);
bool ADD_WOULD_OVERFLOW_INT(int x, int y);

/*
Returns true iff the value (x+y) cannot be stored in an unsigned int.
 */
bool add_would_overflow_uint(unsigned int x, unsigned int y);
bool ADD_WOULD_OVERFLOW_UINT(unsigned int x, unsigned int y);

/*
Returns true iff the value (x+y) cannot be stored in a long.
 */
bool add_would_overflow_long(long x, long y);
bool ADD_WOULD_OVERFLOW_LONG(long x, long y);

/*
Returns true iff the value (x+y) cannot be stored in an unsigned long.
 */
bool add_would_overflow_ulong(unsigned long x, unsigned long y);
bool ADD_WOULD_OVERFLOW_ULONG(unsigned long x, unsigned long y);

/*
Returns true iff the value (x+y) cannot be stored in a long long.
 */
bool add_would_overflow_llong(long long x, long long y);
bool ADD_WOULD_OVERFLOW_LLONG(long long x, long long y);

/*
Returns true iff the value (x+y) cannot be stored in an unsigned long long.
 */
bool add_would_overflow_ullong(unsigned long long x, unsigned long long y);
bool ADD_WOULD_OVERFLOW_ULLONG(unsigned long long x, unsigned long long y);

/*
Macro which evaluates true if the expression (x+y) will result in arithmetic 
overflow.  It also evaluates true if one of the operands is negative and the 
other is of a type that is too large to fit into a long long (because the 
result of the addition is not guaranteed in the C89 standard).

Treat it as though it were defined something like this:

bool ADD_WOULD_OVERFLOW({anyinttype} x, {anyinttype} y);
*/

#include "zutilimp.h" /* implementation stuff that you needn't see in order to use the library */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __INCL_zutil_h */

#include "exhaust.h"
#include "minmax.h"
#include "morelimits.h"
#include <stddef.h>
