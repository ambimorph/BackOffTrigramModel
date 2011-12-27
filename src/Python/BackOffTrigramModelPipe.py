#!/usr/bin/python

import os, subprocess

class BackOffTMPipe:
    def __init__(self, pathtotmpipeexecutable, pathtolangmod):
        self.tmpipe = subprocess.Popen([pathtotmpipeexecutable, pathtolangmod], stdin=-1, stdout=-1)
        self.stdin = self.tmpipe.stdin
        self.stdout = self.tmpipe.stdout

    def trigram_log_probability(self, three_word_list):
        self.tmpipe.stdin.write("t " + " ".join(three_word_list) + "\n")
        return float(self.tmpipe.stdout.readline())

    def shutdown(self):
        if hasattr(self, "tmpipe"):
            if hasattr(self.tmpipe, "pid") and self.tmpipe.pid:
                os.kill(self.tmpipe.pid, 15)
            self.tmpipe.wait()

    def __del__(self):
        self.shutdown()
