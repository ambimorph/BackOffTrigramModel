/**
 * copyright 2002-2005 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this work to deal in this work without
 * restriction (including the rights to use, modify, distribute,
 * sublicense, and/or sell copies).
 */

#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <limits.h>

#include "zutil.h"

#ifdef NDEBUG
#warning You are compiling test.c with NDEBUG set, and since the tests use assert() to verify the results, this means the tests will pass even if the code is wrong.
#endif

int
test_overflow() {
	/* Test that my understanding of C99 promotion and conversion and overflow is correct. */
	int x = INT_MAX-2;
	int y = INT_MAX-3;
	unsigned long long z = x + y;
	unsigned long long q = x;
	unsigned long long r = y;
	unsigned long long s = q + r;
	assert (z != s);
}

int
test_nextmult() {
	assert (nextmult(10, 20) == 20);
	assert (nextmult(10, 21) == 30);
	assert (nextmult(10, 19) == 20);
	assert (nextmult(1, 19) == 19);
	assert (nextmult(3, 5) == 6);

	assert (lnextmult(10, 20) == 20);
	assert (lnextmult(10, 21) == 30);
	assert (lnextmult(10, 19) == 20);
	assert (lnextmult(1, 19) == 19);
	assert (lnextmult(3, 5) == 6);
	assert (lnextmult(800000000, 5) == 800000000);

	assert (MACRO_NEXTMULT(10, 20) == 20);
	assert (MACRO_NEXTMULT(10, 21) == 30);
	assert (MACRO_NEXTMULT(10, 19) == 20);
	assert (MACRO_NEXTMULT(1, 19) == 19);
	assert (MACRO_NEXTMULT(3, 5) == 6);

	assert (MACRO_NEXTMULT(10, 20) == 20);
	assert (MACRO_NEXTMULT(10, 21) == 30);
	assert (MACRO_NEXTMULT(10, 19) == 20);
	assert (MACRO_NEXTMULT(1, 19) == 19);
	assert (MACRO_NEXTMULT(3, 5) == 6);
	assert (MACRO_NEXTMULT(800000000, 5) == 800000000);

	return 1;
}

int
_help_test_uint32_encode(const unsigned long lu) {
	unsigned long r;
	zbyte p[4];
	/*printf("about to try; %lu ", lu);*/
	uint32_encode(lu, p);
	r = uint32_decode(p);
	assert(lu == r);
	/*printf("== %lu\n", r);*/
	return 1;
}

int
_help_test_uint64_encode(const unsigned long long llu) {
	unsigned long long r;
	zbyte p[8];
	/*printf("about to try; %llu ", llu);*/
	uint64_encode(llu, p);
	r = uint64_decode(p);
	assert(llu == r);
	/*printf("== %llu\n", r);*/
	return 1;
}

int
test_uint32_encode() {
	_help_test_uint32_encode(0);
	_help_test_uint32_encode(1);
	_help_test_uint32_encode(2);
	_help_test_uint32_encode(24);
	_help_test_uint32_encode(42);
	_help_test_uint32_encode(53);
	_help_test_uint32_encode(99);
	_help_test_uint32_encode((1<<8)-2);
	_help_test_uint32_encode((1<<8)-1);
	_help_test_uint32_encode((1<<8));
	_help_test_uint32_encode((1<<8)+1);
	_help_test_uint32_encode((1<<8)+2);
	_help_test_uint32_encode((1<<16)-2);
	_help_test_uint32_encode((1<<16)-1);
	_help_test_uint32_encode((1<<16));
	_help_test_uint32_encode((1<<16)+1);
	_help_test_uint32_encode((1<<16)+2);
	_help_test_uint32_encode((1<<24)-2);
	_help_test_uint32_encode((1<<24)-1);
	_help_test_uint32_encode((1<<24));
	_help_test_uint32_encode((1<<24)+1);
	_help_test_uint32_encode((1<<24)+2);
	_help_test_uint32_encode(Z_UINT32_MAX-2);
	_help_test_uint32_encode(Z_UINT32_MAX-1);
	_help_test_uint32_encode(Z_UINT32_MAX);
	return 1;
}

int
test_uint64_encode() {
	_help_test_uint64_encode(0);
	_help_test_uint64_encode(1);
	_help_test_uint64_encode(2);
	_help_test_uint64_encode(24);
	_help_test_uint64_encode(42);
	_help_test_uint64_encode(53);
	_help_test_uint64_encode(99);
	_help_test_uint64_encode((1<<8)-2);
	_help_test_uint64_encode((1<<8)-1);
	_help_test_uint64_encode((1<<8));
	_help_test_uint64_encode((1<<8)+1);
	_help_test_uint64_encode((1<<8)+2);
	_help_test_uint64_encode((1<<16)-2);
	_help_test_uint64_encode((1<<16)-1);
	_help_test_uint64_encode((1<<16));
	_help_test_uint64_encode((1<<16)+1);
	_help_test_uint64_encode((1<<16)+2);
	_help_test_uint64_encode((1<<24)-2);
	_help_test_uint64_encode((1<<24)-1);
	_help_test_uint64_encode((1<<24));
	_help_test_uint64_encode((1<<24)+1);
	_help_test_uint64_encode((1<<24)+2);
	_help_test_uint64_encode(Z_UINT32_MAX-2);
	_help_test_uint64_encode(Z_UINT32_MAX-1);
	_help_test_uint64_encode(Z_UINT32_MAX);
	_help_test_uint64_encode(Z_UINT32_MAX+1LLU);
	_help_test_uint64_encode(Z_UINT32_MAX+2LLU);
	_help_test_uint64_encode(Z_UINT64_MAX-2);
	_help_test_uint64_encode(Z_UINT64_MAX-1);
	_help_test_uint64_encode(Z_UINT64_MAX);
	return 1;
}

void
bench_uint32_encode() {
	unsigned i;
	for (i = 0; i < 1000000; i++) {
		if (! test_uint32_encode()) {
			printf("what ???\n");
		}
	}
}

void
bench_uint64_encode() {
	unsigned i;
	for (i = 0; i < 1000000; i++) {
		if (! test_uint64_encode()) {
			printf("what ???\n");
		}
	}
}

int
test_generic_ADD_WOULD_OVERFLOW() {
	if (sizeof(signed char) < sizeof(signed int)) {
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX - 2, CHAR_MAX - 3));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX, CHAR_MAX));
		assert (!ADD_WOULD_OVERFLOW((CHAR_MAX/2)+1, (CHAR_MAX/2)+1));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX/2, CHAR_MAX/2));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX, 0));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX, 1));
		assert (!ADD_WOULD_OVERFLOW(1, CHAR_MAX));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX-1, 1));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX-2, 2));
		assert (!ADD_WOULD_OVERFLOW((char)0, (char)0));
	} else {
		assert (ADD_WOULD_OVERFLOW(CHAR_MAX - 2, CHAR_MAX - 3));
		assert (ADD_WOULD_OVERFLOW(CHAR_MAX, CHAR_MAX));
		assert (ADD_WOULD_OVERFLOW((CHAR_MAX/2)+1, (CHAR_MAX/2)+1));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX/2, CHAR_MAX/2));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX, 0));
		assert (ADD_WOULD_OVERFLOW(CHAR_MAX, 1));
		assert (ADD_WOULD_OVERFLOW(1, CHAR_MAX));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX-1, 1));
		assert (!ADD_WOULD_OVERFLOW(CHAR_MAX-2, 2));
		assert (!ADD_WOULD_OVERFLOW((char)0, (char)0));
	}

	if (sizeof(signed short) < sizeof(signed int)) {
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX - 2, SHRT_MAX - 3));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX, SHRT_MAX));
		assert (!ADD_WOULD_OVERFLOW((SHRT_MAX/2)+1, (SHRT_MAX/2)+1));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX/2, SHRT_MAX/2));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX, 0));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX-1, 1));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX-2, 2));

		assert (!ADD_WOULD_OVERFLOW(SHRT_MIN, SHRT_MIN));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MIN, -1));
		assert (!ADD_WOULD_OVERFLOW(-1, SHRT_MIN));
		assert (!ADD_WOULD_OVERFLOW((SHRT_MIN/2)-1, (SHRT_MIN/2)-1));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MIN/2, SHRT_MIN/2));
		assert (!ADD_WOULD_OVERFLOW((short)0, (short)0));
	} else {
		assert (ADD_WOULD_OVERFLOW(SHRT_MAX - 2, SHRT_MAX - 3));
		assert (ADD_WOULD_OVERFLOW(SHRT_MAX, SHRT_MAX));
		assert (ADD_WOULD_OVERFLOW((SHRT_MAX/2)+1, (SHRT_MAX/2)+1));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX/2, SHRT_MAX/2));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX, 0));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX-1, 1));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MAX-2, 2));

		assert (ADD_WOULD_OVERFLOW(SHRT_MIN, SHRT_MIN));
		assert (ADD_WOULD_OVERFLOW(SHRT_MIN, -1));
		assert (ADD_WOULD_OVERFLOW(-1, SHRT_MIN));
		assert (ADD_WOULD_OVERFLOW((SHRT_MIN/2)-1, (SHRT_MIN/2)-1));
		assert (!ADD_WOULD_OVERFLOW(SHRT_MIN/2, SHRT_MIN/2));
		assert (!ADD_WOULD_OVERFLOW((short)0, (short)0));
	}

