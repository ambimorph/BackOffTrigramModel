#!/usr/bin/env python

import BackOffTrigramModelPipe
import unittest

DECIMAL_PLACES = 5

class TmpipeUnklessTest(unittest.TestCase):

    @classmethod  
    def setUpClass(cls):  
        cls.unkless_tmpipe_obj = BackOffTrigramModelPipe.BackOffTMPipe("BackOffTrigramModelPipe", "test/data/pos_trigram_model_0.05K.arpa")

    def test_unicode(self):
	unicode_char = u'\xb6'
	self.unkless_tmpipe_obj.in_vocabulary(unicode_char) 

    def test_in_vocabulary(self):
        assert self.unkless_tmpipe_obj.in_vocabulary('"')
        assert self.unkless_tmpipe_obj.in_vocabulary("'s")
        assert self.unkless_tmpipe_obj.in_vocabulary('with')
        assert not self.unkless_tmpipe_obj.in_vocabulary('wax')

    def test_unigram_probability(self):
        probability = self.unkless_tmpipe_obj.unigram_probability('"')
        self.assertAlmostEqual(probability, -2.589533, DECIMAL_PLACES, msg=probability)

        probability = self.unkless_tmpipe_obj.unigram_probability("'s")
        self.assertAlmostEqual(probability, -2.52453, DECIMAL_PLACES, msg=probability)

        probability = self.unkless_tmpipe_obj.unigram_probability('with')
        self.assertAlmostEqual(probability, -2.395761, DECIMAL_PLACES, msg=probability)

        probability = self.unkless_tmpipe_obj.unigram_probability('wax')
        self.assertIs(probability, None, msg=probability)

    def test_trigram_probability(self):
        """
        Testing all backoff conditions.  See TrigramModel.h for formulas.
        """
        # attested
        probability = self.unkless_tmpipe_obj.trigram_probability(["that", "with","the"])
        self.assertAlmostEqual(probability, -0.4422206, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 attested, w2 w3 attested
        probability = self.unkless_tmpipe_obj.trigram_probability(["and", "that","with"])
        self.assertAlmostEqual(probability, -2.333839, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 attested, w2 w3 not
        probability = self.unkless_tmpipe_obj.trigram_probability(["and", "that","and"])
        self.assertAlmostEqual(probability, -3.66923311, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 not attested, w2 w3 attested
        probability = self.unkless_tmpipe_obj.trigram_probability(["the", "that","government"])
        self.assertAlmostEqual(probability, -2.759567, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 not attested, w2 w3 not attested
        probability = self.unkless_tmpipe_obj.trigram_probability(["the", "that","and"])
        self.assertAlmostEqual(probability, -3.637584, DECIMAL_PLACES, msg=probability)
        # Contains oov
        probability = self.unkless_tmpipe_obj.trigram_probability(["that", "they","understood"])
        self.assertIs(probability, None, msg=probability)


class TmpipeUnkfulTest(unittest.TestCase):
        
    @classmethod  
    def setUpClass(cls):  
        cls.unkful_tmpipe_obj = BackOffTrigramModelPipe.BackOffTMPipe("BackOffTrigramModelPipe", "test/data/trigram_model_0.1K.arpa")

    def test_get_vocabulary_with_prefix(self):
        prefix = self.unkful_tmpipe_obj.vocabulary_with_prefix('c')
        self.assertListEqual(prefix, ["can", "cost", "country"], prefix)
        prefix = self.unkful_tmpipe_obj.vocabulary_with_prefix("gen")
        self.assertListEqual(prefix, ["generation", "genetic"], prefix)


    def test_unigram_probability(self):
        probability = self.unkful_tmpipe_obj.unigram_probability('"')
        self.assertAlmostEqual(probability, -2.589533, DECIMAL_PLACES, msg=probability)

        probability = self.unkful_tmpipe_obj.unigram_probability("'s")
        self.assertAlmostEqual(probability, -2.52453, DECIMAL_PLACES, msg=probability)

        probability = self.unkful_tmpipe_obj.unigram_probability('with')
        self.assertAlmostEqual(probability, -2.325526, DECIMAL_PLACES, msg=probability)

        probability = self.unkful_tmpipe_obj.unigram_probability('wax')
        self.assertAlmostEqual(probability, -0.3612903, DECIMAL_PLACES, msg=probability)

    def test_trigram_probability(self):
        """
        Testing all backoff conditions.  See TrigramModel.h for formulas.
        """
        # attested
        probability = self.unkful_tmpipe_obj.trigram_probability(["that", "with","the"])
        self.assertAlmostEqual(probability, -0.4419316, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 attested, w2 w3 attested
        probability = self.unkful_tmpipe_obj.trigram_probability(["and", "that","with"])
        self.assertAlmostEqual(probability, -2.27247187, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 attested, w2 w3 not
        probability = self.unkful_tmpipe_obj.trigram_probability(["and", "that","and"])
        self.assertAlmostEqual(probability, -3.09802487, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 not attested, w2 w3 attested
        probability = self.unkful_tmpipe_obj.trigram_probability(["the", "that","government"])
        self.assertAlmostEqual(probability, -2.763977, DECIMAL_PLACES, msg=probability)
        # backedoff w1 w2 not attested, w2 w3 not attested
        probability = self.unkful_tmpipe_obj.trigram_probability(["the", "that","and"])
        self.assertAlmostEqual(probability, -3.132153, DECIMAL_PLACES, msg=probability)
        # Contains oov
        probability = self.unkful_tmpipe_obj.trigram_probability(["that", "they","understood"])
        self.assertAlmostEqual(probability, -0.4997397, DECIMAL_PLACES, msg=probability)

if __name__ == '__main__':
    unittest.main()
