#!/usr/bin/env python

import BackOffTrigramModelPipe, unittest
import sys

EPSILON = .0000001

tmpipeobj = BackOffTrigramModelPipe.BackOffTMPipe("../../C/BackOffTrigramModelPipe", "data/mini.arpa")

class BackOffTMPipeTest(unittest.TestCase):
    def test_trigram_probability(self):
        tp = tmpipeobj.trigram_log_probability([",", '"', "says"])
        assert abs(-0.659269 - tp) < EPSILON, l
        tp = tmpipeobj.trigram_log_probability(["it", "will", "be"])
        assert abs(-1.009832 - tp) < EPSILON, l
        tp = tmpipeobj.trigram_log_probability(["it", "will", "not"])
        assert abs(-2.440987 - tp) < EPSILON, l

    def test_unigram_probability(self):
        tmpipeobj.stdin.write('u "\n')
        l = tmpipeobj.stdout.readline()
        assert abs(-2.187073 - float(l)) < EPSILON, l
        tmpipeobj.stdin.write('u &\n')
        l = tmpipeobj.stdout.readline()
        assert abs(-2.799857 - float(l)) < EPSILON, l
        tmpipeobj.stdin.write("u it\n")
        l = tmpipeobj.stdout.readline()
        assert abs(-2.1371 - float(l)) < EPSILON, l
        tmpipeobj.stdin.write("u zero\n")
        l = tmpipeobj.stdout.readline()
        assert abs(-3.799857 - float(l)) < EPSILON, l
        
    def test_unigram_backoff(self):
        tmpipeobj.stdin.write("o it\n")
        l = tmpipeobj.stdout.readline()
        assert abs(-0.260354 - float(l)) < EPSILON, l
        tmpipeobj.stdin.write("o zero\n")
        l = tmpipeobj.stdout.readline()
        assert abs(-0.2765851 - float(l)) < EPSILON, l
        

if __name__ == '__main__':
    unittest.main()
