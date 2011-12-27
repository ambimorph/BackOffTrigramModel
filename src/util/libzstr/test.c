/**
 * copyright 2002-2004 Bryce "Zooko" Wilcox-O'Hearn
 * mailto:zooko@zooko.com
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this work to deal in this work without restriction (including the rights
 * to use, modify, distribute, sublicense, and/or sell copies).
 */
#include "zstr.h"
#include "moreassert.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int test_czstr_manual() {
	zstr a = cs_as_z("abcdefgh");
	czstr b = { a.len, a.buf };
	printf("%d:%s\n", b.len, b.buf);
	return 0;
}

int test_czstr_union_cast_manual() {
	zstr a;
	czstr b;
	z_union_zstr_czstr u;
	a = cs_as_z("abcdefgh");
	u.z = a;
	b = u.c;
	printf("%d:%s\n", b.len, b.buf);
	return 0;
}

const static size_t B1SIZE=4096;
const static size_t B2SIZE=128;

unsigned zstrstr_1_pass() {
	unsigned acc = 0;
	FILE* f = fopen("/usr/share/dict/words", "r");
	char buf1[B1SIZE+1];
	char buf2[B2SIZE+1];
	czstr z1, z2;
	czstr resz;

	while (! feof(f)) {
		size_t siz1 = random() % B1SIZE;
		size_t siz2 = random() % B2SIZE;
		buf1[0] = '\0';
		siz1 = fread(buf1, 1, siz1, f);
		buf1[siz1] = '\0';
		z1 = (czstr){ siz1, (const zbyte*)buf1 };

		buf2[0] = '\0';
		siz2 = fread(buf2, 1, siz2, f);
		buf2[siz2] = '\0';
		z2 = (czstr){ siz2, (const zbyte*)buf2 };

/*		res = strstr(z1.buf, z2.buf);
                if (res != NULL) {
                    acc++;
                }*/

		resz = zstrstr(z1, z2);
		if (resz.len != 0) {
			acc++;
		}
/*              
               if (res != resz.buf) {
                    printf("ERROR\n");
                    printf("z1: %llu:%s; z2: %llu:%s\n", (unsigned long long)z1.len, z1.buf, (unsigned long long)z2.len, z2.buf);
                    printf("%p->%s, %p->%s\n", res, res, resz.buf, resz.buf);
                    exit(1);
                }*/
	}

	fclose(f);
	/*printf("found %u hits.  Most recent hit: %llu, %s, %llu, %s, %s\n", acc, (unsigned long long)z1.len, z1.buf, (unsigned long long)z2.len, z2.buf, hit);*/
	/*printf("found %u hits.  Most recent hit: siz1 %llu, siz2 %llu, index %llu\n", acc, (unsigned long long)z1.len, (unsigned long long)z2.len, (unsigned long long)(hit - z1.buf));*/

	return acc;
}

const static unsigned REPS=512;

void bench_zstrstr() {
	unsigned long acc = 0;
	unsigned int i;
	for (i = 0; i < REPS; i++)
		acc += zstrstr_1_pass();
	printf("total hits: %lu\n", acc);
}

int test_zstrstr() {
	czstr a = cs_as_cz("abcdefh");
	czstr b = cs_as_cz("abcdefh");
	runtime_assert4 (zstrstr(a, b).buf == a.buf, "f", zstrstr(a, b).buf, "s", a.buf);
	assert ((const char*)zstrstr(a, b).buf == strstr(a.buf, b.buf));
	assert (zstrstr(a, a).buf == a.buf);
	assert ((const char*)zstrstr(a, a).buf == strstr(a.buf, a.buf));

	czstr c = cs_as_cz("abcdefhi");
	assert ((const char*)zstrstr(a, c).buf == NULL);
	assert ((const char*)zstrstr(a, c).buf == strstr(a.buf, c.buf));

	czstr d = cs_as_cz("bcdefh");
	assert (zstrstr(a, d).buf == a.buf+1);
	assert ((const char*)zstrstr(a, d).buf == strstr(a.buf, d.buf));

	czstr e = cs_as_cz("bcdef");
	assert (zstrstr(a, e).buf == a.buf+1);
	assert ((const char*)zstrstr(a, e).buf == strstr(a.buf, e.buf));

	czstr a2 = cs_as_cz("bcdef bcdef bcdef abcde abcde abcde bcdef abcdef bcdef");
	runtime_assert4 ((const char*)zstrstr(a2, a).buf == strstr(a2.buf, a.buf), "f", zstrstr(a2, a).buf, "s", strstr(a2.buf, a.buf));

	czstr a3 = cs_as_cz("bcdef bcdef bcdef abcde abcde abcde bcdef abcdef bcdef abcdef");
	czstr b2 = cs_as_cz("abcdef");
	/*printf("%s, %llu, %s, %llu\n", zstrstr(a2, b2).buf, (unsigned long long)(zstrstr(a2, b2).buf-a2.buf), zstrstr(a3, b2).buf, (unsigned long long)(zstrstr(a3, b2).buf-a3.buf));*/
	runtime_assert4 ((zstrstr(a2, b2).buf-a2.buf) == (zstrstr(a3, b2).buf-a3.buf), "f", zstrstr(a2, b2).buf, "s", zstrstr(a3, b2).buf);
	assert ((const char*)zstrstr(a3, b2).buf == strstr(a3.buf, b2.buf));

	return 0;
}

