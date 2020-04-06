# Operating systems Three Easy Pieces: Chapter 29 solution

## Question 1

`gettimeofday` is accurate enough on the machine I am using.

## Question 2

When more threads are used, it takes more time. But when more threads than actual number of CPUs are used, the time stays same. I have 12 CPUs. So 12 threads and 100 threads takes roughly the same amount of time.

## Question 3

As the threshold increase performance doesn't increase like in the book. As the threshold increase exponentially the performance increase linearly and stops at a point (32). On the other hand with a good threshold (32) performance increase as number of threads increase.

![Chart](./Time&#32;vs.&#32;Threshold.png)
