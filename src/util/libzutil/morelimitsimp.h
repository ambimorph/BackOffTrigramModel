/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#ifndef __INCL_morelimitsimp_h
#define __INCL_morelimitsimp_h

#define Z_MAX_UNSIGNED_typ(typ) ((typ)(~((typ)0)))
#define Z_MIN_UNSIGNED_typ(typ) ((typ)0)

/* The following Z_MAX_SIGNED_typ and Z_MIN_SIGNED_typ macros will work on any C 
   implementation where the maximum value of a signed type (called typ) is 
   equal to 2^(sizeof(typ)*CHAR_BIT) - 1, and the minimum value of a signed 
   type is equal to the -1*(maximum value+1).  I guess that this includes every
   extant C implementation. */
#define Z_SIGNED_HIGH_BIT_siz(siz) (((signed long long)1) << ((siz*CHAR_BIT)-2))
#define Z_SIGNED_LOW_BITS_siz(siz) (Z_SIGNED_HIGH_BIT_typ(typ)-1)
#define Z_SIGNED_HIGH_BIT_typ(typ) ((typ)(Z_SIGNED_HIGH_BIT_siz(sizeof(typ))))
#define Z_SIGNED_LOW_BITS_typ(typ) (Z_SIGNED_HIGH_BIT_typ(typ)-1)
#define Z_MAX_SIGNED_siz(siz) (Z_SIGNED_HIGH_BIT_siz(siz) + Z_SIGNED_LOW_BITS_siz(siz))
#define Z_MAX_SIGNED_typ(typ) ((typ)(Z_SIGNED_HIGH_BIT_typ(typ) + Z_SIGNED_LOW_BITS_typ(typ)))
#define Z_MIN_SIGNED_siz(siz) ((-Z_MAX_SIGNED_siz(siz))-1)
#define Z_MIN_SIGNED_typ(typ) ((typ)((-Z_MAX_SIGNED_typ(typ))-1))

#define Z_MAX_typ(typ) ((Z_MAX_SIGNED_typ(typ) > Z_MAX_UNSIGNED_typ(typ))?Z_MAX_SIGNED_typ(typ):Z_MAX_UNSIGNED_typ(typ))
#define Z_MIN_typ(typ) ((Z_MIN_SIGNED_typ(typ) < Z_MIN_UNSIGNED_typ(typ))?Z_MIN_SIGNED_typ(typ):Z_MIN_UNSIGNED_typ(typ))

#define Z_UNSIGNED_HIGH_BIT_BITS(b) (1ULL << ((b)-1))
#define Z_UNSIGNED_LOW_BITS_BITS(b) (Z_UNSIGNED_HIGH_BIT_BITS(b)-1)
#define Z_MAX_UNSIGNED_BITS(b) (Z_UNSIGNED_HIGH_BIT_BITS(b) | Z_UNSIGNED_LOW_BITS_BITS(b))
#define Z_MAX_UNSIGNED_siz(siz) (Z_UNSIGNED_HIGH_BIT_BITS((siz)*CHAR_BIT) | Z_UNSIGNED_LOW_BITS_BITS((siz)*CHAR_BIT))

#endif /* #ifndef __INCL_morelimitsimp_h */