//#define ADD_WOULD_OVERFLOW(x, y) ( \
// (OPERAND_TYPE_FITS_INTO_LLONG(x) && OPERAND_TYPE_FITS_INTO_LLONG(y)) ? \
//  ((long long)(x) + (long long)(y)) != (x)+(y) : \
//   (((x) >= 0) && ((y) >= 0)) ? \
//    ((x) + (y) < (x)) : \
//    (true))
	printf("OPERAND_TYPE_FITS_INTO_LLONG(INT_MAX-2): %d\n", OPERAND_TYPE_FITS_INTO_LLONG(INT_MAX-2));
	printf("OPERAND_TYPE_FITS_INTO_LLONG(INT_MAX-3): %d\n", OPERAND_TYPE_FITS_INTO_LLONG(INT_MAX-3));

	assert (ADD_WOULD_OVERFLOW(INT_MAX - 2, INT_MAX - 3));
	assert (ADD_WOULD_OVERFLOW(INT_MAX, INT_MAX));
	assert (ADD_WOULD_OVERFLOW((INT_MAX/2)+1, (INT_MAX/2)+1));
	assert (!ADD_WOULD_OVERFLOW(INT_MAX/2, INT_MAX/2));
	assert (!ADD_WOULD_OVERFLOW(INT_MAX, 0));
	assert (ADD_WOULD_OVERFLOW(INT_MAX, 1));
	assert (ADD_WOULD_OVERFLOW(1, INT_MAX));
	assert (!ADD_WOULD_OVERFLOW(INT_MAX-1, 1));
	assert (!ADD_WOULD_OVERFLOW(INT_MAX-2, 2));

	assert (ADD_WOULD_OVERFLOW(INT_MIN, INT_MIN));
	assert (ADD_WOULD_OVERFLOW(INT_MIN, -1));
	assert (ADD_WOULD_OVERFLOW(-1, INT_MIN));
	assert (ADD_WOULD_OVERFLOW((INT_MIN/2)-1, (INT_MIN/2)-1));
	assert (!ADD_WOULD_OVERFLOW(INT_MIN/2, INT_MIN/2));
	assert (!ADD_WOULD_OVERFLOW(0, 0));

	assert (ADD_WOULD_OVERFLOW(UINT_MAX - 2, UINT_MAX - 3));
	assert (ADD_WOULD_OVERFLOW(UINT_MAX, UINT_MAX));
	assert (ADD_WOULD_OVERFLOW((UINT_MAX/2)+1, (UINT_MAX/2)+1));
	assert (!ADD_WOULD_OVERFLOW(UINT_MAX/2, UINT_MAX/2));
	assert (!ADD_WOULD_OVERFLOW(UINT_MAX, 0));
	assert (ADD_WOULD_OVERFLOW(UINT_MAX, 1));
	assert (ADD_WOULD_OVERFLOW(1, UINT_MAX));
	assert (!ADD_WOULD_OVERFLOW(UINT_MAX-1, 1));
	assert (!ADD_WOULD_OVERFLOW(UINT_MAX-2, 2));
	assert (!ADD_WOULD_OVERFLOW(0U, 0U));

	printf("LONG_MAX - 2: %ld, LONG_MAX - 3: %ld, LONG_MAX: %ld, LONG_MAX-2+LONG_MAX-3: %ld\n", LONG_MAX-2, LONG_MAX-3, LONG_MAX, LONG_MAX-2+LONG_MAX-3);
	assert (ADD_WOULD_OVERFLOW(LONG_MAX - 2, LONG_MAX - 3));
	assert (ADD_WOULD_OVERFLOW(LONG_MAX, LONG_MAX));
	assert (ADD_WOULD_OVERFLOW((LONG_MAX/2)+1, (LONG_MAX/2)+1));
	assert (!ADD_WOULD_OVERFLOW(LONG_MAX/2, LONG_MAX/2));
	assert (!ADD_WOULD_OVERFLOW(LONG_MAX, 0));
	assert (ADD_WOULD_OVERFLOW(LONG_MAX, 1));
	assert (ADD_WOULD_OVERFLOW(1, LONG_MAX));
	assert (!ADD_WOULD_OVERFLOW(LONG_MAX-1, 1));
	assert (!ADD_WOULD_OVERFLOW(LONG_MAX-2, 2));

	assert (ADD_WOULD_OVERFLOW(LONG_MIN, LONG_MIN));
	assert (ADD_WOULD_OVERFLOW(LONG_MIN, -1));
	assert (ADD_WOULD_OVERFLOW(-1, LONG_MIN));
	assert (ADD_WOULD_OVERFLOW((LONG_MIN/2)-1, (LONG_MIN/2)-1));
	assert (!ADD_WOULD_OVERFLOW(LONG_MIN/2, LONG_MIN/2));
	assert (!ADD_WOULD_OVERFLOW(0L, 0L));

	assert (ADD_WOULD_OVERFLOW(ULONG_MAX - 2, ULONG_MAX - 3));
	assert (ADD_WOULD_OVERFLOW(ULONG_MAX, ULONG_MAX));
	assert (ADD_WOULD_OVERFLOW((ULONG_MAX/2)+1, (ULONG_MAX/2)+1));
	assert (!ADD_WOULD_OVERFLOW(ULONG_MAX/2, ULONG_MAX/2));
	assert (!ADD_WOULD_OVERFLOW(ULONG_MAX, 0));
	assert (ADD_WOULD_OVERFLOW(ULONG_MAX, 1));
	assert (ADD_WOULD_OVERFLOW(1, ULONG_MAX));
	assert (!ADD_WOULD_OVERFLOW(ULONG_MAX-1, 1));
	assert (!ADD_WOULD_OVERFLOW(ULONG_MAX-2, 2));
	assert (!ADD_WOULD_OVERFLOW(0, 0));

	return 1;
}

int
test_specific_add_would_overflow() {
	assert (add_would_overflow_char(CHAR_MAX - 2, CHAR_MAX - 3));
	assert (add_would_overflow_char(CHAR_MAX, CHAR_MAX));
	assert (add_would_overflow_char((CHAR_MAX/2)+1, (CHAR_MAX/2)+1));
	assert (!add_would_overflow_char(CHAR_MAX/2, CHAR_MAX/2));
	assert (!add_would_overflow_char(CHAR_MAX, 0));
	assert (add_would_overflow_char(CHAR_MAX, 1));
	assert (add_would_overflow_char(1, CHAR_MAX));
	assert (!add_would_overflow_char(CHAR_MAX-1, 1));
	assert (!add_would_overflow_char(CHAR_MAX-2, 2));
	assert (!add_would_overflow_char(0, 0));

	assert (add_would_overflow_shrt(SHRT_MAX - 2, SHRT_MAX - 3));
	assert (add_would_overflow_shrt(SHRT_MAX, SHRT_MAX));
	assert (add_would_overflow_shrt((SHRT_MAX/2)+1, (SHRT_MAX/2)+1));
	assert (!add_would_overflow_shrt(SHRT_MAX/2, SHRT_MAX/2));
	assert (!add_would_overflow_shrt(SHRT_MAX, 0));
	assert (!add_would_overflow_shrt(SHRT_MAX-1, 1));
	assert (!add_would_overflow_shrt(SHRT_MAX-2, 2));
	assert (!add_would_overflow_shrt(0, 0));

	assert (add_would_overflow_shrt(SHRT_MIN, SHRT_MIN));
	assert (add_would_overflow_shrt(SHRT_MIN, -1));
	assert (add_would_overflow_shrt(-1, SHRT_MIN));
	assert (add_would_overflow_shrt((SHRT_MIN/2)-1, (SHRT_MIN/2)-1));
	assert (!add_would_overflow_shrt(SHRT_MIN/2, SHRT_MIN/2));

	assert (add_would_overflow_int(INT_MAX - 2, INT_MAX - 3));
	assert (add_would_overflow_int(INT_MAX, INT_MAX));
	assert (add_would_overflow_int((INT_MAX/2)+1, (INT_MAX/2)+1));
	assert (!add_would_overflow_int(INT_MAX/2, INT_MAX/2));
	assert (!add_would_overflow_int(INT_MAX, 0));
	assert (add_would_overflow_int(INT_MAX, 1));
	assert (add_would_overflow_int(1, INT_MAX));
	assert (!add_would_overflow_int(INT_MAX-1, 1));
	assert (!add_would_overflow_int(INT_MAX-2, 2));
	assert (!add_would_overflow_int(0, 0));

	assert (add_would_overflow_int(INT_MIN, INT_MIN));
	assert (add_would_overflow_int(INT_MIN, -1));
	assert (!add_would_overflow_int(0, -1));
	assert (add_would_overflow_int(-1, INT_MIN));
	assert (add_would_overflow_int((INT_MIN/2)-1, (INT_MIN/2)-1));
	assert (!add_would_overflow_int(INT_MIN/2, INT_MIN/2));

	assert (add_would_overflow_uint(UINT_MAX - 2, UINT_MAX - 3));
	assert (add_would_overflow_uint(UINT_MAX, UINT_MAX));
	assert (add_would_overflow_uint((UINT_MAX/2)+1, (UINT_MAX/2)+1));
	assert (!add_would_overflow_uint(UINT_MAX/2, UINT_MAX/2));
	assert (!add_would_overflow_uint(UINT_MAX, 0));
	assert (add_would_overflow_uint(UINT_MAX, 1));
	assert (add_would_overflow_uint(1, UINT_MAX));
	assert (!add_would_overflow_uint(UINT_MAX-1, 1));
	assert (!add_would_overflow_uint(UINT_MAX-2, 2));
	assert (!add_would_overflow_uint(0, 0));

	assert (add_would_overflow_long(LONG_MAX - 2, LONG_MAX - 3));
	assert (add_would_overflow_long(LONG_MAX, LONG_MAX));
	assert (add_would_overflow_long((LONG_MAX/2)+1, (LONG_MAX/2)+1));
	assert (!add_would_overflow_long(LONG_MAX/2, LONG_MAX/2));
	assert (!add_would_overflow_long(LONG_MAX, 0));
	assert (add_would_overflow_long(LONG_MAX, 1));
	assert (add_would_overflow_long(1, LONG_MAX));
	assert (!add_would_overflow_long(LONG_MAX-1, 1));
	assert (!add_would_overflow_long(LONG_MAX-2, 2));
	assert (!add_would_overflow_long(0, 0));

	assert (add_would_overflow_long(LONG_MIN, LONG_MIN));
	assert (add_would_overflow_long(LONG_MIN, -1));
	assert (add_would_overflow_long(-1, LONG_MIN));
	assert (add_would_overflow_long((LONG_MIN/2)-1, (LONG_MIN/2)-1));
	assert (!add_would_overflow_long(LONG_MIN/2, LONG_MIN/2));

	assert (add_would_overflow_ulong(ULONG_MAX - 2, ULONG_MAX - 3));
	assert (add_would_overflow_ulong(ULONG_MAX, ULONG_MAX));
	assert (add_would_overflow_ulong((ULONG_MAX/2)+1, (ULONG_MAX/2)+1));
	assert (!add_would_overflow_ulong(ULONG_MAX/2, ULONG_MAX/2));
	assert (!add_would_overflow_ulong(ULONG_MAX, 0));
	assert (add_would_overflow_ulong(ULONG_MAX, 1));
	assert (add_would_overflow_ulong(1, ULONG_MAX));
	assert (!add_would_overflow_ulong(ULONG_MAX-1, 1));
	assert (!add_would_overflow_ulong(ULONG_MAX-2, 2));
	assert (!add_would_overflow_ulong(0, 0));

	return 1;
}

