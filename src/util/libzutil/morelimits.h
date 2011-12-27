/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_morelimits_h
#define __INCL_morelimits_h

#include "morelimitsimp.h" /* implementation stuff that you needn't see in order to use the library */

#include <stddef.h>
#include <limits.h>

/*
 * The following are not defined in the standard C library's "limits.h", but are sometimes defined in other headers.
 */
#define Z_SIZE_T_MAX Z_MAX_typ(size_t)
#define Z_SIZE_T_MIN Z_MIN_typ(size_t)

#ifndef SIZE_T_MAX
#define SIZE_T_MAX Z_SIZE_T_MAX
#endif
#ifndef SIZE_T_MIN
#define SIZE_T_MIN Z_SIZE_T_MIN
#endif

#ifndef SIZE_MAX
#define SIZE_MAX Z_SIZE_T_MAX
#endif
#ifndef SIZE_MIN
#define SIZE_MIN Z_SIZE_T_MIN
#endif

#define Z_TIME_T_MAX Z_MAX_typ(time_t)
#define Z_TIME_T_MIN Z_MIN_typ(time_t)

#ifndef TIME_T_MAX 
#define TIME_T_MAX Z_TIME_T_MAX
#endif
#ifndef TIME_T_MIN
#define TIME_T_MIN Z_TIME_T_MIN
#endif

/**
 * The following is useful only if you are storing numbers in storage space of
 * type void*, and you want to be sure your numbers aren't too big.  ANSI C does
 * not guarantee that you can do this.
 */
#define Z_MAX_VOIDP Z_MAX_UNSIGNED_BITS(sizeof(void*) * CHAR_BIT)

/*
 * The C standard does not guarantee integers of an exact width, so if you rely
 * on an integer to be of a specific width your code may not port to all C 
 * platforms.  The following are intended only for reading and writing integers
 * of fixed width from streams of data.
 */
#define Z_UINT8_MAX ((unsigned short)Z_MAX_UNSIGNED_BITS(8))
#define Z_UINT16_MAX ((unsigned short)Z_MAX_UNSIGNED_BITS(16))
#define Z_UINT32_MAX ((unsigned long)Z_MAX_UNSIGNED_BITS(32))
#define Z_UINT64_MAX ((unsigned long long)Z_MAX_UNSIGNED_BITS(64))

/*
 * The following are not defined in the standard C library's "limits.h", 
 * presumably because you could just write "0" instead.
 */
#define ULONG_MIN Z_MIN_typ(unsigned long)
#define UINT_MIN Z_MIN_typ(unsigned int)
#define USHRT_MIN Z_MIN_typ(unsigned short)
#define UCHAR_MIN Z_MIN_typ(unsigned char)
#define ULLONG_MIN Z_MIN_typ(unsigned long long)

/*
 * All of the following should be defined in the standard C library's "limits.h" 
 * header.  They are included here because some limits.h's lack some of them 
 * (the long long ones), and in order to check that my Z_MAX_typ and Z_MIN_typ macros 
 * and your system's <limits.h> agree!  (test.c tests this.)
 */
#define Z_ULLONG_MAX Z_MAX_typ(unsigned long long)
#define Z_ULONG_MAX Z_MAX_typ(unsigned long)
#define Z_UINT_MAX Z_MAX_typ(unsigned int)
#define Z_USHRT_MAX Z_MAX_typ(unsigned short)
#define Z_UCHAR_MAX Z_MAX_typ(unsigned char)
#define Z_BYTE_MAX Z_MAX_typ(unsigned char)

#define Z_LLONG_MAX Z_MAX_typ(long long)
#define Z_LONG_MAX Z_MAX_typ(long)
#define Z_INT_MAX Z_MAX_typ(int)
#define Z_SHRT_MAX Z_MAX_typ(short)
#define Z_CHAR_MAX Z_MAX_typ(char)

#define Z_LLONG_MIN Z_MIN_typ(long long)
#define Z_LONG_MIN Z_MIN_typ(long)
#define Z_INT_MIN Z_MIN_typ(int)
#define Z_SHRT_MIN Z_MIN_typ(short)
#define Z_CHAR_MIN Z_MIN_typ(char)

#define Z_SCHAR_MAX Z_MAX_typ(signed char)
#define Z_SCHAR_MIN Z_MIN_typ(signed char)

#ifndef ULLONG_MAX
#define ULLONG_MAX Z_ULLONG_MAX
#endif

#ifndef ULONG_MAX
#define ULONG_MAX Z_ULONG_MAX
#endif

#ifndef UINT_MAX
#define UINT_MAX Z_UINT_MAX
#endif

#ifndef USHRT_MAX
#define USHRT_MAX Z_USHRT_MAX
#endif

#ifndef USHRT_MAX
#define USHRT_MAX Z_USHRT_MAX
#endif

#ifndef UCHAR_MAX
#define UCHAR_MAX Z_UCHAR_MAX
#endif

#ifndef LLONG_MAX
#define LLONG_MAX Z_LLONG_MAX
#endif

#ifndef LONG_MAX
#define LONG_MAX Z_LONG_MAX
#endif

#ifndef INT_MAX
#define INT_MAX Z_INT_MAX
#endif

#ifndef SHRT_MAX
#define SHRT_MAX Z_SHRT_MAX
#endif

#ifndef CHAR_MAX
#define CHAR_MAX Z_CHAR_MAX
#endif

#ifndef LLONG_MIN
#define LLONG_MIN Z_LLONG_MIN
#endif

#ifndef LONG_MIN
#define LONG_MIN Z_LONG_MIN
#endif

#ifndef INT_MIN
#define INT_MIN Z_INT_MIN
#endif

#ifndef SHRT_MIN
#define SHRT_MIN Z_SHRT_MIN
#endif

#ifndef CHAR_MIN
#define CHAR_MIN Z_CHAR_MIN
#endif

#ifndef SCHAR_MAX
#define SCHAR_MAX Z_SCHAR_MAX
#endif

#ifndef SCHAR_MIN
#define SCHAR_MIN Z_SCHAR_MIN
#endif

#endif /* #ifndef __INCL_morelimits_h */
