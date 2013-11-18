#include "zutil.h"
#include "zstr.h"
#include "moreassert.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "BackOffTrigramModel.h"

const static size_t BUFSIZE=1024;

const static size_t TRAILER=1; /* 1 character to make sure that strtod terminates properly */

#define isUNK(ap, p) ((((ap)-(p))==5) && (memcmp((p), "<UNK>", 5) == 0 || memcmp((p), "<unk>", 5) == 0))


void
print_jt(Pvoid_t*const T) {
  PWord_t ptr;
  zbyte index[MAXTRIGRAMSIZE+1];
  zstr z;

  index[0] = '\0';
  JSLF(ptr, *T, index);
  while (ptr != NULL) {
      z = repr(cs_as_cz((char*)index));
      printf("%s\n", z.buf);
      free(z.buf);
      JSLG(ptr, *T, index);
      printf("%f\n", *(float*)ptr);
      JSLN(ptr, *T, index);
  }
}

void
_read_unigram(char**const pbuf, Pvoid_t*const P, Pvoid_t*const B) {
  assert (sizeof(Word_t) >= sizeof(float));

  float prob = strtod(*pbuf, (char**)pbuf);
  const char* wordp=(*pbuf)+1; /* pointer to the beginning of the word */
  char* afterwordp = strpbrk(wordp, " \t\n");
  assert (afterwordp != NULL);
  assert ((afterwordp - wordp) <= MAXUNIGRAMSIZE);
  float backoff;
  if (*afterwordp == '\n') {
    backoff = 0;
    *pbuf = afterwordp;
  }
  else {
    backoff = strtod(afterwordp, (char**)pbuf);
  }
  

  PWord_t ptr;

  if (isUNK(afterwordp, wordp)) {
    JSLI(ptr, *P, UNKBYTESTR);
    memcpy(ptr, &prob, sizeof(prob));
    JSLI(ptr, *B, UNKBYTESTR);
    memcpy(ptr, &backoff, sizeof(backoff));
  }
  else {
    char temp = *afterwordp;
    *afterwordp = '\0';
    JSLG(ptr, *P, (unsigned char*)wordp);
    assert (ptr == NULL);
    JSLI(ptr, *P, (unsigned char*)wordp);
    memcpy(ptr, &prob, sizeof(prob));
    JSLI(ptr, *B, (unsigned char*)wordp);
    memcpy(ptr, &backoff, sizeof(backoff));
    *afterwordp = temp;
  }
}

/* updates buf to point to the first unused char */
void
_read_bigram(char**const pbuf, Pvoid_t*const UP, Pvoid_t*const P, Pvoid_t*const B) {
  assert (sizeof(Word_t) >= sizeof(float));

  PWord_t ptr;

  float prob = strtod(*pbuf, pbuf);
  char* firstwordp=(*pbuf)+1; /* pointer to the beginning of the first word */
  char* afterfirstwordp = strpbrk(firstwordp, " \t");
  assert (afterfirstwordp != NULL);
  char tmp = *afterfirstwordp;
  *afterfirstwordp = '\0';
  JSLG(ptr, *P, (unsigned char*)firstwordp);
  assert (ptr == NULL);
  *afterfirstwordp = tmp;
  char* secondwordp = afterfirstwordp+1;
  char* aftersecondwordp = strpbrk(secondwordp, " \t\n");
  assert (aftersecondwordp != NULL);
  tmp = *aftersecondwordp;
  *aftersecondwordp = '\0';
  JSLG(ptr, *P, (unsigned char*)secondwordp);
  assert (ptr == NULL);
  *aftersecondwordp = tmp;
  assert ((aftersecondwordp - firstwordp) <= MAXBIGRAMSIZE);
  float backoff;
  if (tmp == '\n') {
    backoff = 0;
    *pbuf = aftersecondwordp;
  }
  else {
    backoff = strtod(aftersecondwordp, pbuf);
  }

  char buf[MAXBIGRAMSIZE+1]; /* +1 for null-terminating char */
  char* indexp = firstwordp;
  char* afterindexp = aftersecondwordp;

  if (isUNK(afterfirstwordp, firstwordp)) {
    indexp = buf;
    afterindexp = indexp;
    *afterindexp++ = UNKBYTESTR[0];
    *afterindexp++ = ' ';
    if (isUNK(aftersecondwordp, secondwordp)) {
      *afterindexp++ = UNKBYTESTR[0];
    }
    else {
      memcpy(afterindexp, secondwordp, aftersecondwordp-secondwordp);
      afterindexp = afterindexp + (aftersecondwordp-secondwordp);
    }
  }

  else if (isUNK(aftersecondwordp, secondwordp)) {
    /* First word was not <UNK>: */
    /* Must copy first word into buf. */
    memcpy(buf, firstwordp, secondwordp-firstwordp);
    indexp = buf;
    afterindexp = buf + (secondwordp-firstwordp);
    *afterindexp++ = UNKBYTESTR[0];
  }

  zbyte temp = *afterindexp;
  *afterindexp = '\0';
  JSLI(ptr, *P, (unsigned char*)indexp);
  memcpy(ptr, &prob, sizeof(prob));
  JSLI(ptr, *B, (unsigned char*)indexp);
  memcpy(ptr, &backoff, sizeof(backoff));
  *afterindexp = temp;

}