int
test_CHAR_FITS_INTO_INT() {
	assert (TYPE_FITS_INTO_INT(signed char));
	assert (TYPE_FITS_INTO_INT(char));
	assert (TYPE_FITS_INTO_INT(unsigned char));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)0));
	assert (OPERAND_TYPE_FITS_INTO_INT((char)0));
	assert (OPERAND_TYPE_FITS_INTO_INT((unsigned char)0));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)1));
	assert (OPERAND_TYPE_FITS_INTO_INT((char)1));
	assert (OPERAND_TYPE_FITS_INTO_INT((unsigned char)1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)2));
	assert (OPERAND_TYPE_FITS_INTO_INT((char)2));
	assert (OPERAND_TYPE_FITS_INTO_INT((unsigned char)2));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)-1));
	assert (OPERAND_TYPE_FITS_INTO_INT((char)-1));
	assert (OPERAND_TYPE_FITS_INTO_INT((unsigned char)-1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_INT((char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_INT((unsigned char)UCHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)CHAR_MIN));
	assert (OPERAND_TYPE_FITS_INTO_INT((char)CHAR_MIN));
	assert (OPERAND_TYPE_FITS_INTO_INT((unsigned char)UCHAR_MIN));
	return 1;
}

int
test_CHAR_FITS_INTO_LONG() {
	assert (TYPE_FITS_INTO_LONG(signed char));
	assert (TYPE_FITS_INTO_LONG(char));
	assert (TYPE_FITS_INTO_LONG(unsigned char));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((char)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((unsigned char)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((char)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((unsigned char)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((char)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((unsigned char)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((unsigned char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((unsigned char)UCHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)CHAR_MIN));
	assert (OPERAND_TYPE_FITS_INTO_LONG((char)CHAR_MIN));
	assert (OPERAND_TYPE_FITS_INTO_LONG((unsigned char)UCHAR_MIN));
	return 1;
}

int
test_CHAR_FITS_INTO_LLONG() {
	assert (TYPE_FITS_INTO_LLONG(signed char));
	assert (TYPE_FITS_INTO_LLONG(char));
	assert (TYPE_FITS_INTO_LLONG(unsigned char));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((char)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((unsigned char)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((char)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((unsigned char)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((char)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((unsigned char)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((unsigned char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((unsigned char)UCHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)CHAR_MIN));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((char)CHAR_MIN));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((unsigned char)UCHAR_MIN));
	return 1;
}

int
test_CHAR_PROMOTES_TO_SIGNED_TYPE() {
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(signed char));
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(char));
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(unsigned char));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((char)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned char)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((char)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned char)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((char)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned char)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((char)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned char)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((char)CHAR_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned char)UCHAR_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)CHAR_MIN));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((char)CHAR_MIN));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned char)UCHAR_MIN));
	return 1;
}

int
test_SIGNED_NONLONG_FITS_INTO_INT() {
	assert (TYPE_FITS_INTO_INT(signed char));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)0));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)2));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)-1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed char)CHAR_MIN));
	assert (TYPE_FITS_INTO_INT(signed short));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed short)0));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed short)1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed short)2));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed short)-1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed short)SHRT_MAX));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed short)SHRT_MIN));
	assert (TYPE_FITS_INTO_INT(signed int));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed int)0));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed int)1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed int)2));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed int)-1));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed int)INT_MAX));
	assert (OPERAND_TYPE_FITS_INTO_INT((signed int)INT_MIN));
	return 1;
}

int
test_SIGNED_STUFF_FITS_INTO_LONG() {
	assert (TYPE_FITS_INTO_LONG(signed char));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed char)CHAR_MIN));
	assert (TYPE_FITS_INTO_LONG(signed short));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed short)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed short)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed short)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed short)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed short)SHRT_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed short)SHRT_MIN));
	assert (TYPE_FITS_INTO_LONG(signed int));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed int)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed int)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed int)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed int)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed int)INT_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed int)INT_MIN));
	assert (TYPE_FITS_INTO_LONG(signed long));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed long)0));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed long)1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed long)2));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed long)-1));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed long)LONG_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LONG((signed long)LONG_MIN));
	return 1;
}

int
test_SIGNED_STUFF_FITS_INTO_LLONG() {
	assert (TYPE_FITS_INTO_LLONG(signed char));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed char)CHAR_MIN));
	assert (TYPE_FITS_INTO_LLONG(signed short));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed short)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed short)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed short)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed short)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed short)SHRT_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed short)SHRT_MIN));
	assert (TYPE_FITS_INTO_LLONG(signed int));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed int)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed int)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed int)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed int)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed int)INT_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed int)INT_MIN));
	assert (TYPE_FITS_INTO_LLONG(signed long));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long)LONG_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long)LONG_MIN));
	assert (TYPE_FITS_INTO_LLONG(signed long long));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long long)0));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long long)1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long long)2));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long long)-1));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long long)LLONG_MAX));
	assert (OPERAND_TYPE_FITS_INTO_LLONG((signed long long)LLONG_MIN));
	return 1;
}

int
test_SIGNED_NONLONG_PROMOTES_TO_SIGNED_TYPE() {
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(signed char));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)CHAR_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed char)CHAR_MIN));
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(signed short));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed short)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed short)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed short)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed short)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed short)SHRT_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed short)SHRT_MIN));
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(signed int));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)INT_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((signed int)INT_MIN));
	return 1;
}

int
test_UNSIGNED_INT_NOT_FITS_INTO_INT() {
	assert (!TYPE_FITS_INTO_INT(unsigned int));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned int)0));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned int)-1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned int)1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned int)2));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned int)UINT_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned int)UINT_MIN));
	return 1;
}

int
test_UNSIGNED_INT_NOT_PROMOTES_TO_SIGNED_TYPE() {
	assert (!TYPE_PROMOTES_TO_SIGNED_TYPE(unsigned int));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)0));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)-1));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)1));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)2));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)UINT_MAX));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned int)UINT_MIN));
	return 1;
}

int
test_UNSIGNED_LONG_NOT_FITS_INTO_INT() {
	assert (!TYPE_FITS_INTO_INT(unsigned long));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long)0));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long)-1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long)1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long)2));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long)ULONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long)ULONG_MIN));
	return 1;
}

int
test_UNSIGNED_LONG_NOT_FITS_INTO_LONG() {
	assert (!TYPE_FITS_INTO_LONG(unsigned long));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long)0));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long)-1));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long)1));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long)2));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long)ULONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long)ULONG_MIN));
	return 1;
}

int
test_UNSIGNED_LONG_NOT_PROMOTES_TO_SIGNED_TYPE() {
	assert (!TYPE_PROMOTES_TO_SIGNED_TYPE(unsigned long));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long)0));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long)-1));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long)1));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long)2));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long)ULONG_MAX));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long)ULONG_MIN));
	return 1;
}

int
test_UNSIGNED_LLONG_NOT_FITS_INTO_INT() {
	assert (!TYPE_FITS_INTO_INT(unsigned long long));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)0));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)-1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)2));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)ULONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)ULONG_MIN));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)ULLONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_INT((unsigned long long)ULLONG_MIN));
	return 1;
}

int
test_UNSIGNED_LLONG_NOT_FITS_INTO_LONG() {
	assert (!TYPE_FITS_INTO_LONG(unsigned long long));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)0));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)-1));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)1));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)2));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)ULONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)ULONG_MIN));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)ULLONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_LONG((unsigned long long)ULLONG_MIN));
	return 1;
}

