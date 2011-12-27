/**
 * copyright 2002-2006 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_zutilimp_h
#define __INCL_zutilimp_h

#include "zutil.h"

#include "morelimits.h"
#include "moreassert.h"

#define Z_ZERO_VAL(x) ((x)-(x))
#define Z_UNIT_VAL(x) (Z_ZERO_VAL(x) + 1)
#define Z_TYPE_ZERO_VAL(x) ((x)0)
#define Z_TYPE_UNIT_VAL(x) (Z_TYPE_ZERO_VAL(x) + 1)

#define TYPE_PROMOTES_TO_SIGNED_TYPE(x) ((Z_TYPE_ZERO_VAL(x) - Z_TYPE_UNIT_VAL(x)) < Z_TYPE_ZERO_VAL(x))
#define TYPE_FITS_INTO_INT(x) (TYPE_PROMOTES_TO_SIGNED_TYPE(x) && (sizeof(x) <= sizeof(signed int)))
#define TYPE_FITS_INTO_LONG(x) ((TYPE_PROMOTES_TO_SIGNED_TYPE(x) && (sizeof(x) <= sizeof(signed long))) || (sizeof(x) < sizeof(signed long)))
#define TYPE_FITS_INTO_LLONG(x) ((TYPE_PROMOTES_TO_SIGNED_TYPE(x) && (sizeof(x) <= sizeof(signed long long))) || (sizeof(x) < sizeof(signed long long)))

/* The following macro tests whether all integers of the type of the operand will promote into a signed type, rather than whether this particular operand can fit into a signed int when coerced.   Therefore !OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)2) even though OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)2). */
#define OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(x) ((Z_ZERO_VAL(x) - Z_UNIT_VAL(x)) < Z_ZERO_VAL(x))
/* The following macros test whether all integers of the type of the operand can fit into the specified type, rather than whether this particular operand can fit into the specified type when coerced.   Therefore !OPERAND_TYPE_FITS_INTO_INT((unsigned int)2) even though OPERAND_TYPE_FITS_INTO_INT((signed int)2). */
#define OPERAND_TYPE_FITS_INTO_INT(x) (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(x) && (sizeof(x) <= sizeof(signed int)))
#define OPERAND_TYPE_FITS_INTO_LONG(x) (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(x) && (sizeof(x) <= sizeof(signed long)))
#define OPERAND_TYPE_FITS_INTO_LLONG(x) (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(x) && (sizeof(x) <= sizeof(signed long long)))

/* We define OPERAND_EXCEEDS_LLONG_MAX in this funny way in order to trick gcc into not giving warnings about comparisons being useless due to the limited range of datatypes. */
#define OPERAND_EXCEEDS_LLONG_MAX(x) ((ULLONG_MAX - (x)) < (ULLONG_MAX - LLONG_MAX))

#define ADD_WOULD_OVERFLOW_Styp(x, y, typ) ((((x) > 0) && ((y) > 0) && ((Z_MAX_typ(typ) - (x)) < (y))) || (((x) < 0) && ((y) < 0) && ((Z_MIN_typ(typ) - (x)) > (y))))
#define ADD_WOULD_OVERFLOW_Utyp(x, y, typ) (((typ)((x)+(y))) < (x))

#define MACRO_ADD_WOULD_OVERFLOW_CHAR(x, y) ADD_WOULD_OVERFLOW_Styp(x, y, char)
#define MACRO_ADD_WOULD_OVERFLOW_SHRT(x, y) ADD_WOULD_OVERFLOW_Styp(x, y, short)
#define MACRO_ADD_WOULD_OVERFLOW_INT(x, y) ADD_WOULD_OVERFLOW_Styp(x, y, int)
#define MACRO_ADD_WOULD_OVERFLOW_LONG(x, y) ADD_WOULD_OVERFLOW_Styp(x, y, long)
#define MACRO_ADD_WOULD_OVERFLOW_LLONG(x, y) ADD_WOULD_OVERFLOW_Styp(x, y, long long)

#define MACRO_ADD_WOULD_OVERFLOW_UCHAR(x, y) ADD_WOULD_OVERFLOW_Utyp(x, y, unsigned char)
#define MACRO_ADD_WOULD_OVERFLOW_USHRT(x, y) ADD_WOULD_OVERFLOW_Utyp(x, y, unsigned short)
#define MACRO_ADD_WOULD_OVERFLOW_UINT(x, y) ADD_WOULD_OVERFLOW_Utyp(x, y, unsigned int)
#define MACRO_ADD_WOULD_OVERFLOW_ULONG(x, y) ADD_WOULD_OVERFLOW_Utyp(x, y, unsigned long)
#define MACRO_ADD_WOULD_OVERFLOW_ULLONG(x, y) ADD_WOULD_OVERFLOW_Utyp(x, y, unsigned long long)

