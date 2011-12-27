/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_minmaximp_h
#define __INCL_minmaximp_h

#include "morelimits.h"
#include "zutilimp.h"

/**
 * Min/max macros that are fast but unsafe.  If one of the arguments is negative 
 * and the other is of a type that doesn't promote to a signed type, you'll get 
 * the wrong answer.  
 */
#define _MIN_UNSAFE(x, y) ((x) < (y)?(x):(y))
#define _MAX_UNSAFE(x, y) ((x) > (y)?(x):(y))

/**
 * This macro just does what you expect.  It evaluates to the largest of the 
 * two operands, and the type of the result is a reasonable type for storing 
 * that result, for example it is a signed int if both the operands were 
 * signed ints, it is an unsigned int if either operand was an unsigned int, 
 * it is a double if either of the operands were a double, etc.
 *
 * You can even use _MAX_SAFE on pairs of pointers and it will do the correct 
 * thing for pointer comparison in C.  (Note: you may be surprised if you don't 
 * know what the correct thing for pointer comparison in C *is*, exactly.  It 
 * isn't a simple rule of "compare memory addresses numerically".)
 */
/* _MAX_SAFE is just for pedantic and verification purposes -- we use _FASTER_MAX_SAFE in practice. */
#define _MAX_SAFE(x, y) (((x) >= 0&&(y) < 0)?(x):(((y) >= 0&&(x) < 0)?(y):(((x) > (y))?(x):(y))))

/**
 * This handy-dandy _FASTER_MAX_SAFE macro is almost as fast as _MAX_UNSAFE 
 * while being as safe as _MAX_SAFE.  It can be exactly as fast as _MAX_SAFE in 
 * the case that both of the operands are of a type that promotes to a signed 
 * type or both of the operands are of a type that promotes to an unsigned type, 
 * since the compiler can determine this at compile time.  It can also be faster 
 * than _MAX_SAFE in some other cases.
 */
#define _PROMOTE_NONLL_TO_LLS(x) \
    ((sizeof(x) < sizeof(long long)) ? \
        ((long long)(x)) : \
        (x))

#define _MAX_UNSAFE_LLS(x, y) \
    ((((long long)(x)) > ((long long)(y))) ? \
        _PROMOTE_NONLL_TO_LLS(x) : \
        _PROMOTE_NONLL_TO_LLS(y))

#define _MAX_UNSAFE_LLU(x, y) \
    ((((unsigned long long)(x)) > ((unsigned long long)(y))) ? \
        _PROMOTE_NONLL_TO_LLS(x) : \
        _PROMOTE_NONLL_TO_LLS(y))

#define _FASTER_MAX_SAFE(x, y) \
    (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(x) ? \
        (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(y) ? \
            _MAX_UNSAFE_LLS(x, y) : \
            (((x) < 0) ? \
                _PROMOTE_NONLL_TO_LLS(y) : \
                _MAX_UNSAFE_LLU(x, y))) : \
        (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(y) ? \
            (((y) < 0) ? \
                _PROMOTE_NONLL_TO_LLS(x) : \
                _MAX_UNSAFE_LLU(x, y)) : \
            _MAX_UNSAFE_LLU(x, y)))

#define _RAISE_EXCEPTION ((long long)(1/0)) /* If you are wondering why you just got a divide-by-zero exception, it is because this code was compiled in debug mode (the ZMINMAXDEBUG flag was set) and there is a MINi macro being used where it cannot give the right answer, either because the answer is negative and the type of the expression is unsigned, or because the answer is greater than LLONG_MAX and the type of the expression is long long.  Please see minmax.h for information on how to use these MINi macros safely. */

/**
 * The MIN_LLS macros always correctly choose the smallest one of the two 
 * operands, but the result is cast to type long long.  Therefore if the 
 * winning operand (the smallest operand) is too large to fit into a signed long 
 * long then the result is implementation-dependent.  I suspect that on most 
 * platforms you can cast the result back to unsigned long long and you'll have 
 * the right answer, but this isn't guaranteed by the C standard.  Also, if you 
 * use the result without casting it to unsigned long long then you can get 
 * wrong behavior, for example the following will evaluate to true:
 * MIN_LLS(LLONG_MAX+1LLU, LLONG_MAX+2LLU) < 0
 */
/* _MIN_LLS_FLEX is just for pedantic and verification purposes -- we use _FASTER_MIN_LLS_FLEX in practice. */
#define _MIN_LLS_FLEX(x, y) (((x) < 0&&(y) >= 0)?((long long)(x)):(((y) < 0&&(x) >= 0)?((long long)(y)):(((x) < (y))?((long long)(x)):((long long)(y)))))
/* _MIN_LLS_CHECK is just for pedantic and verification purposes -- we use _FASTER_MIN_LLS_CHECK in practice. */
#define _MIN_LLS_UNSAFE(x, y) \
    ((((long long)(x)) < ((long long)(y))) ? \
        ((long long)(x)) : \
        ((long long)(y)))
#define _MIN_LLS_CHECK(x, y) \
    ((!OPERAND_TYPE_FITS_INTO_LLONG(x) && !OPERAND_TYPE_FITS_INTO_LLONG(y) && OPERAND_EXCEEDS_LLONG_MAX(x) && OPERAND_EXCEEDS_LLONG_MAX(y)) ? \
        _RAISE_EXCEPTION : \
        _MIN_LLS_UNSAFE(x, y))