int
test_UNSIGNED_LLONG_NOT_FITS_INTO_LLONG() {
	assert (!TYPE_FITS_INTO_LLONG(unsigned long long));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)0));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)-1));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)1));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)2));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)ULONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)ULONG_MIN));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)ULLONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_LLONG((unsigned long long)ULLONG_MIN));
	return 1;
}

int
test_UNSIGNED_LLONG_NOT_PROMOTES_TO_SIGNED_TYPE() {
	assert (!TYPE_PROMOTES_TO_SIGNED_TYPE(unsigned long long));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)0));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)-1));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)1));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)2));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)ULONG_MAX));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)ULONG_MIN));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)ULLONG_MAX));
	assert (!OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((unsigned long long)ULLONG_MIN));
	return 1;
}

int
test_SIGNED_LLONG_NOT_FITS_INTO_INT() {
	assert (!TYPE_FITS_INTO_INT(long long));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)0));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)-1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)1));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)2));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)ULONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)ULONG_MIN));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)ULLONG_MAX));
	assert (!OPERAND_TYPE_FITS_INTO_INT((long long)ULLONG_MIN));
	return 1;
}

int
test_SIGNED_LLONG_PROMOTES_TO_SIGNED_TYPE() {
	assert (TYPE_PROMOTES_TO_SIGNED_TYPE(long long));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)0));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)-1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)1));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)2));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)ULONG_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)ULONG_MIN));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)ULLONG_MAX));
	assert (OPERAND_TYPE_PROMOTES_TO_SIGNED_TYPE((long long)ULLONG_MIN));
	return 1;
}

int
test_FITS_INTO_INT() {
	test_CHAR_FITS_INTO_INT();
	test_SIGNED_NONLONG_FITS_INTO_INT();
	test_UNSIGNED_INT_NOT_FITS_INTO_INT();
	test_UNSIGNED_LONG_NOT_FITS_INTO_INT();
	test_UNSIGNED_LLONG_NOT_FITS_INTO_INT();
	test_SIGNED_LLONG_NOT_FITS_INTO_INT();
	return 1;
}

int
test_FITS_INTO_LONG() {
	test_CHAR_FITS_INTO_LONG();
	test_SIGNED_STUFF_FITS_INTO_LONG();
	test_UNSIGNED_LONG_NOT_FITS_INTO_LONG();
	test_UNSIGNED_LLONG_NOT_FITS_INTO_LONG();
	return 1;
}

int
test_FITS_INTO_LLONG() {
	test_CHAR_FITS_INTO_LLONG();
	test_SIGNED_STUFF_FITS_INTO_LLONG();
	test_UNSIGNED_LLONG_NOT_FITS_INTO_LLONG();
	return 1;
}

int
test_PROMOTES_TO_SIGNED_TYPE() {
	if (!test_CHAR_PROMOTES_TO_SIGNED_TYPE()) {
		return 0;
	}

	if (!test_SIGNED_NONLONG_PROMOTES_TO_SIGNED_TYPE()) {
		return 0;
	}

	if (!test_UNSIGNED_INT_NOT_PROMOTES_TO_SIGNED_TYPE()) {
		return 0;
	}

	if (!test_UNSIGNED_LONG_NOT_PROMOTES_TO_SIGNED_TYPE()) {
		return 0;
	}
	
	if (!test_UNSIGNED_LLONG_NOT_PROMOTES_TO_SIGNED_TYPE()) {
		return 0;
	}

	if (!test_SIGNED_LLONG_PROMOTES_TO_SIGNED_TYPE()) {
		return 0;
	}

	return 1;
}

/* If this test is commented-in, it will ideally give compile-time errors!
int
test_MIN_crazybadargs() {
	char b[10];
	int z = 1;
	MINi(b, z);
}
*/

int
test_minmax_fast() {
	unsigned int unsignedthree = 3;
	unsigned char unsignedcharthree = 3;
	long long signedllthree = 3;
	int negone = -1;
	if (_MIN_UNSAFE(unsignedthree, negone) != negone) {
		/* printf("just as we expected, using _MIN_UNSAFE on one negative operand and one unsigned int operand results in the wrong answer; _MIN_UNSAFE(%uU, %d) != %d\n", unsignedthree, negone, negone); */
	} else {
		printf("???_MIN_UNSAFE() should not have been able to correctly answer this question featuring a negative operand and an unsigned int operand.\n");
	}
	if (_MAX_UNSAFE(unsignedthree, negone) != unsignedthree) {
		/* printf("just as we expected, using _MAX_UNSAFE on one negative operand and one unsigned int operand results in the wrong answer; _MAX_UNSAFE(%uU, %d) != %d\n", unsignedthree, negone, unsignedthree); */
	} else {
		printf("???_MAX_UNSAFE() should not have been able to correctly answer this question featuring a negative operand and an unsigned int operand.\n");
	}
	if (_MIN_UNSAFE(signedllthree, negone) != negone) {
		printf("???_MIN_UNSAFE() should have been able to correctly answer this question featuring a negative operand and a long long operand.  _MIN_UNSAFE(%lldLL, %d) != %d\n\n", signedllthree, negone, negone);
	} else {
		/* printf("just as we expected, using _MIN_UNSAFE on one negative operand and one long long operand results in the right answer\n"); */
	}
	if (_MIN_UNSAFE(unsignedcharthree, negone) != negone) {
		printf("???_MIN_UNSAFE() should have been able to correctly answer this question featuring a negative operand and an unsigned char operand. _MIN_UNSAFE(%uc, %d) != %d\n\n", unsignedcharthree, negone, negone);
	} else {
		/* printf("just as we expected, using _MIN_UNSAFE on one negative operand and one unsigned char operand results in the right answer\n"); */
	}
	return 0;
}

