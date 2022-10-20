#!/usr/bin/env python3

from sys import argv
from collections import defaultdict

txt = argv[1]

print("Python")
print("Processing", txt, "...")

fp = open(txt)

count = 0
wc = defaultdict(int)

for line in fp:
    #print(line, )
    count += 1

    # Remove \n and blank line$
    #line = line.rstrip("\n")
    #if (len(line) == 0):
    #    continue

    for word in line.split():
        wc[word] += 1

fp.close()

print("Processed", count, "lines.")

for word, value in sorted(wc.items(), key=lambda item: item[1], reverse=True):
    print("%10d: [%s]" % (value, word))
