#!/usr/bin/env python

import sys

filename = sys.argv[1]
runtimes = []
with open(filename) as f:
    for line in f:
        runtimes.append(float(line))

mean = sum(runtimes) / len(runtimes)
print "mean:  ", mean
print "stddev:", (sum((runtime - mean) ** 2 for runtime in runtimes) /
                  len(runtimes)) ** 0.5