int test_czstr() {
	zstr a = cs_as_z("abcdefgh");
	czstr b = cz(a);

	printf("%d:%s\n", b.len, b.buf);
	/*b.len = 5;*/ /* should be a compile error since b is const. */
	/*b.buf = NULL;*/ /* should be a compile error since b is const. */
	/*b.buf[0] = '\0';*/ /* should be a compile error since b is a czstr. */
	return 0;
}

int test_new_zstr_from_cs() {
	zstr z;
	size_t l;
	z = new_z_from_cs("testee");
	l = z.len;
	assert (l == z.len);
	return z.len;
}

int test_repr() {
	zstr z2;
	czstr z = cs_as_cz("k");
	zstr rz = repr(z);
	#ifndef NDEBUG
	const czstr a = cs_as_cz("\\\\k");
	#endif

	assert (!strcmp((const char*)rz.buf, "k"));

	z = cs_as_cz("\\k");
	assert (z.len == 2);
	free_z(rz);
	rz = repr(z);
	assert (rz.len == 3);
	assert (a.len == 3);
	assert (!strcmp((const char*)rz.buf, "\\\\k"));
	assert (zeq(cz(rz), a));

	z2 = new_z(4);
	z2.buf[0] = 1;
	z2.buf[1] = 10;
	z2.buf[2] = 100;
	z2.buf[3] = 252;

	free_z(rz);
	rz = repr(cz(z2));
	assert (!strcmp((const char*)rz.buf, "\\x01\\x0ad\\xfc"));

	free_z(z2);
	z2 = new_z(1);
	z2.buf[0] = '\0';

	free_z(rz);
	rz = repr(cz(z2));
	assert (!strcmp((const char*)rz.buf, "\\x00"));

	free_z(z2);
	free_z(rz);
	return 0;
}

/** This test requires manual intervention to provide an appropriate file to read and write. */
void test_stream() {
	FILE* fp = fopen("/tmp/opsec.p12", "r");
	FILE* fpo;
	zstr z1 = z_slurp_stream(fp);
	zstr z2;
	fpo = fopen("/tmp/opsec.p12.out", "w");
	cz_to_stream(cz(z1), fpo);
	fflush(fpo);
	fclose(fpo);
	z2 = z_slurp_stream(fopen("/tmp/opsec.p12.out", "r"));
	assert (zeq(cz(z1), cz(z2)));
}

void test_encode() {
	FILE* fp;
	czstr a = cs_as_cz("blah");
	zstr b;
	fp = fopen("/tmp/encode", "w");
	/*printf("len = %d\n", a.len);*/
	z_encode(a, fp);
	fclose(fp);
	fp = fopen("/tmp/encode", "r");
	b = z_decode(fp);
	fclose(fp);
	printf("b.len = %d, b.buf = %s\n", b.len, b.buf);	
}

int test() {
	/*test_czstr();*/
	/*test_stream();*/
	test_encode();
	test_zstrstr();
	test_repr();
	return 0;
}

int main(int argc, char**argv) {
	int seed = 0;
	if (argc >= 2) {
		seed = atol(argv[1]);
	}
	printf("seed %d\n", seed);
	srandom(seed);
	test();
	bench_zstrstr();
	return 0;
}

