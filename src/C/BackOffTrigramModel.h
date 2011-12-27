#include "Judy.h"
#include "zstr.h"

const static size_t MAXWORDSIZE=64;
#define MAXUNIGRAMSIZE ((size_t)(17 + MAXWORDSIZE))
#define MAXBIGRAMSIZE ((size_t)(17 + 2 * MAXWORDSIZE))
#define MAXTRIGRAMSIZE ((size_t)(17 + 3 * MAXWORDSIZE))

const static zbyte UNKBYTESTR[]={0xFF, 0};

void
read_arpa_file(FILE* arpafile, Pvoid_t* UP, Pvoid_t* UB, Pvoid_t* BP, Pvoid_t* BB, Pvoid_t* TP);

/**
 * The following three functions are defined by this equation:
 *
 * p(wd3|wd1,wd2)= if(trigram exists)           p_3(wd1,wd2,wd3)
 *                 else if(bigram w1,w2 exists) bo_wt_2(w1,w2)*p(wd3|wd2)
 *                 else                         p(wd3|w2)
 * 
 * p(wd2|wd1)= if(bigram exists) p_2(wd1,wd2)
 *            else              bo_wt_1(wd1)*p_1(wd2)
 * 
 */

double
unigram_prob_1(zstr unigram, Pvoid_t* pUP);

double
bigram_prob_2(zstr bigram, zstr unigram1, zstr unigram2, Pvoid_t* pUP, Pvoid_t* pUB, Pvoid_t* pBP);

/**
 * The data must be pre-unkified (using our 0xFF unk marker).
 */
double
trigram_prob_3(zstr trigram, zstr bigram1, zstr bigram2, zstr unigram1, zstr unigram2, zstr unigram3, Pvoid_t* pUP, Pvoid_t* pUB, Pvoid_t* pBP, Pvoid_t* pBB, Pvoid_t* pTP);

/* Set the .buf and .len members of pbi1, pbi2, puni1, puni2, and puni3 to 
 * point to the substrings of the trigram, as separated by the ' ' char.
 * In addition, test each unigram for knownness, if any of the unigrams are 
 * unknown, then create an unkified copy of tri in buf, and set the pointers 
 * of putri, pubi1, pubi2, puuni1, puuni2, and puuni3 to point into buf.
 * If all unigrams are known, then the pointers of the "pu" variables will be 
 * set to point into the original trigram in the tri variable instead.
 *
 * @precondition utri.buf points to space which is sufficient to hold a copy of tri
 */
void
split_trigram_and_unkify_in_place(zstr tri, zbyte* buf, zstr* pbi1, zstr* pbi2, zstr* puni1, zstr* puni2, zstr* puni3, zstr* putri, zstr* pubi1, zstr* pubi2, zstr* puuni1, zstr* puuni2, zstr* puuni3, Pvoid_t* pUP);

double 
trigram_split_unkify_prob_3(zstr tri, Pvoid_t* pUP, Pvoid_t* pUB, Pvoid_t* pBP, Pvoid_t* pBB, Pvoid_t* pTP);