int
_test_MIN_smallerint_biggeruint(int i, unsigned u) {
	if (MINi(i, u) >= ((long long)(u))) {
		printf("failed test %d MINi(%d, %uU): %lldLL == %lluULL >= u == %uU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	if (MINi(i, u) > i) {
		printf("failed test %d MINi(%d, %uU): %lldLL == %lluULL > i == %d\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) != i) {
		printf("failed test %d MINi(%d, %uU): %lldLL == %lluULL != i == %d\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	return 0;
}

int 
_test_MAX_smallerint_biggeruint(int i, unsigned u) {
	if (MAXi(i, u) < u) {
		printf("failed test %d MAXi(%d, %uU): %lldLL == %lluLLU < u == %uU == %uU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u, u);
	}
	if (MAXi(i, u) != u) {
		printf("failed test %d MAXi(%d, %uU): %lldLL == %lluLLU != u == %u\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	return 0;
}

int
_test_MIN_smallerlong_biggerulong(long i, unsigned long u) {
	if (MINi(i, u) > i) {
		printf("failed test %d MINi(%ld, %lu): %lldLL == %lluULL > i == %ld\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) != i) {
		printf("failed test %d MINi(%ld, %lu): %lldLL == %lluULL != i == %ld\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	return 0;
}

int
_test_MAX_smallerlong_biggerulong(long i, unsigned long u) {
	if (MAXi(i, u) < u) {
		printf("failed test %d MAXi(%ld, %lu): %lldLL == %lluLLU < u == %luUL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	if (MAXi(i, u) != u) {
		printf("failed test %d MAXi(%ld, %lu): %lldLL == %lluLLU != u == %luUL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	return 0;
}

int
_test_MIN_biggerint_smalleruint(int i, unsigned u) {
	if (MINi(i, u) >= i) {
		printf("failed test %d MINi(%d, %uU): %lldLL == %lluULL >= i == %d\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) > u) {
		printf("failed test %d MINi(%d, %d): %lldLL == %lluULL > u == %uU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	if (MINi(i, u) != u) {
		printf("failed test %d MINi(%d, %d): %lldLL == %lluULL != u == %uU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	return 0;
}

int
_test_MAX_biggerint_smalleruint(int i, unsigned u) {
	if (MAXi(i, u) <= u) {
		printf("failed test %d MAXi(%d, %uU): %lldLL == %lluLLU <= u == %uU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	if (MAXi(i, u) < i) {
		printf("failed test %d MAXi(%d, %d): %lldLL == %lluLLU < i == %d\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	if (MAXi(i, u) != i) {
		printf("failed test %d MAXi(%d, %d): %lldLL == %lluLLU != i == %d\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	return 0;
}

int
_test_MIN_biggerulong_smallerint(unsigned long u, int i) {
	if (MINi(u, i) != i) {
		printf("failed test %d MINi(%luUL, %d): %lldLL == %lluLLU != i == %d\n", __LINE__, u, i, MINi(u, i), MINi(u, i), i);
	}
	return 0;
}

int
_test_MAX_biggerulong_smallerint(unsigned long u, int i) {
	if (MAXi(u, i) != u) {
		printf("failed test %d MAXi(%luUL, %d): %lldLL == %lluLLU != u == %luUL\n", __LINE__, u, i, MAXi(u, i), MAXi(u, i), u);
	}
	return 0;
}

int
_test_MIN_biggerullong_smallerint(unsigned long long u, int i) {
	/*if (MINi(u, i) >= u) {
		printf("failed test %d as expected, MINi(%lluULL, %d): %lldLL == %lluULL >= u == %lluLLU\n", __LINE__, u, i, MINi(u, i), MINi(u, i), u);
	}*/
	if (MINi(u, i) != i) {
		printf("failed test %d MINi(%lluULL, %d): %lldLL == %lluULL != i == %uU\n", __LINE__, u, i, MINi(u, i), MINi(u, i), i);
	}
	return 0;
}

int
_test_MAX_biggerullong_smallerint(unsigned long long u, int i) {
	/*if (MAXi(u, i) <= i) {
		printf("failed test %d as expected MAXi(%lluULL, %d): %lldLL == %lluULL <= i == %d\n", __LINE__, u, i, MAXi(u, i), MAXi(u, i), i);
	}*/
	if (MAXi(u, i) != u) {
		printf("failed test %d MAXi(%lluULL, %d): %lldLL == %lluULL != u == %lluULL\n", __LINE__, u, i, MAXi(u, i), MAXi(u, i), u);
	}
	return 0;
}

int
_test_MIN_biggerlong_smallerulong(long i, unsigned long u) {
	if (MINi(i, u) <= -1) {
		printf("failed test %d MINi(%ld, %luLU): %lldLL == %lluULL <= -1 == %d == %uU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), -1, -1);
	}
	if (MINi(i, u) >= i) {
		printf("failed test %d MINi(%ld, %luLU): %lldLL == %lluULL >= i == %ld\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) > u) {
		printf("failed test %d MINi(%ld, %luLU): %lldLL == %lluULL > u == %luLU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	if (MINi(i, u) != u) {
		printf("failed test %d MINi(%ld, %luLU): %lldLL == %lluULL != u == %luLU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	return 0;
}

int
_test_MAX_biggerlong_smallerulong(long i, unsigned long u) {
	if (MAXi(i, u) <= u) {
		printf("failed test %d MAXi(%ld, %luLU): %lldLL == %lluLLU <= u == %luLU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	if (MAXi(i, u) < i) {
		printf("failed test %d MAXi(%ld, %ldL): %lldLL == %lluLLU < i == %ldL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	if (MAXi(i, u) != i) {
		printf("failed test %d MAXi(%ld, %ldL): %lldLL == %lluLLU != i == %ldL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	return 0;
}

int
_test_MIN_biggerlong_smallerullong(long i, unsigned long long u) {
	if (MINi(i, u) <= -1) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL <= -1 == %d == %u\n", __LINE__, i, u, MINi(i, u), MINi(i, u), -1, -1);
	}
	if (MINi(i, u) >= i) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL >= i == %ld\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if ((unsigned long long)MINi(i, u) > u) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL > u == %lluLLU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	if ((unsigned long long)MINi(i, u) != u) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL != u == %lluLLU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	return 0;
}

int
_test_MAX_biggerlong_smallerullong(long i, unsigned long long u) {
	/*if (MAXi(i, u) <= -1) {
		printf("failed test %d as expected MAXi(%ld, %lluLLU): %ldL == %luUL <= -1 == %d == %u\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), -1, -1);
	}*/
	if (MAXi(i, u) <= u) {
		printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU <= u == %lluLLU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	if ((long)MAXi(i, u) < i) {
		printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU < i == %ldL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	if ((long)MAXi(i, u) != i) {
		printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU != i == %ldL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	return 0;
}

int
_test_MIN_smallerlong_biggerullong(long i, unsigned long long u) {
	if ((unsigned long long)MINi(i, u) >= u) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL >= u == %lluLLU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	if (MINi(i, u) < i) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL < i == %ldL\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) != i) {
		printf("failed test %d MINi(%ld, %lluLLU): %lldLL == %lluULL != i == %ldL\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	return 0;
}

int
_test_MAX_smallerlong_biggerullong(long i, unsigned long long u) {
	if (MAXi(i, u) < 0) {
		printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU < 0\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u));
	}
	if (i >= 0) {
		if (MAXi(i, u) < (unsigned long long)i) {
			printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU < i == %ldL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
		}
	}
	if (MAXi(i, u) < u) {
		printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU < u == %lluLLU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	if (MAXi(i, u) != u) {
		printf("failed test %d MAXi(%ld, %lluLLU): %lldLL == %lluLLU != u == %lluLLU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	return 0;
}

int
_test_MIN_equalint_equaluint(int i, unsigned u) {
	if (MINi(i, u) != i) {
		printf("failed test %d MINi(%d, %d): %lldLL == %lluULL != i == %d\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) != u) {
		printf("failed test %d MINi(%d, %d): %lldLL == %lluULL != u == %uU\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	return 0;
}

int
_test_MAX_equalint_equaluint(int i, unsigned u) {
	if (MAXi(i, u) != i) {
		printf("failed test %d MAXi(%d, %d): %lldLL == %lluLLU != i == %d\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	if (MAXi(i, u) != u) {
		printf("failed test %d MAXi(%d, %d): %lldLL == %lluLLU != u == %uU\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	return 0;
}

int
_test_MIN_equallong_equalulong(long i, unsigned long u) {
	if (MINi(i, u) != i) {
		printf("failed test %d MINi(%ld, %ld): %lldLL == %lluULL != i == %ldL\n", __LINE__, i, u, MINi(i, u), MINi(i, u), i);
	}
	if (MINi(i, u) != u) {
		printf("failed test %d MINi(%ld, %ld): %lldLL == %lluULL != u == %luUL\n", __LINE__, i, u, MINi(i, u), MINi(i, u), u);
	}
	return 0;
}

int
_test_MAX_equallong_equalulong(long i, unsigned long u) {
	if (MAXi(i, u) != i) {
		printf("failed test %d MAXi(%ld, %ld): %lldLL == %lluLLU != i == %ldL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), i);
	}
	if (MAXi(i, u) != u) {
		printf("failed test %d MAXi(%ld, %ld): %lldLL == %lluLLU != u == %luUL\n", __LINE__, i, u, MAXi(i, u), MAXi(i, u), u);
	}
	return 0;
}

int
_test_MIN_hugeullong_hugerullong(unsigned long long u1, unsigned long long u2) {
	/* XXX actually the following casts to (unsigned long long) are cheating -- C standard doesn't guarantee that we'll get the right answer here. */
	if ((unsigned long long)MINi(u1, u2) >= u2) {
		printf("failed test %d MINi(%lluULL, %lluULL): %lldLL == %lluULL >= u2 == %lluULL\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2), u2);
	}
	if ((unsigned long long)MINi(u1, u2) > u1) {
		printf("failed test %d MINi(%lluULL, %lluULL): %lldLL == %lluULL > u1 == %lluULL\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2), u1);
	}
	if ((unsigned long long)MINi(u1, u2) != u1) {
		printf("failed test %d MINi(%lluULL, %lluULL): %lldLL == %lluULL != u1 == %lluULL\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2), u1);
	}
	return 0;
}

int
_test_MAX_hugeullong_hugerullong(unsigned long long u1, unsigned long long u2) {
	if (MAXi(u1, u2) < 0) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL < 0\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2));
	}
	if (MAXi(u1, u2) <= u1) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL <= u1 == %lluULL\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2), u1);
	}
	if (MAXi(u1, u2) > u2) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL > u2 == %lluULL\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2), u2);
	}
	if (MAXi(u1, u2) != u2) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL != u2 == %lluULL\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2), u2);
	}
	return 0;
}

int
_test_MIN_hugerullong_hugeullong(unsigned long long u1, unsigned long long u2) {
	/*if (MINi(u1, u2) < 0) {
		printf("failed test %d as expected MINi(%lluULL, %lluULL): %lldLL == %lluULL < 0\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2));
	}*/
	/* XXX actually the following casts to (unsigned long long) are cheating -- C standard doesn't guarantee that we'll get the right answer here. */
	if ((unsigned long long)MINi(u1, u2) >= u1) {
		printf("failed test %d MINi(%lluULL, %lluULL): %lldLL == %lluULL >= u1 == %lluULL\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2), u1);
	}
	printf("about to min %lluULL, %lluULL\n", u1, u2);
	if ((unsigned long long)MINi(u1, u2) > u2) {
		printf("failed test %d MINi(%lluULL, %lluULL): %lldLL == %lluULL > u2 == %lluULL\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2), u2);
	}
	printf("done with min %lluULL, %lluULL\n", u1, u2);
	if ((unsigned long long)MINi(u1, u2) != u2) {
		printf("failed test %d MINi(%lluULL, %lluULL): %lldLL == %lluULL != u2 == %lluULL\n", __LINE__, u1, u2, MINi(u1, u2), MINi(u1, u2), u2);
	}
	return 0;
}

int
_test_MAX_hugerullong_hugeullong(unsigned long long u1, unsigned long long u2) {
	if (MAXi(u1, u2) < 0) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL < 0\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2));
	}
	if (MAXi(u1, u2) <= u2) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL <= u2 == %lluULL\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2), u2);
	}
	if (MAXi(u1, u2) > u1) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL > u1 == %lluULL\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2), u1);
	}
	if (MAXi(u1, u2) != u1) {
		printf("failed test %d MAXi(%lluULL, %lluULL): %lldLL == %lluULL != u1 == %lluULL\n", __LINE__, u1, u2, MAXi(u1, u2), MAXi(u1, u2), u1);
	}
	return 0;
}

int
_test_various_MIN_smallerint_biggeruint() {
	_test_MIN_smallerint_biggeruint(-1, 0);
	_test_MIN_smallerint_biggeruint(-1, 1);
	_test_MIN_smallerint_biggeruint(-1, UINT_MAX);

	_test_MIN_smallerint_biggeruint(0, 1);
	_test_MIN_smallerint_biggeruint(0, 2);
	_test_MIN_smallerint_biggeruint(0, UINT_MAX);

	_test_MIN_smallerint_biggeruint(1, 2);
	_test_MIN_smallerint_biggeruint(1, 3);
	_test_MIN_smallerint_biggeruint(1, UINT_MAX);

	_test_MIN_smallerint_biggeruint(INT_MIN, 0);
	_test_MIN_smallerint_biggeruint(INT_MIN, 2);
	_test_MIN_smallerint_biggeruint(INT_MIN, UINT_MAX);
	_test_MIN_smallerint_biggeruint(INT_MIN, UINT_MIN);

	return 0;
}

int
_test_various_MAX_smallerint_biggeruint() {
	_test_MAX_smallerint_biggeruint(-1, 0);
	_test_MAX_smallerint_biggeruint(-1, 1);
	_test_MAX_smallerint_biggeruint(-1, UINT_MAX);

	_test_MAX_smallerint_biggeruint(0, 1);
	_test_MAX_smallerint_biggeruint(0, 2);
	_test_MAX_smallerint_biggeruint(0, UINT_MAX);

	_test_MAX_smallerint_biggeruint(1, 2);
	_test_MAX_smallerint_biggeruint(1, 3);
	_test_MAX_smallerint_biggeruint(1, UINT_MAX);

	_test_MAX_smallerint_biggeruint(INT_MIN, 0);
	_test_MAX_smallerint_biggeruint(INT_MIN, 2);
	_test_MAX_smallerint_biggeruint(INT_MIN, UINT_MAX);
	_test_MAX_smallerint_biggeruint(INT_MIN, UINT_MIN);

	return 0;
}

int
_test_various_MIN_smallerlong_biggerulong() {
	_test_MIN_smallerlong_biggerulong(-1, 0);
	_test_MIN_smallerlong_biggerulong(-1, 1);
	_test_MIN_smallerlong_biggerulong(-1, UINT_MAX);
	_test_MIN_smallerlong_biggerulong(-1, ULONG_MAX);

	_test_MIN_smallerlong_biggerulong(0, 1);
	_test_MIN_smallerlong_biggerulong(0, 2);
	_test_MIN_smallerlong_biggerulong(0, UINT_MAX);
	_test_MIN_smallerlong_biggerulong(0, ULONG_MAX);

	_test_MIN_smallerlong_biggerulong(1, 2);
	_test_MIN_smallerlong_biggerulong(1, 3);
	_test_MIN_smallerlong_biggerulong(1, UINT_MAX);
	_test_MIN_smallerlong_biggerulong(1, ULONG_MAX);

	_test_MIN_smallerlong_biggerulong(INT_MIN, 0);
	_test_MIN_smallerlong_biggerulong(INT_MIN, 2);
	_test_MIN_smallerlong_biggerulong(INT_MIN, UINT_MAX);
	_test_MIN_smallerlong_biggerulong(INT_MIN, ULONG_MAX);
	_test_MIN_smallerlong_biggerulong(INT_MIN, UINT_MIN);
	_test_MIN_smallerlong_biggerulong(INT_MIN, ULONG_MIN);

	_test_MIN_smallerlong_biggerulong(LONG_MIN, 0);
	_test_MIN_smallerlong_biggerulong(LONG_MIN, 2);
	_test_MIN_smallerlong_biggerulong(LONG_MIN, UINT_MAX);
	_test_MIN_smallerlong_biggerulong(LONG_MIN, ULONG_MAX);
	_test_MIN_smallerlong_biggerulong(LONG_MIN, UINT_MIN);
	_test_MIN_smallerlong_biggerulong(LONG_MIN, ULONG_MIN);

	return 0;
}

int
_test_various_MAX_smallerlong_biggerulong() {
	_test_MAX_smallerlong_biggerulong(-1, 0);
	_test_MAX_smallerlong_biggerulong(-1, 1);
	_test_MAX_smallerlong_biggerulong(-1, UINT_MAX);
	_test_MAX_smallerlong_biggerulong(-1, ULONG_MAX);

	_test_MAX_smallerlong_biggerulong(0, 1);
	_test_MAX_smallerlong_biggerulong(0, 2);
	_test_MAX_smallerlong_biggerulong(0, UINT_MAX);
	_test_MAX_smallerlong_biggerulong(0, ULONG_MAX);

	_test_MAX_smallerlong_biggerulong(1, 2);
	_test_MAX_smallerlong_biggerulong(1, 3);
	_test_MAX_smallerlong_biggerulong(1, UINT_MAX);
	_test_MAX_smallerlong_biggerulong(1, ULONG_MAX);

	_test_MAX_smallerlong_biggerulong(INT_MIN, 0);
	_test_MAX_smallerlong_biggerulong(INT_MIN, 2);
	_test_MAX_smallerlong_biggerulong(INT_MIN, UINT_MAX);
	_test_MAX_smallerlong_biggerulong(INT_MIN, ULONG_MAX);
	_test_MAX_smallerlong_biggerulong(INT_MIN, UINT_MIN);
	_test_MAX_smallerlong_biggerulong(INT_MIN, ULONG_MIN);

	_test_MAX_smallerlong_biggerulong(LONG_MIN, 0);
	_test_MAX_smallerlong_biggerulong(LONG_MIN, 2);
	_test_MAX_smallerlong_biggerulong(LONG_MIN, UINT_MAX);
	_test_MAX_smallerlong_biggerulong(LONG_MIN, ULONG_MAX);
	_test_MAX_smallerlong_biggerulong(LONG_MIN, UINT_MIN);
	_test_MAX_smallerlong_biggerulong(LONG_MIN, ULONG_MIN);

	return 0;
}

int
_test_various_MIN_biggerint_smalleruint() {
	_test_MIN_biggerint_smalleruint(1, 0);
	_test_MIN_biggerint_smalleruint(2, 0);
	_test_MIN_biggerint_smalleruint(INT_MAX, 0);

	_test_MIN_biggerint_smalleruint(3, 2);

	_test_MIN_biggerint_smalleruint(INT_MAX, INT_MAX-1);
	_test_MIN_biggerint_smalleruint(INT_MAX-1, INT_MAX-2);

	return 0;
}

int
_test_various_MAX_biggerint_smalleruint() {
	_test_MAX_biggerint_smalleruint(1, 0);
	_test_MAX_biggerint_smalleruint(2, 0);
	_test_MAX_biggerint_smalleruint(INT_MAX, 0);

	_test_MAX_biggerint_smalleruint(3, 2);

	_test_MAX_biggerint_smalleruint(INT_MAX, INT_MAX-1);
	_test_MAX_biggerint_smalleruint(INT_MAX-1, INT_MAX-2);

	return 0;
}

int
_test_various_MIN_biggerlong_smallerulong() {
	_test_MIN_biggerlong_smallerulong(1, 0);
	_test_MIN_biggerlong_smallerulong(2, 0);
	_test_MIN_biggerlong_smallerulong(INT_MAX, 0);
	_test_MIN_biggerlong_smallerulong(LONG_MAX, 0);

	_test_MIN_biggerlong_smallerulong(3, 2);

	_test_MIN_biggerlong_smallerulong(LONG_MAX, LONG_MAX-1);
	_test_MIN_biggerlong_smallerulong(LONG_MAX-1, LONG_MAX-2);
	_test_MIN_biggerlong_smallerulong(INT_MAX, INT_MAX-1);
	_test_MIN_biggerlong_smallerulong(INT_MAX-1, INT_MAX-2);

	return 0;
}

int
_test_various_MAX_biggerlong_smallerulong() {
	_test_MAX_biggerlong_smallerulong(1, 0);
	_test_MAX_biggerlong_smallerulong(2, 0);
	_test_MAX_biggerlong_smallerulong(INT_MAX, 0);
	_test_MAX_biggerlong_smallerulong(LONG_MAX, 0);

	_test_MAX_biggerlong_smallerulong(3, 2);

	_test_MAX_biggerlong_smallerulong(LONG_MAX, LONG_MAX-1);
	_test_MAX_biggerlong_smallerulong(LONG_MAX-1, LONG_MAX-2);
	_test_MAX_biggerlong_smallerulong(INT_MAX, INT_MAX-1);
	_test_MAX_biggerlong_smallerulong(INT_MAX-1, INT_MAX-2);

	return 0;
}

int
_test_various_MIN_biggerlong_smallerullong() {
	_test_MIN_biggerlong_smallerullong(1, 0);
	_test_MIN_biggerlong_smallerullong(2, 0);
	_test_MIN_biggerlong_smallerullong(INT_MAX, 0);
	_test_MIN_biggerlong_smallerullong(LONG_MAX, 0);

	_test_MIN_biggerlong_smallerullong(3, 2);

	_test_MIN_biggerlong_smallerullong(LONG_MAX, LONG_MAX-1);
	_test_MIN_biggerlong_smallerullong(LONG_MAX-1, LONG_MAX-2);
	_test_MIN_biggerlong_smallerullong(INT_MAX, INT_MAX-1);
	_test_MIN_biggerlong_smallerullong(INT_MAX-1, INT_MAX-2);

	return 0;
}

int
_test_various_MAX_biggerlong_smallerullong() {
	_test_MAX_biggerlong_smallerullong(1, 0);
	_test_MAX_biggerlong_smallerullong(2, 0);
	_test_MAX_biggerlong_smallerullong(INT_MAX, 0);
	_test_MAX_biggerlong_smallerullong(LONG_MAX, 0);

	_test_MAX_biggerlong_smallerullong(3, 2);

	_test_MAX_biggerlong_smallerullong(LONG_MAX, LONG_MAX-1);
	_test_MAX_biggerlong_smallerullong(LONG_MAX-1, LONG_MAX-2);
	_test_MAX_biggerlong_smallerullong(INT_MAX, INT_MAX-1);
	_test_MAX_biggerlong_smallerullong(INT_MAX-1, INT_MAX-2);

	return 0;
}

int
_test_various_MIN_smallerlong_biggerullong() {
	_test_MIN_smallerlong_biggerullong(0, 10);
	_test_MIN_smallerlong_biggerullong(0, 20);
	_test_MIN_smallerlong_biggerullong(0, INT_MAX);
	_test_MIN_smallerlong_biggerullong(0, LONG_MAX);

	_test_MIN_smallerlong_biggerullong(2, 3);

	_test_MIN_smallerlong_biggerullong(LONG_MAX-1, LONG_MAX);
	_test_MIN_smallerlong_biggerullong(LONG_MAX-2, LONG_MAX-1);
	_test_MIN_smallerlong_biggerullong(INT_MAX-1, INT_MAX);
	_test_MIN_smallerlong_biggerullong(INT_MAX-2, INT_MAX-1);

	return 0;
}

int
_test_various_MAX_smallerlong_biggerullong() {
	_test_MAX_smallerlong_biggerullong(0, 1);
	_test_MAX_smallerlong_biggerullong(0, 2);
	_test_MAX_smallerlong_biggerullong(0, INT_MAX);
	_test_MAX_smallerlong_biggerullong(0, LONG_MAX);

	_test_MAX_smallerlong_biggerullong(2, 3);

	_test_MAX_smallerlong_biggerullong(LONG_MAX-1, LONG_MAX);
	_test_MAX_smallerlong_biggerullong(LONG_MAX-2, LONG_MAX-1);
	_test_MAX_smallerlong_biggerullong(INT_MAX-1, INT_MAX);
	_test_MAX_smallerlong_biggerullong(INT_MAX-2, INT_MAX-1);

	return 0;
}

int
_test_various_MIN_equalint_equaluint() {
	_test_MIN_equalint_equaluint(0, 0);
	_test_MIN_equalint_equaluint(1, 1);
	_test_MIN_equalint_equaluint(UINT_MIN, UINT_MIN);
	_test_MIN_equalint_equaluint(INT_MAX, INT_MAX);
	return 0;
}

int
_test_various_MAX_equalint_equaluint() {
	_test_MAX_equalint_equaluint(0, 0);
	_test_MAX_equalint_equaluint(1, 1);
	_test_MAX_equalint_equaluint(UINT_MIN, UINT_MIN);
	_test_MAX_equalint_equaluint(INT_MAX, INT_MAX);
	return 0;
}

int
_test_various_MIN_equallong_equalulong() {
	_test_MIN_equallong_equalulong(0, 0);
	_test_MIN_equallong_equalulong(1, 1);
	_test_MIN_equallong_equalulong(UINT_MIN, UINT_MIN);
	_test_MIN_equallong_equalulong(ULONG_MIN, ULONG_MIN);
	_test_MIN_equallong_equalulong(INT_MAX, INT_MAX);
	_test_MIN_equallong_equalulong(LONG_MAX, LONG_MAX);
	return 0;
}

int
_test_various_MAX_equallong_equalulong() {
	_test_MAX_equallong_equalulong(0, 0);
	_test_MAX_equallong_equalulong(1, 1);
	_test_MAX_equallong_equalulong(UINT_MIN, UINT_MIN);
	_test_MAX_equallong_equalulong(ULONG_MIN, ULONG_MIN);
	_test_MAX_equallong_equalulong(INT_MAX, INT_MAX);
	_test_MAX_equallong_equalulong(LONG_MAX, LONG_MAX);
	return 0;
}

int
_test_various_MIN_hugeullong_hugerullong() {
	_test_MIN_hugeullong_hugerullong(LLONG_MAX, LLONG_MAX+1LLU);
	_test_MIN_hugeullong_hugerullong(LLONG_MAX+1LLU, LLONG_MAX+2LLU);
	_test_MIN_hugeullong_hugerullong(ULLONG_MAX-1, ULLONG_MAX);

	return 0;
}

int
_test_various_MAX_hugeullong_hugerullong() {
	_test_MAX_hugeullong_hugerullong(LLONG_MAX, LLONG_MAX+1LLU);
	_test_MAX_hugeullong_hugerullong(LLONG_MAX+1LLU, LLONG_MAX+2LLU);
	_test_MAX_hugeullong_hugerullong(ULLONG_MAX-1, ULLONG_MAX);

	return 0;
}

int
_test_various_MIN_hugerullong_hugeullong() {
	_test_MIN_hugerullong_hugeullong(LLONG_MAX+1LLU, LLONG_MAX);
	_test_MIN_hugerullong_hugeullong(LLONG_MAX+2LLU, LLONG_MAX+1LLU);
	_test_MIN_hugerullong_hugeullong(ULLONG_MAX, ULLONG_MAX-1);

	return 0;
}

int
_test_various_MAX_hugerullong_hugeullong() {
	_test_MAX_hugerullong_hugeullong(LLONG_MAX+1LLU, LLONG_MAX);
	_test_MAX_hugerullong_hugeullong(LLONG_MAX+2LLU, LLONG_MAX+1LLU);
	_test_MAX_hugerullong_hugeullong(ULLONG_MAX, ULLONG_MAX-1);

	return 0;
}

int
_test_various_MIN_biggerulong_smallerint() {
	_test_MIN_biggerulong_smallerint(0, -1);

	return 0;
}

int
_test_various_MIN_biggerullong_smallerint() {
	_test_MIN_biggerullong_smallerint(0, -1);

	return 0;
}

int
_test_various_MAX_biggerulong_smallerint() {
	_test_MAX_biggerulong_smallerint(0, -1);

	return 0;
}

int
_test_various_MAX_biggerullong_smallerint() {
	_test_MAX_biggerullong_smallerint(0, -1);

	return 0;
}

int
test_MIN() {
	_test_various_MIN_smallerint_biggeruint();
	_test_various_MIN_smallerlong_biggerulong();
	_test_various_MIN_biggerint_smalleruint();
	_test_various_MIN_biggerlong_smallerulong();
	_test_various_MIN_biggerlong_smallerullong();
	_test_various_MIN_smallerlong_biggerullong();
	_test_various_MIN_equalint_equaluint();
	_test_various_MIN_equallong_equalulong();
	_test_various_MIN_hugeullong_hugerullong();
	_test_various_MIN_hugerullong_hugeullong();
	_test_various_MIN_biggerulong_smallerint();
	_test_various_MIN_biggerullong_smallerint();
	return 0;
}

/** This test was designed to exercise each branch of the conditional expressions in _FASTER_MAX_SAFE, hence the name "transparentbox". */
int
test_MAX_transparentbox() {
	signed char x = 0;
	signed char y = -1;
	unsigned long z = 0;
	signed char a = 1;
	unsigned long b = 2;
	/* 1, 1, x */
	if (MAXi(x, y) != x) {
		printf("failed test %d MAXi(%c, %c): %lldLL == %lluLLU != %c\n", __LINE__, x, y, MAXi(x, y), MAXi(x, y), x);
	}
	/* 1, 1, y */
	if (MAXi(y, x) != x) {
		printf("failed test %d MAXi(%c, %c): %lldLL == %lluLLU != %c\n", __LINE__, y, x, MAXi(y, x), MAXi(y, x), x);
	}
	/* 1, 0, 1 */
	if (MAXi(y, z) != z) {
		printf("failed test %d MAXi(%c, %luLU): %lldLL == %lluLLU != %luLU\n", __LINE__, y, z, MAXi(y, z), MAXi(y, z), z);
	}
	/* 1, 0, 0, x */
	if (MAXi(a, z) != a) {
		printf("failed test %d MAXi(%c, %luLU): %lldLL == %lluLLU != %c\n", __LINE__, a, z, MAXi(a, z), MAXi(a, z), a);
	}
	/* 1, 0, 0, y */
	if (MAXi(a, b) != b) {
		printf("failed test %d MAXi(%c, %luLU): %lldLL == %lluLLU != %luLU\n", __LINE__, a, b, MAXi(a, b), MAXi(a, b), b);
	}
	/* 0, 1, 1 */
	if (MAXi(z, y) != z) {
		printf("failed test %d MAXi(%luLU, %c): %lldLL == %lluLLU != %luLU\n", __LINE__, z, y, MAXi(z, y), MAXi(z, y), z);
	}
	/* 0, 1, 0, x */
	if (MAXi(b, a) != b) {
		printf("failed test %d MAXi(%luLU, %c): %lldLL == %lluLLU != %luLU\n", __LINE__, b, a, MAXi(b, a), MAXi(b, a), b);
	}
	/* 0, 1, 0, y */
	if (MAXi(z, a) != a) {
		printf("failed test %d MAXi(%luLU, %c): %lldLL == %lluLLU != %c\n", __LINE__, z, a, MAXi(z, a), MAXi(z, a), a);
	}
	/* 0, 0, x */
	if (MAXi(b, z) != b) {
		printf("failed test %d MAXi(%luLU, %luLU): %lldLL == %lluLLU != %luLU\n", __LINE__, b, z, MAXi(b, z), MAXi(b, z), b);
	}
	/* 0, 0, y */
	if (MAXi(z, b) != b) {
		printf("failed test %d MAXi(%luLU, %luLU): %lldLL == %lluLLU != %luLU\n", __LINE__, z, b, MAXi(z, b), MAXi(z, b), b);
	}
	return 0;
}

void
test_MAX() {
	test_MAX_transparentbox();
	_test_various_MAX_smallerint_biggeruint();
	_test_various_MAX_smallerlong_biggerulong();
	_test_various_MAX_biggerint_smalleruint();
	_test_various_MAX_biggerlong_smallerulong();
	_test_various_MAX_biggerlong_smallerullong();
	_test_various_MAX_smallerlong_biggerullong();
	_test_various_MAX_equalint_equaluint();
	_test_various_MAX_equallong_equalulong();
	_test_various_MAX_hugeullong_hugerullong();
	_test_various_MAX_hugerullong_hugeullong();
	_test_various_MAX_biggerulong_smallerint();
	_test_various_MAX_biggerullong_smallerint();
}

void
test_exhausterr() {
	CHECKMALLOC((const char*const)malloc(UINT_MAX));
}

int
test_morelimits() {
#if 0 /* alas, the Z_foo_MAX macros can't be used in #if expressions.  This makes them unsuitable for use as LONG_MAX values, according to xxx draco */
#if Z_LONG_MAX == LONG_MAX
#error error in morelimits macro
#endif
#if Z_ULONG_MAX == ULONG_MAX
#error error in morelimits macro
#endif
#if Z_LLONG_MAX == LLONG_MAX
#error error in morelimits macro
#endif
#if Z_ULLONG_MAX == ULLONG_MAX
#error error in morelimits macro
#endif
#endif
	assert (TIME_T_MAX > TIME_T_MIN);
	assert (SIZE_T_MAX > SIZE_T_MIN);

	assert (Z_ULLONG_MAX == ULLONG_MAX);
	assert (Z_ULONG_MAX == ULONG_MAX);
	assert (Z_UINT_MAX == UINT_MAX);
	assert (Z_USHRT_MAX == USHRT_MAX);
	assert (Z_UCHAR_MAX == UCHAR_MAX);
	assert (Z_LLONG_MAX == LLONG_MAX);
	assert (Z_LONG_MAX == LONG_MAX);
	assert (Z_INT_MAX == INT_MAX);
	assert (Z_SHRT_MAX == SHRT_MAX);
	assert (Z_CHAR_MAX == CHAR_MAX);
	assert (Z_LLONG_MIN == LLONG_MIN);
	assert (Z_LONG_MIN == LONG_MIN);
	assert (Z_INT_MIN == INT_MIN);
	assert (Z_SHRT_MIN == SHRT_MIN);
	assert (Z_CHAR_MIN == CHAR_MIN);
	assert (Z_SCHAR_MAX == SCHAR_MAX);
	assert (Z_SCHAR_MIN == SCHAR_MIN);

	assert (Z_UINT8_MAX <= UCHAR_MAX);
	assert (Z_UINT8_MAX > 0);
	assert (Z_UINT8_MAX < USHRT_MAX);

	assert (Z_UINT16_MAX > 0);
	assert (Z_UINT16_MAX <= USHRT_MAX);

	assert (Z_UINT32_MAX <= Z_ULONG_MAX);
	assert (Z_UINT32_MAX <= Z_ULONG_MAX);
	assert (Z_UINT32_MAX > 0);
	assert (Z_UINT32_MAX == ((1LLU << 32) - 1));

	assert (Z_UINT64_MAX >= 0);
	assert (Z_UINT64_MAX == ((1LLU << 63) + ((1LLU << 63) - 1)));

	return 0;
}

void
print_morelimits() {
	printf("Z_MAX_VOIDP:                   %40llu\n", Z_MAX_VOIDP);
	printf("Z_MAX_UNSIGNED_typ(unsigned char): %36u\n", Z_MAX_UNSIGNED_typ(unsigned char));
	printf("Z_MAX_SIGNED_typ(char):            %36d\n", Z_MAX_SIGNED_typ(char));
	printf("\n");
	printf("Z_SIZE_T_MAX:                  %40zu\n", Z_SIZE_T_MAX);
	printf("SIZE_T_MAX:                    %40zu\n", SIZE_T_MAX);
	printf("\n");
	printf("Z_SIZE_T_MIN:                  %40zu\n", Z_SIZE_T_MIN);
	printf("SIZE_T_MIN:                    %40zu\n", SIZE_T_MIN);
	printf("\n");
	printf("Z_TIME_T_MAX:                  %40ld\n", Z_TIME_T_MAX);
	printf("TIME_T_MAX:                    %40ld\n", TIME_T_MAX);
	printf("\n");
	printf("Z_TIME_T_MIN:                  %40ld\n", Z_TIME_T_MIN);
	printf("TIME_T_MIN:                    %40ld\n", TIME_T_MIN);
	printf("\n");
	printf("UCHAR_MAX:                     %40u\n", UCHAR_MAX);
	printf("Z_UCHAR_MAX:                   %40u\n", Z_UCHAR_MAX);
	printf("\n");
	printf("USHRT_MAX:                     %40u\n", USHRT_MAX);
	printf("Z_USHRT_MAX:                   %40u\n", Z_USHRT_MAX);
	printf("\n");
	printf("UINT_MAX:                      %40u\n", UINT_MAX);
	printf("Z_UINT_MAX:                    %40u\n", Z_UINT_MAX);
	printf("\n");
	printf("ULONG_MAX:                     %40lu\n", ULONG_MAX);
	printf("Z_ULONG_MAX:                   %40lu\n", Z_ULONG_MAX);
	printf("\n");
	printf("ULLONG_MAX:                    %40llu\n", ULLONG_MAX);
	printf("Z_ULLONG_MAX:                  %40llu\n", Z_ULLONG_MAX);
	printf("\n");
	printf("UCHAR_MIN:                     %40u\n", UCHAR_MIN);
	printf("USHRT_MIN:                     %40u\n", USHRT_MIN);
	printf("UINT_MIN:                      %40u\n", UINT_MIN);
	printf("ULONG_MIN:                     %40lu\n", ULONG_MIN);
	printf("ULLONG_MIN:                    %40llu\n", ULLONG_MIN);
	printf("\n");
	printf("CHAR_MAX:                      %40d\n", CHAR_MAX);
	printf("Z_CHAR_MAX:                    %40d\n", Z_CHAR_MAX);
	printf("\n");
	printf("SHRT_MAX:                      %40d\n", SHRT_MAX);
	printf("Z_SHRT_MAX:                    %40d\n", Z_SHRT_MAX);
	printf("\n");
	printf("INT_MAX:                       %40d\n", INT_MAX);
	printf("Z_INT_MAX:                     %40d\n", Z_INT_MAX);
	printf("\n");
	printf("LONG_MAX:                      %40ld\n", LONG_MAX);
	printf("Z_LONG_MAX:                    %40ld\n", Z_LONG_MAX);
	printf("\n");
	printf("LLONG_MAX:                     %40lld\n", LLONG_MAX);
	printf("Z_LLONG_MAX:                   %40lld\n", Z_LLONG_MAX);
	printf("\n");
	printf("CHAR_MIN:                      %40d\n", CHAR_MIN);
	printf("Z_CHAR_MIN:                    %40d\n", Z_CHAR_MIN);
	printf("\n");
	printf("SHRT_MIN:                      %40d\n", SHRT_MIN);
	printf("Z_SHRT_MIN:                    %40d\n", Z_SHRT_MIN);
	printf("\n");
	printf("INT_MIN:                       %40d\n", INT_MIN);
	printf("Z_INT_MIN:                     %40d\n", Z_INT_MIN);
	printf("\n");
	printf("LONG_MIN:                      %40ld\n", LONG_MIN);
	printf("Z_LONG_MIN:                    %40ld\n", Z_LONG_MIN);
	printf("\n");
	printf("LLONG_MIN:                     %40lld\n", LLONG_MIN);
	printf("Z_LLONG_MIN:                   %40lld\n", Z_LLONG_MIN);
	printf("\n");
	printf("Z_UINT8_MAX:                   %40u\n", Z_UINT8_MAX);
	printf("Z_UINT16_MAX:                  %40u\n", Z_UINT16_MAX);
	printf("Z_UINT32_MAX:                  %40lu\n", Z_UINT32_MAX);
	printf("Z_UINT64_MAX:                  %40llu\n", Z_UINT64_MAX);
}

int
test() {
	/*print_morelimits();*/
	test_overflow();
	test_nextmult();
	test_uint32_encode();
	test_uint64_encode();
	test_FITS_INTO_INT();
	test_FITS_INTO_LONG();
	test_FITS_INTO_LLONG();
	test_PROMOTES_TO_SIGNED_TYPE();
	test_generic_ADD_WOULD_OVERFLOW();
	test_specific_add_would_overflow();
	test_morelimits();
	/*test_MIN_crazybadargs();*/
	test_MIN();
	test_MAX();
	test_minmax_fast();
	/*
	 * To test handling of memory exhaustion, you have to #define Z_EXHAUST_EXIT before #include'ing zutil.h.
	test_exhausterr();
 	 */
	return 0;
}

int
bench() {
	int i;
	for (i=0; i<20000000;i++) {
		test_MAX();
	}
	return 0;
}

int
main(int argv, char**argc) {
	return test();
}

/*int main(int argv, char**argc) {
	bench_uint32_encode();
	return 1;
	}*/
