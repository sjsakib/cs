# Operating systems Three Easy Pieces: Chapter 10 solution

## Question 1

`./multi.py -n 1 -L a:30:200`

With one CPU and one job, it should finish in 30

## Question 2

The first 10 cycles will be the same, if `-r` is 2, the next 20 cycles will take ten.

## Question 3

It decrease `-r` times faster with every tick after the CPU is warm. 

## Question 4

Works just as expected. Become after `-w` ticks.

## Question 5

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50`

The caches cannot hold all three of the working sets. On top of that the quantum is same as the warm up time. As soon as the CPU warms up, job is switched. Sad.

## Question 6

`./multi.py -n 2 -L a:100:100,b:100:50,c:100:50 -A a:0,b:1,c:1`

I think this combination is as good as it gets. `a` can't be be put put with other jobs in a CPU because of it's big working set.

## Question 7

If we can run a job exclusively on a performance increase much more due to better cache usage.

## Question 8

It works better than manual affinity because of better CPU utilization. Performance increase with lower values of `-P`
