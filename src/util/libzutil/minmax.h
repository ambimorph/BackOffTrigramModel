/**
 * copyright 2002-2006 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_minmax_h
#define __INCL_minmax_h

#include "minmaximp.h" /* implementation stuff that you needn't see in order to use the library */

/**
 * How to use these macros:
 *
 * MAXi
 *
 * You can just use MAXi(), and it will do the right thing.  There is one detail 
 * about C that you ought to keep in mind, which is that if either of the two 
 * operands is of type unsigned long long, then the result will be of 
 * unsigned long long, which means that if you compare the result to a number of 
 * a signed type you'll get the wrong answer, e.g. the following will evaluate 
 * to false: MAXi(2, 1LLU) > -1
 * This is just something that you should be aware of as a C programmer -- it 
 * happens anytime a signed value is compared to an unsigned value and can't be 
 * fixed by the MAXi macro.
 * 
 * As a matter of fact, the MAXi macro casts the result to signed long long, 
 * unless the result is too big to fit into a signed long long.  That's why 
 * (MAXi(2, 1LU) > -1) is true, just as you would expect if you didn't know about 
 * C's integer promotion rules.  This might cause spurious warnings or other 
 * issues even though it never changes the actual value.  For example, if you 
 * are using MAXi as the argument to (s)printf, you ought to manually cast it to 
 * the right type.
 * 
 * MINi
 *
 * You can just use MINi(), and it will do the right thing *unless* both of the 
 * operands are unsigned long longs containing values larger than LLONG_MAX, in 
 * which case it will still do the right thing except that the result will be 
 * cast to type signed long long, the consequences of which are 
 * implementation-dependent.
 *
 * (On almost all actual C implementations, you can cast the result back to 
 * unsigned long long and you'll have the right answer, but this isn't 
 * guaranteed by the C standard.  Also, if you use the result without casting it 
 * to unsigned long long then you can get wrong behavior, for example the 
 * following will evaluate to true:
 * MINi(LLONG_MAX+1LLU, LLONG_MAX+2LLU) < 0)
 *
 * Anyway, if you are taking the min of two unsigned long longs and you want to 
 * be sure that you'll get the right answer on any standard-conforming 
 * C implementation, then use "MIN_LLU" instead of "MINi".  MIN_LLU casts the 
 * result to type unsigned long long, which means if the winning operand (the 
 * smallest one of the two) is negative, then it will be coerced into the 
 * non-negative number which is congruent to its original value mod 2^N, where 
 * N is the number of bits in an unsigned long long.
 *
 * So to be safe, use MINi, unless both of the arguments are of type 
 * unsigned long long, in which case you should use MIN_LLU.
 *
 * debug mode
 *
 * If you #define "ZMINMAXDEBUG" before #include'ing this header file then each 
 * of these macros will cause a floating point exception (a divide-by-zero 
 * error) rather than returning a potentially incorrect result.  That is the MINi 
 * macro will cause a floating point exception if both of the operands are 
 * unsigned long longs and both of their values are greater than LLONG_MAX, and 
 * the MIN_LLU macro will cause a floating point exception if the smallest of 
 * the two operands is a negative number.
 *
 * This is to help you locate the potentially incorrect MINi and change it from 
 * MINi to MIN_LLU (if both of the operands are unsigned long longs) or from 
 * MIN_LLU to MINi (if one of the operands might be negative).
 *
 * One drawback to using the ZMINMAXDEBUG versions is that a sufficiently clever 
 * compiler will emit warnings telling you that the code might cause a 
 * floating-point exception.
 */

#endif /* #ifndef __INCL_minmax_h */