#define _FASTER_MIN_LLS_CHECK(x, y) \
    (!OPERAND_TYPE_FITS_INTO_LLONG(x) ? \
        (!OPERAND_TYPE_FITS_INTO_LLONG(y) ? \
            (OPERAND_EXCEEDS_LLONG_MAX(x) ? \
                (OPERAND_EXCEEDS_LLONG_MAX(y) ? \
                    _RAISE_EXCEPTION : \
                    ((long long)(y))) : \
                (OPERAND_EXCEEDS_LLONG_MAX(y) ? \
                    ((long long)(x)) : \
                    _MIN_LLS_UNSAFE(x, y))) : \
            (OPERAND_EXCEEDS_LLONG_MAX(x) ? \
                ((long long)(y)) : \
                _MIN_LLS_UNSAFE(x, y))) : \
        (!OPERAND_TYPE_FITS_INTO_LLONG(y) ? \
            (OPERAND_EXCEEDS_LLONG_MAX(y) ? \
                ((long long)(x)) : \
                _MIN_LLS_UNSAFE(x, y)) : \
            _MIN_LLS_UNSAFE(x, y)))
#define _FASTER_MIN_LLS_FLEX(x, y) \
    (!OPERAND_TYPE_FITS_INTO_LLONG(x) ? \
        (!OPERAND_TYPE_FITS_INTO_LLONG(y) ? \
            ((((unsigned long long)(x)) < ((unsigned long long)(y))) ? \
                ((long long)(x)) : \
                ((long long)(y))) : \
            (((y) < 0) ? \
                ((long long)(y)) : \
                ((((unsigned long long)(x)) < ((unsigned long long)(y))) ? \
                    ((long long)(x)) : \
                    ((long long)(y))))) : \
        (!OPERAND_TYPE_FITS_INTO_LLONG(y) ? \
            (((x) < 0) ? \
                ((long long)(x)) : \
                ((((unsigned long long)(x)) < ((unsigned long long)(y))) ? \
                    ((long long)(x)) : \
                    ((long long)(y)))) : \
            _MIN_LLS_UNSAFE(x, y)))

/**
 * The _MIN_CHECK macro causes a divide-by-zero error if one of the operands is negative and the other is of unsigned type, else it just does the simple _MIN_UNSAFE.
 */
#define _MIN_CHECK(x, y) \
    (((((x) < 0) && !OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(y)) || (((y) < 0) && !OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE(x))) ? \
        _RAISE_EXCEPTION : \
        _MIN_UNSAFE(x, y))

/**
 * The MIN_LLU macros always correctly choose the smallest one of the two 
 * operands, but the result is cast to type unsigned long long.  Therefore if 
 * the winning operand (the smallest operand) is negative, and if you use the 
 * result without casting it back to a signed type first then you can get wrong 
 * behavior, for example the following will evaluate to true:
 * MIN_LLU(-1, 1) > 0
 * Note that casting it back to a signed type is implementation-dependent, i.e. 
 * the C standard doesn't guarantee you that you will get the right value back.  
 * That is, the C standard doesn't guarantee that the following expression will 
 * evaluate to -1:
 * (signed int)MIN_LLU(-1, 1)
 * (Although I guess that this will work on almost all platforms in practice.)
 */
#define _MIN_LLU_UNSAFE(x, y) \
    ((((unsigned long long)(x)) < ((unsigned long long)(y))) ? \
        ((unsigned long long)(x)) : \
        ((unsigned long long)(y)))

/* _MIN_LLU_FLEX is just for pedantic and verification purposes -- we use _FASTER_MIN_LLU_FLEX in practice. */
#define _MIN_LLU_FLEX(x, y) \
    ((((x) < 0) && ((y) >= 0)) ? \
        ((unsigned long long)(x)) : \
        ((((y) < 0) && ((x) >= 0)) ? \
            ((unsigned long long)(y)) : \
            _MIN_LLU_UNSAFE(x, y)))

#define _FASTER_MIN_LLU_FLEX(x, y) \
    (!OPERAND_TYPE_FITS_INTO_LLONG(x) ? \
        (!OPERAND_TYPE_FITS_INTO_LLONG(y) ? \
            _MIN_LLU_UNSAFE(x, y) : \
            (((y) < 0) ? \
                ((unsigned long long)(y)) : \
                _MIN_LLU_UNSAFE(x, y))) : \
        (!OPERAND_TYPE_FITS_INTO_LLONG(y) ? \
            (((x) < 0) ? \
                ((unsigned long long)(x)) : \
                _MIN_LLU_UNSAFE(x, y))))

#ifdef ZMINMAXDEBUG
#define MIN_LLS _FASTER_MIN_LLS_CHECK
#define MIN_LLU _MIN_CHECK
#else
#define MIN_LLS _FASTER_MIN_LLS_FLEX
#define MIN_LLU _MIN_LLU_FLEX
#endif

#define MAXi _FASTER_MAX_SAFE
#define MINi MIN_LLS

#endif /* #ifndef __INCL_minmaximp_h */