#define MACRO_ADD_WOULD_OVERFLOW_SCHAR(x, y) ADD_WOULD_OVERFLOW_Styp(x, y, signed char)

/* Note the final true in this expression.  This case occurs only when the 
 * type of one of the operands is too big a type to fit into a long long and 
 * the other operand is negative.  C will convert the signed operand to an 
 * unsigned type by sign-extension.  This isn't exactly the same as an integer 
 * overflow, but it is very likely something that the programmer wishes to avoid.
 */
#define ADD_WOULD_OVERFLOW(x, y) ( \
 (OPERAND_TYPE_FITS_INTO_LLONG(x) && OPERAND_TYPE_FITS_INTO_LLONG(y)) ? \
  ((long long)(x) + (long long)(y)) != (x)+(y) : \
   (((x) >= 0) && ((y) >= 0)) ? \
    ((x) + (y) < (x)) : \
    (true))

#ifdef NDEBUG
#define ADD_WOULD_OVERFLOW_CHAR(x, y) MACRO_ADD_WOULD_OVERFLOW_CHAR(x, y)
#define ADD_WOULD_OVERFLOW_SHRT(x, y) MACRO_ADD_WOULD_OVERFLOW_SHRT(x, y)
#define ADD_WOULD_OVERFLOW_INT(x, y) MACRO_ADD_WOULD_OVERFLOW_INT(x, y)
#define ADD_WOULD_OVERFLOW_LONG(x, y) MACRO_ADD_WOULD_OVERFLOW_LONG(x, y)
#define ADD_WOULD_OVERFLOW_LLONG(x, y) MACRO_ADD_WOULD_OVERFLOW_LLONG(x, y) 

#define ADD_WOULD_OVERFLOW_UCHAR(x, y) MACRO_ADD_WOULD_OVERFLOW_UCHAR(x, y)
#define ADD_WOULD_OVERFLOW_USHRT(x, y) MACRO_ADD_WOULD_OVERFLOW_USHRT(x, y)
#define ADD_WOULD_OVERFLOW_UINT(x, y) MACRO_ADD_WOULD_OVERFLOW_UINT(x, y)
#define ADD_WOULD_OVERFLOW_ULONG(x, y) MACRO_ADD_WOULD_OVERFLOW_ULONG(x, y)
#define ADD_WOULD_OVERFLOW_ULLONG(x, y) MACRO_ADD_WOULD_OVERFLOW_ULLONG(x, y) 

#define ADD_WOULD_OVERFLOW_SCHAR(x, y) MACRO_ADD_WOULD_OVERFLOW_SCHAR(x, y)

#endif /* #ifdef NDEBUG */

#define MACRO_NEXTMULT(k, m) ( \
 ((((m)%(k))==0) ? (m) : \
  (runtime_assert(!ADD_WOULD_OVERFLOW((k)-((m)%(k)), (m)), "Cannot compute nextmult of these numbers due to integer overflow.")) ? \
   ((m)+((k)-((m)%(k)))) : \
   (0) \
  ) \
)

#ifdef NDEBUG
#define DIVCEIL(n, d) ((n)/(d)+((n)%(d)!=0))
#define LDIVCEIL(n, d) ((unsigned long)((n)/(d)+((n)%(d)!=0)))
#define UINT16_DECODE(bs) (((unsigned long)((bs)[1])) | ((unsigned long)((bs)[0])) << 8)
#define UINT32_DECODE(bs) (((unsigned long)((bs)[3])) | ((unsigned long)((bs)[2])) << 8 | ((unsigned long)((bs)[1])) << 16 | ((unsigned long)((bs)[0])) << 24)
#define UINT64_DECODE(bs) (((unsigned long long)(bs[7])) | ((unsigned long long)(bs[6])) << 8 | ((unsigned long long)(bs[5])) << 16 | ((unsigned long long)(bs[4])) << 24 | ((unsigned long long)(bs[3])) << 32 | ((unsigned long long)(bs[2])) << 40 | ((unsigned long long)(bs[1])) << 48 | ((unsigned long long)(bs[0])) << 56)
#define NEXTMULT(k, m) MACRO_NEXTMULT(k, m)
#define LNEXTMULT(k, m) MACRO_NEXTMULT(k, m)

#endif /* #ifdef NDEBUG */

#endif /* #ifndef __INCL_zutilimp_h */
