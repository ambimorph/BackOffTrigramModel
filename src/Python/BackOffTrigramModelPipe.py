#!/usr/bin/python

import os, subprocess, codecs

class BackOffTMPipe:

    def __init__(self, pathtotmpipeexecutable, pathtolangmod):
        self.tmpipe = subprocess.Popen([pathtotmpipeexecutable, pathtolangmod], stdin=-1, stdout=-1)
        self.stdin = self.tmpipe.stdin
        self.stdin_byte_writer = codecs.getwriter('utf-8')(self.tmpipe.stdin)
        self.stdout = self.tmpipe.stdout

    def in_vocabulary(self, token):
        self.stdin.write("v " + token + '\n')
        return int(self.stdout.readline())

    def vocabulary_with_prefix(self, prefix):
        self.stdin.write("p " + prefix + '\n')
        return self.stdout.readline().split()

    def unigram_probability(self, token):
        if self.in_vocabulary(token):
            self.stdin.write("u " + token + '\n')
            return float(self.stdout.readline())
        else:
            self.stdin.write("U\n") # Is this an unk model?
            try:
                return float(self.stdout.readline())
            except ValueError, exp:
                return None

    def trigram_probability(self, tokens):
        self.stdin.write("U\n") # Is this an unk model?
        if self.stdout.readline() == "None\n":
            if reduce(lambda x, y: x and y, [self.in_vocabulary(t) for t in tokens]):
                self.stdin.write("t " + " ".join(tokens) + '\n')
                return float(self.stdout.readline())
            else:
                return None
        else:
            self.stdin.write("t " + " ".join(tokens) + '\n')
            return float(self.stdout.readline())


    def shutdown(self):
        if hasattr(self, "tmpipe"):
            if hasattr(self.tmpipe, "pid") and self.tmpipe.pid:
                os.kill(self.tmpipe.pid, 15)
            self.tmpipe.wait()

    def __del__(self):
        self.shutdown()
