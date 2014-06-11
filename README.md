live-fd-count
=============

This is a set of test package used to verify/ think about this patch

https://gist.github.com/wmealing/c0836bc6a38f8f90aa0d


This patch is currently against the RHEL6 kernel, although the idea is to have it accepted upstream first, 
before getting something  into the Red Hat kernel first.

This repository is intended to be used as a reference for my LKML post.


Colleagues of mine have pointed out that this may have performance 
impacts for tools that frequently parse /proc/pid/status

I have compiled a kernel with the above, and here are the performance stats.

System settings


```
# sysctl -w fs.file-max=5000000
fs.file-max = 5000000

```

Increase this sessions limits.

```
# ulimit -n 1000000
```

test.py had 500002 files open each time.

Here are some of the performance benchmarks so far.

```
# time cat /proc/`pidof python test.py`/status |grep FD
FDSize:	524288
FDCount: 500002

real	0m0.008s
user	0m0.002s
sys	0m0.004s

# time ./test-getdents /proc/`pidof python test.py`/fd &> /dev/null 

real	0m0.631s
user	0m0.001s
sys	0m0.485s
```

This time with readdir(3)

```
# time ./test-opendir /proc/`pidof python test.py`/fd &> /dev/null

real	0m0.129s
user	0m0.001s
sys	0m0.007s

```

(which oddly seems faster?)

My benchmark values above are not meant for micro-benchmarking but rather as a scale to
know how far behind the code is.

Is the current method of getting a live fdcount acceptable, if not how should I be doing it ?

Thanks

Wade Mealing.