/* updates buf to point to the first unused char */
void
_read_trigram(char**const pbuf, Pvoid_t*const P) {
  assert (sizeof(Word_t) >= sizeof(float));

  float prob = strtod(*pbuf, pbuf);
  char* firstwordp=(*pbuf)+1; /* pointer to the beginning of the first word */
  char* afterfirstwordp = strpbrk(firstwordp, " \t");
  assert (afterfirstwordp != NULL);
  char* secondwordp = afterfirstwordp+1;
  char* aftersecondwordp = strpbrk(secondwordp, " \t");
  assert (aftersecondwordp != NULL);
  char* thirdwordp = aftersecondwordp+1;
  assert (thirdwordp != NULL);
  char* afterthirdwordp = strpbrk(thirdwordp, " \n");
  assert (afterthirdwordp != NULL);
  assert (*afterthirdwordp == '\n');
  assert ((afterthirdwordp - firstwordp) <= MAXTRIGRAMSIZE);

  char buf[MAXBIGRAMSIZE+1]; /* +1 for null-terminating char */
  char* indexp = firstwordp;
  char* afterindexp = afterthirdwordp;

  if (isUNK(afterfirstwordp, firstwordp)) {
    indexp = buf;
    afterindexp = indexp;
    *afterindexp++ = UNKBYTESTR[0];
    *afterindexp++ = ' ';
    if (isUNK(aftersecondwordp, secondwordp)) {
      *afterindexp++ = UNKBYTESTR[0];
      *afterindexp++ = ' ';
    }
    else {
      memcpy(afterindexp, secondwordp, aftersecondwordp-secondwordp);
      afterindexp = afterindexp + (aftersecondwordp-secondwordp);
      *afterindexp++ = ' ';
    }
    if (isUNK(afterthirdwordp, thirdwordp)) {
      *afterindexp++ = UNKBYTESTR[0];
    }
    else {
      memcpy(afterindexp, thirdwordp, afterthirdwordp-thirdwordp);
      afterindexp = afterindexp + (afterthirdwordp-thirdwordp);
    }
  }

  else if (isUNK(aftersecondwordp, secondwordp)) {
    /* First word was not <UNK>: */
    /* Must copy first word into buf. */
    memcpy(buf, firstwordp, secondwordp-firstwordp);
    indexp = buf;
    afterindexp = buf + (secondwordp-firstwordp);
    *afterindexp++ = UNKBYTESTR[0];
    *afterindexp++ = ' ';
    if (isUNK(afterthirdwordp, thirdwordp)) {
      *afterindexp++ = UNKBYTESTR[0];
    }
    else {
      memcpy(afterindexp, thirdwordp, afterthirdwordp-thirdwordp);
      afterindexp = afterindexp + (afterthirdwordp-thirdwordp);
    }
  }

  else if (isUNK(afterthirdwordp, thirdwordp)) {
    /* First and second words were not <UNK>: */
    /* Must copy first two words into buf. */
    memcpy(buf, firstwordp, thirdwordp-firstwordp);
    indexp = buf;
    afterindexp = buf + (thirdwordp-firstwordp);
    *afterindexp++ = UNKBYTESTR[0];
  }

  PWord_t ptr;
  zbyte temp = *afterindexp;
  *afterindexp = '\0';
  assert (strchr(indexp, '\n') == NULL);
  JSLI(ptr, *P, (unsigned char*)indexp);
  memcpy(ptr, &prob, sizeof(prob));
  *afterindexp = temp;
  assert (*afterthirdwordp == '\n');
  char* tmp = strchr(afterthirdwordp, '\n');
  assert (tmp != NULL);
  *pbuf = tmp + 1;
}

