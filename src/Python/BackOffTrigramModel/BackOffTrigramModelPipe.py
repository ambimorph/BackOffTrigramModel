#!/usr/bin/python

import os, subprocess, codecs

class BackOffTMPipe:

    def __init__(self, pathtotmpipeexecutable, pathtolangmod):
        self.tmpipe = subprocess.Popen([pathtotmpipeexecutable, pathtolangmod], stdin=-1, stdout=-1, stderr=-1)
        self.unkbytestr = b'\x1A'
        self.stdin = self.tmpipe.stdin
        self.stdin_byte_writer = codecs.getwriter('utf-8')(self.tmpipe.stdin)
        self.stdout = self.tmpipe.stdout

    def in_vocabulary(self, token):
        self.stdin_byte_writer.write("iu " + token + '\n')
        return int(self.stdout.readline())

    def is_unk_model(self):
        self.stdin_byte_writer.write("Up\n") # Is this an unk model?
        try:
            return bool(float(self.stdout.readline()))
        except ValueError, exp:
            return False

    def vocabulary_with_prefix(self, prefix):
        self.stdin_byte_writer.write("us " + prefix + '\n')
        return [ b.decode('utf-8') for b in self.stdout.readline().split() ]

    def unigram_probability(self, token):
        if self.in_vocabulary(token):
            self.stdin_byte_writer.write("up " + token + '\n')
            return float(self.stdout.readline())
        else:
            self.stdin_byte_writer.write("Up\n") # Probability of unk
            try:
                return float(self.stdout.readline())
            except ValueError, exp:
                return None

    def unigram_backoff(self, token):
        if self.in_vocabulary(token):
            self.stdin_byte_writer.write("ub " + token + '\n')
            return float(self.stdout.readline())
        else:
            self.stdin_byte_writer.write("Ub\n") # backoff of unk
            try:
                return float(self.stdout.readline())
            except ValueError, exp:
                return None

    def in_bigrams(self, tokens):
        if self.is_unk_model():
            unkified_tokens = [t if self.in_vocabulary(t) else self.unkbytestr for t in tokens]
            self.stdin.write("ib " + ' '.join(unkified_tokens) + '\n')
            return int(self.stdout.readline())
        else:
            if self.in_vocabulary(tokens[0]) and self.in_vocabulary(tokens[1]):
                self.stdin.write("ib " + ' '.join(tokens) + '\n')
                return int(self.stdout.readline())
            else:
                return False

    def bigram_backoff(self, tokens):
        if self.is_unk_model():
            unkified_tokens = [t if self.in_vocabulary(t) else self.unkbytestr for t in tokens]
            self.stdin.write("bb " + ' '.join(unkified_tokens) + '\n')
            try:
                return float(self.stdout.readline())
            except ValueError:
                return None
        else:
            self.stdin.write("bb " + ' '.join(tokens) + '\n')
            try:
                return float(self.stdout.readline())
            except ValueError:
                return None

    def in_trigrams(self, tokens):
        if self.is_unk_model():
            unkified_tokens = [t if self.in_vocabulary(t) else self.unkbytestr for t in tokens]
            self.stdin.write("it " + ' '.join(unkified_tokens) + '\n')
            return int(self.stdout.readline())
        else:
            if reduce(lambda x, y: x and y, [self.in_vocabulary(t) for t in tokens]):
                self.stdin.write("it " + ' '.join(tokens) + '\n')
                return int(self.stdout.readline())
            else:
                return False

    def trigram_probability(self, tokens):
        if self.is_unk_model():
            self.stdin_byte_writer.write("tp " + " ".join(tokens) + '\n')
            return float(self.stdout.readline())
        else:
            if reduce(lambda x, y: x and y, [self.in_vocabulary(t) for t in tokens]):
                self.stdin_byte_writer.write("tp " + " ".join(tokens) + '\n')
                return float(self.stdout.readline())
            else:
                return None


    def shutdown(self):
        if hasattr(self, "tmpipe"):
            if hasattr(self.tmpipe, "pid") and self.tmpipe.pid:
                import os
                os.kill(self.tmpipe.pid, 15)
            self.tmpipe.wait()

    def __del__(self):
        self.shutdown()
