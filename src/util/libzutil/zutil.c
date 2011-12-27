/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#include "zutil.h"

#include "moreassert.h"
#include "morelimits.h"

int const zutil_vermaj = 1;
int const zutil_vermin = 0;
int const zutil_vermicro = 0;
char const* const zutil_vernum = "1.0.0";

#undef uint16_decode
unsigned short
uint16_decode(const zbyte* const bs) {
	return ((unsigned short)(bs[1])) | ((unsigned short)(bs[0])) << 8;
}

#undef UINT16_DECODE
unsigned short
UINT16_DECODE(const zbyte* const bs) {
	return ((unsigned short)(bs[1])) | ((unsigned short)(bs[0])) << 8;
}

#undef uint32_decode
unsigned long
uint32_decode(const zbyte* const bs) {
	return ((unsigned long)(bs[3])) | ((unsigned long)(bs[2])) << 8 | ((unsigned long)(bs[1])) << 16 | ((unsigned long)(bs[0])) << 24;
}

#undef UINT32_DECODE
unsigned long
UINT32_DECODE(const zbyte* const bs) {
	return ((unsigned long)(bs[3])) | ((unsigned long)(bs[2])) << 8 | ((unsigned long)(bs[1])) << 16 | ((unsigned long)(bs[0])) << 24;
}

#undef uint16_encode
void
uint16_encode(const unsigned short hu, zbyte* const bs) {
	runtime_assert(hu <= Z_UINT16_MAX, "Cannot encode a number this big into 16 bits.");
	bs[1] = hu % (1U << 8);
	bs[0] = hu / (1U << 8);
}

#undef uint32_encode
void
uint32_encode(const unsigned long lu, zbyte* const bs) {
	runtime_assert(lu <= Z_UINT32_MAX, "Cannot encode a number this big into 32 bits.");
	bs[3] = lu % (1U << 8);
	bs[2] = (lu / (1U << 8)) % (1U << 8);
	bs[1] = (lu / (1LU << 16)) % (1U << 8);
	bs[0] = lu / (1LU << 24);
}

#undef uint64_decode
unsigned long long
uint64_decode(const zbyte* const bs) {
	return ((unsigned long long)(bs[7])) | ((unsigned long long)(bs[6])) << 8 | ((unsigned long long)(bs[5])) << 16 | ((unsigned long long)(bs[4])) << 24 | ((unsigned long long)(bs[3])) << 32 | ((unsigned long long)(bs[2])) << 40 | ((unsigned long long)(bs[1])) << 48 | ((unsigned long long)(bs[0])) << 56;
}

#undef UINT64_DECODE
unsigned long long
UINT64_DECODE(const zbyte* const bs) {
	return ((unsigned long long)(bs[7])) | ((unsigned long long)(bs[6])) << 8 | ((unsigned long long)(bs[5])) << 16 | ((unsigned long long)(bs[4])) << 24 | ((unsigned long long)(bs[3])) << 32 | ((unsigned long long)(bs[2])) << 40 | ((unsigned long long)(bs[1])) << 48 | ((unsigned long long)(bs[0])) << 56;
}

#undef uint64_encode
void
uint64_encode(const unsigned long long llu, zbyte* const bs) {
	runtime_assert(llu <= Z_UINT64_MAX, "Cannot encode a number this big into 64 bits.");
	bs[7] = llu % (1U << 8);
	bs[6] = (llu / (1U << 8)) % (1U << 8);
	bs[5] = (llu / (1LU << 16)) % (1U << 8);
	bs[4] = (llu / (1LU << 24)) % (1U << 8);
	bs[3] = (llu / (1LLU << 32)) % (1U << 8);
	bs[2] = (llu / (1LLU << 40)) % (1U << 8);
	bs[1] = (llu / (1LLU << 48)) % (1U << 8);
	bs[0] = (llu / (1LLU << 56));
}

unsigned int
nextmult(unsigned int k, unsigned int m) {
	if ((m % k) == 0)
		return m;
	else {
		unsigned int a = k - (m % k);
		runtime_assert(!add_would_overflow_uint(m, a), "Cannot store nextmult of these numbers in an unsigned int.");
		return m + a;
	}
}

unsigned long
lnextmult(unsigned long k, unsigned long m) {
	if ((m % k) == 0)
		return m;
	else {
		unsigned long a = k - (m % k);
		runtime_assert(!add_would_overflow_ulong(m, a), "Cannot store nextmult of these numbers in an unsigned long.");
		return m + a;
	}
}
 
#undef NEXTMULT
unsigned int
NEXTMULT(unsigned int k, unsigned int m) {
	if ((m % k) == 0)
		return m;
	else {
		unsigned int a = k - (m % k);
		runtime_assert(!add_would_overflow_uint(m, a), "Cannot store nextmult of these numbers in an unsigned int.");
		return m + a;
	}
}