/* Read some more bytes from arpafile into buf.  Treat the span of  bytes from
 * *pbegindata (inclusive) to *pafterdata (exclusive) to be good data  which
 * gets moved over to the beginning of the buffer and appended to.  Update
 * *pbegindata and *pafterdata to show the new location of the span of good
 * data bytes. */
void
_refill_buf(char*const buf, char**const pbegindata, char**const pafterdata, FILE*const arpafile) {
  assert (runtime_assert(*pbegindata <= *pafterdata, "begindata is required to never point after afterdata.  This can happen if the .arpa input file is truncated or corrupted."));
  assert (runtime_assert(*pafterdata <= buf+BUFSIZE+1, "afterdata is required to never point past the end of the buffer"));
  size_t charsleft = *pafterdata - *pbegindata;
  if (*pbegindata < (buf+charsleft)) {
    memmove(buf, *pbegindata, charsleft);
  } else {
    memcpy(buf, *pbegindata, charsleft);
  }
  *pafterdata = buf + charsleft + fread(buf+charsleft, 1, BUFSIZE-charsleft, arpafile);
  *pbegindata = buf;
}

const char* PATTERN = "\n\\data\\\n";
const size_t PATTERNLEN = 8; /* BUFSIZE needs to be much larger than this. */
void
read_arpa_file(FILE*const arpafile, Pvoid_t*const pUP, Pvoid_t*const pUB, Pvoid_t*const pBP, Pvoid_t*const pBB, Pvoid_t*const pTP) {

  char buf[BUFSIZE];
  char* afterdata = buf; /* pointer to the first char in buf after the data */
  char* begindata = buf; /* pointer to the first char in buf containing data */
  char* pattern = NULL;
  _refill_buf(buf, &begindata, &afterdata, arpafile);
  do {
    pattern = strstr(buf, PATTERN);
    if (pattern != NULL)
      /* Then everything up to and including the pattern is useless. */
      begindata = pattern + PATTERNLEN;
    else
      /* Then all of the data up at most the last PATTERNLEN-1 bytes is useless. */
      begindata = afterdata - (PATTERNLEN-1);
    runtime_assert(begindata >= buf, "The arpafile is required to have a PATTERN before it comes to an end, but apparently it just ran out of bytes.");
    _refill_buf(buf, &begindata, &afterdata, arpafile);
  } while (pattern == NULL);

  runtime_assert(buf == begindata, "internal consistency check");

  char* p = begindata;

  p += 8; /* seek to beginning of unigram count */
  unsigned int numunigrams = strtoul(p, (char**)&p, 10);

  p += 9; /* go to beginning of bigram count */
  unsigned int numbigrams = strtoul(p, (char**)&p, 10);

  p += 9; /* go to the beginning of trigram count */
  unsigned int numtrigrams = strtoul(p, (char**)&p, 10);

  p += 11; /* go to the beginning of the list of unigrams */

  fprintf(stderr, "numunigrams: %u, numbigrams: %u, numtrigrams: %u\n", numunigrams, numbigrams, numtrigrams); fflush(stderr); /* debuggery */


  #ifndef NDEBUG
  const char* prevp = p;
  #endif
  unsigned int unigramsleft = numunigrams;

  while (unigramsleft > 0) {
    assert(p >= buf && p < buf+BUFSIZE); /* p always points somewhere in the buffer */
    assert((afterdata - p) >= (MAXUNIGRAMSIZE + TRAILER)); /* there is always some unconsumed data waiting in the buffer */

    _read_unigram(&p, pUP, pUB); /* updates p */
    unigramsleft--;
    #ifndef NDEBUG
    assert ((p - prevp) < MAXUNIGRAMSIZE);
    prevp = p;
    #endif
    if (p >= afterdata-MAXUNIGRAMSIZE-TRAILER) {
      _refill_buf(buf, &p, &afterdata, arpafile);
      #ifndef NDEBUG
      prevp = p;
      #endif
    }
  }
  fprintf(stderr, "Finished reading unigrams: %u\n", numunigrams); fflush(stderr);

  assert(p >= buf && p < buf+BUFSIZE); /* p always points somewhere in the buffer */
  assert((afterdata - p) >= (MAXUNIGRAMSIZE + TRAILER)); /* there is always some unconsumed data waiting in the buffer */
  p += 12; /* go to the beginning of the list of bigrams */

  if (p >= afterdata-MAXBIGRAMSIZE-TRAILER) {
    _refill_buf(buf, &p, &afterdata, arpafile);
    #ifndef NDEBUG
    prevp = p;
    #endif
  }

  unsigned int bigramsleft = numbigrams;
  while (bigramsleft > 0) {
    assert(p >= buf && p < buf+BUFSIZE); /* p always points somewhere in the buffer */
    /*printf("%s:%d afterdata-buf: %zu, p-buf %zu diff %lu, req: %lu, bigramsleft: %u\n", __func__, __LINE__, afterdata-buf, p-buf, (afterdata - p), (MAXBIGRAMSIZE + TRAILER), bigramsleft);*/
    assert((afterdata - p) >= (MAXBIGRAMSIZE + TRAILER)); /* there is always some unconsumed data waiting in the buffer */

    _read_bigram(&p, pUP, pBP, pBB); /* updates p */
    bigramsleft--;
    #ifndef NDEBUG
    assert ((p - prevp) < MAXBIGRAMSIZE);
    prevp = p;
    #endif
    if (p >= afterdata-MAXBIGRAMSIZE-TRAILER) {
      _refill_buf(buf, &p, &afterdata, arpafile);
      #ifndef NDEBUG
      prevp = p;
      #endif
    }
    assert(p >= buf && p < buf+BUFSIZE); /* p always points somewhere in the buffer */
    /*printf("%s:%d afterdata-buf: %zu, p-buf: %zu, diff %lu, req: %lu, bigramsleft: %u, %d\n", __func__, __LINE__, afterdata-buf, p-buf, (afterdata - p), (MAXBIGRAMSIZE + TRAILER), bigramsleft, __LINE__);*/
    assert((afterdata - p) >= (MAXBIGRAMSIZE + TRAILER)); /* there is always some unconsumed data waiting in the buffer */
  }
  fprintf(stderr, "Finished reading bigrams: %u\n", numbigrams); fflush(stderr);

  assert(p >= buf && p < buf+BUFSIZE); /* p always points somewhere in the buffer */
  assert((afterdata - p) >= (MAXBIGRAMSIZE + TRAILER)); /* there is always some unconsumed data waiting in the buffer */
  p += 12; /* go to the beginning of the list of trigrams */

  if (p >= afterdata-MAXTRIGRAMSIZE-TRAILER) {
    _refill_buf(buf, &p, &afterdata, arpafile);
    #ifndef NDEBUG
    prevp = p;
    #endif
  }

  unsigned int trigramsleft = numtrigrams;
  while (trigramsleft > 0) {
    assert(p >= buf && p < buf+BUFSIZE); /* p always points somewhere in the buffer */

    _read_trigram(&p, pTP); /* updates p */
    trigramsleft--;
    #ifndef NDEBUG
    assert ((p - prevp) < MAXTRIGRAMSIZE);
    prevp = p;
    #endif
    if (p >= afterdata-MAXTRIGRAMSIZE-TRAILER) {
      _refill_buf(buf, &p, &afterdata, arpafile);
      #ifndef NDEBUG
      prevp = p;
      #endif
    }
  }
  fprintf(stderr, "Finished reading trigrams: %u\n", numtrigrams); fflush(stderr);
}

