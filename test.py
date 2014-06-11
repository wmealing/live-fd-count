#!/bin/env python

import time

f = [open("/tmp/example-%d.txt" % i, "w") for i in range(1, 500000)]

print "sleeping.. "

time.sleep(3000)

for fh in f:
	fh.close()