#undef LNEXTMULT
unsigned long
LNEXTMULT(unsigned long k, unsigned long m) {
	if ((m % k) == 0)
		return m;
	else {
		unsigned long a = k - (m % k);
		runtime_assert(!add_would_overflow_ulong(m, a), "Cannot store nextmult of these numbers in an unsigned long.");
		return m + a;
	}
}


#undef divceil
unsigned int
divceil(unsigned int n, unsigned int d) {
	return n/d+((n%d)!=0);
}

#undef ldivceil
unsigned long
ldivceil(unsigned long n, unsigned long d) {
	return n/d+((n%d)!=0);
}

#undef DIVCEIL
unsigned int
DIVCEIL(unsigned int n, unsigned int d) {
	return n/d+((n%d)!=0);
}

#undef LDIVCEIL
unsigned long
LDIVCEIL(unsigned long n, unsigned long d) {
	return n/d+((n%d)!=0);
}

#undef add_would_overflow_char
bool
add_would_overflow_char(char x, char y) {
	return MACRO_ADD_WOULD_OVERFLOW_CHAR(x, y);
}

#undef ADD_WOULD_OVERFLOW_CHAR
bool
ADD_WOULD_OVERFLOW_CHAR(char x, char y) {
	return MACRO_ADD_WOULD_OVERFLOW_CHAR(x, y);
}

#undef add_would_overflow_uchar
bool
add_would_overflow_uchar(unsigned char x, unsigned char y) {
	return MACRO_ADD_WOULD_OVERFLOW_UCHAR(x, y);
}

#undef ADD_WOULD_OVERFLOW_UCHAR
bool
ADD_WOULD_OVERFLOW_UCHAR(unsigned char x, unsigned char y) {
	return MACRO_ADD_WOULD_OVERFLOW_UCHAR(x, y);
}

#undef add_would_overflow_schar
bool
add_would_overflow_schar(signed char x, signed char y) {
	return MACRO_ADD_WOULD_OVERFLOW_SCHAR(x, y);
}

#undef ADD_WOULD_OVERFLOW_SCHAR
bool
ADD_WOULD_OVERFLOW_SCHAR(signed char x, signed char y) {
	return MACRO_ADD_WOULD_OVERFLOW_SCHAR(x, y);
}

#undef add_would_overflow_shrt
bool
add_would_overflow_shrt(short x, short y) {
	return MACRO_ADD_WOULD_OVERFLOW_SHRT(x, y);
}

#undef ADD_WOULD_OVERFLOW_USHRT
bool
ADD_WOULD_OVERFLOW_USHRT(unsigned short x, unsigned short y) {
	return MACRO_ADD_WOULD_OVERFLOW_USHRT(x, y);
}

#undef add_would_overflow_int
bool
add_would_overflow_int(int x, int y) {
	return MACRO_ADD_WOULD_OVERFLOW_INT(x, y);
}

#undef ADD_WOULD_OVERFLOW_INT
bool
ADD_WOULD_OVERFLOW_INT(int x, int y) {
	return MACRO_ADD_WOULD_OVERFLOW_INT(x, y);
}

#undef add_would_overflow_uint
bool
add_would_overflow_uint(unsigned int x, unsigned int y) {
	return MACRO_ADD_WOULD_OVERFLOW_UINT(x, y);
}

#undef ADD_WOULD_OVERFLOW_UINT
bool
ADD_WOULD_OVERFLOW_UINT(unsigned int x, unsigned int y) {
	return MACRO_ADD_WOULD_OVERFLOW_UINT(x, y);
}

#undef add_would_overflow_long
bool
add_would_overflow_long(long x, long y) {
	return MACRO_ADD_WOULD_OVERFLOW_LONG(x, y);
}

#undef ADD_WOULD_OVERFLOW_LONG
bool
ADD_WOULD_OVERFLOW_LONG(long x, long y) {
	return MACRO_ADD_WOULD_OVERFLOW_LONG(x, y);
}

#undef add_would_overflow_ulong
bool
add_would_overflow_ulong(unsigned long x, unsigned long y) {
	return MACRO_ADD_WOULD_OVERFLOW_ULONG(x, y);
}

#undef ADD_WOULD_OVERFLOW_ULONG
bool
ADD_WOULD_OVERFLOW_ULONG(unsigned long x, unsigned long y) {
	return MACRO_ADD_WOULD_OVERFLOW_ULONG(x, y);
}

#undef add_would_overflow_llong
bool
add_would_overflow_llong(long long x, long long y) {
	return MACRO_ADD_WOULD_OVERFLOW_LLONG(x, y);
}

#undef ADD_WOULD_OVERFLOW_ULLONG
bool
ADD_WOULD_OVERFLOW_ULLONG(unsigned long long x, unsigned long long y) {
	return MACRO_ADD_WOULD_OVERFLOW_ULLONG(x, y);
}