double
unigram_prob_1(const zstr unigram, Pvoid_t* pUP) {
  PWord_t ptr;

  zbyte temp = unigram.buf[unigram.len];
  unigram.buf[unigram.len] = '\0';
  JSLG(ptr, *pUP, unigram.buf);
  unigram.buf[unigram.len] = temp;
  assert (ptr != NULL);
  return *(float*)ptr;
}

double
bigram_prob_2(const zstr bigram, const zstr unigram1, const zstr unigram2, Pvoid_t*const pUP, Pvoid_t*const pUB, Pvoid_t*const pBP) {
  PWord_t ptr;

  zbyte temp = bigram.buf[bigram.len];
  bigram.buf[bigram.len] = '\0';
  JSLG(ptr, *pBP, bigram.buf);
  bigram.buf[bigram.len] = temp;
  if (ptr != NULL) {
    return *(float*)ptr;
  }

  temp = unigram1.buf[unigram1.len];
  unigram1.buf[unigram1.len] = '\0';
  JSLG(ptr, *pUB, unigram1.buf);
  unigram1.buf[unigram1.len] = temp;
  assert (ptr != NULL);

  return *(float*)ptr + unigram_prob_1(unigram2, pUP);
}

double
trigram_prob_3(const zstr trigram, const zstr bigram1, const zstr bigram2, const zstr unigram1, const zstr unigram2, const zstr unigram3, Pvoid_t*const pUP, Pvoid_t*const pUB, Pvoid_t*const pBP, Pvoid_t*const pBB, Pvoid_t*const pTP) {
  PWord_t ptr;

  zbyte temp=trigram.buf[trigram.len];
  trigram.buf[trigram.len] = '\0';
  JSLG(ptr, *pTP, trigram.buf);
  trigram.buf[trigram.len] = temp;
  if (ptr != NULL) {
    return *(float*)ptr;
  }

  double bp = bigram_prob_2(bigram2, unigram2, unigram3, pUP, pUB, pBP);

  temp=bigram1.buf[bigram1.len];
  bigram1.buf[bigram1.len] = '\0';
  JSLG(ptr, *pBB, bigram1.buf);
  bigram1.buf[bigram1.len] = temp;
  if (ptr != NULL) {
    return (*(float*)ptr) + bp;
  }

  return bp;
}

