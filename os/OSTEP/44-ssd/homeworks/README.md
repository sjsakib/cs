# Operating systems Three Easy Pieces: Chapter 44 solution

## Question 1

`./ssd.py -T log -s 2 -n 10 -q`

write(58, F)
write(46, 9)
write(31, I)
trim(31)
write(35, g)
read(46) -> 9
read(35) -> g
write(44, 3)
read(58)
write(79, F)

## Question 2

Without overwrites, it is not that hard to figure out.

## Question 3

Some commands try to read uninitialized data, which fails.

## Question 4

`./ssd.py -T log -s 1 -n 10 -C`

For the first erase 1000 + 160 for four program + 40 for four reads.

## Question 5

The log structured approach performs much better for avoiding unnecessary erases which is very expensive.

## Question 6

There garbage in the system. Storage will seem to be full even though it is not, because blocks with a few live pages can't be erased. It's actually more like fragmentation.

## Question 7

I think think 7 3 is a good combination.


## Question 8

The gc causes extra logical writes in the log structured approach. But it causes less physical writes and of course erases.

## Question 9

Skewed workload gives better performance in both approaches. But the improvement is more significant in the log structured approach.

This might be because skewed workload puts the active pages in same blocks.