void
split_trigram_and_unkify_in_place(zstr tri, zbyte* palimpsest, zstr*const pbi1, zstr*const pbi2, zstr*const puni1, zstr*const puni2, zstr*const puni3, zstr* putri, zstr*const pubi1, zstr*const pubi2, zstr*const puuni1, zstr*const puuni2, zstr*const puuni3, Pvoid_t*const pUP) {
  pbi1->buf = tri.buf;
  puni1->buf = tri.buf;

  const zbyte* p = zchr(cz(tri), ' ');
  assert (p != NULL);

  puni1->len = p - puni1->buf;
  pbi2->buf = (zbyte*)p+1;
  pbi2->len = tri.len - puni1->len - 1;
  puni2->buf = (zbyte*)p+1;

  p = zchr(cz(*pbi2), ' ');
  assert (p != NULL);

  puni2->len = p - puni2->buf;
  puni3->buf = (zbyte*)p+1;
  pbi1->len = p - pbi1->buf;
  puni3->len = tri.len - pbi1->len - 1;

  PWord_t ptr1, ptr2, ptr3;

  zbyte temp = puni1->buf[puni1->len];
  puni1->buf[puni1->len] = '\0';
  JSLG(ptr1, *pUP, puni1->buf);
  puni1->buf[puni1->len] = temp;
  temp = puni2->buf[puni2->len];
  puni2->buf[puni2->len] = '\0';
  JSLG(ptr2, *pUP, puni2->buf);
  puni2->buf[puni2->len] = temp;
  temp = puni3->buf[puni3->len];
  puni3->buf[puni3->len] = '\0';
  JSLG(ptr3, *pUP, puni3->buf);
  puni3->buf[puni3->len] = temp;

  if ((ptr1 == NULL) || (ptr2 == NULL) || (ptr3 == NULL)) {
    /* unkify */
    zbyte* q = palimpsest;
    putri->buf = q;
    puuni1->buf = q;
    pubi1->buf = q;
    if (ptr1 == NULL) {
      *q++ = 0x1A;
    } else {
      memcpy(q, puni1->buf, puni1->len);
      q += puni1->len;
    }
    puuni1->len = q - puuni1->buf;
    *q++ = ' ';

    puuni2->buf = q;
    pubi2->buf = q;
    if (ptr2 == NULL) {
      *q++ = 0x1A;
    } else {
      memcpy(q, puni2->buf, puni2->len);
      q += puni2->len;
    }
    puuni2->len = q - puuni2->buf;
    pubi1->len = q - putri->buf;
    *q++ = ' ';

    puuni3->buf = q;
    if (ptr3 == NULL) {
      *q++ = 0x1A;
    } else {
      memcpy(q, puni3->buf, puni3->len);
      q += puni3->len;
    }
    puuni3->len = q - puuni3->buf;
    pubi2->len = q - pubi2->buf;
    putri->len = q - putri->buf;
  } else {
    *putri = tri;
    *pubi1 = *pbi1;
    *pubi2 = *pbi2;
    *puuni1 = *puni1;
    *puuni2 = *puni2;
    *puuni3 = *puni3;
  }
}

double
trigram_split_unkify_prob_3(zstr tri, Pvoid_t* pUP, Pvoid_t* pUB, Pvoid_t* pBP, Pvoid_t* pBB, Pvoid_t* pTP) {
    zstr b1, b2, u1, u2, u3;
    zstr tu, bu1, bu2, uu1, uu2, uu3;
    zbyte unkbuf[MAXTRIGRAMSIZE+1]; /* +1 for null-terminating char */

    split_trigram_and_unkify_in_place(tri, unkbuf, &b1, &b2, &u1, &u2, &u3, &tu, &bu1, &bu2, &uu1, &uu2, &uu3, pUP);
    return trigram_prob_3(tu, bu1, bu2, uu1, uu2, uu3, pUP, pUB, pBP, pBB, pTP);
}

