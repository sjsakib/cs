# Operating systems Three Easy Pieces: Chapter 38 solution

## Question 1

The left-symmetric layout seems like a strange way to layout the sectors. Not sure how this is supposed to help.

## Question 2

Using bigger chunk again puts multiple parity blocks in the same disks for level 5.

## Question 4

RAID 4 and 5 will be much more efficient all four of disks are used in single request. The reads can be omitted then.

## Question 5

```
./raid.py -L 0 -t -n 100 -c    # 275.7
./raid.py -L 1 -t -n 100 -c    # 278.7
./raid.py -L 4 -t -n 100 -c    # 386.1
./raid.py -L 5 -t -n 100 -c    # 276.5
```

## Question 6

```
./raid.py -L 0 -n 100 -t -D 4 -c   # 275.7
./raid.py -L 0 -n 100 -t -D 8 -c   # 156.5
./raid.py -L 0 -n 100 -t -D 16 -c   # 86.8
./raid.py -L 0 -n 100 -t -D 32 -c   # 58.6
```

Other levels scales pretty similarly.

## Question 7

Level 4 scales badly. Others scale similarly.

## Question 8

Performance doesn't vary with read and write for sequential workload. But with random workload, using request size larger than `chunk size * number of disks` scales very well with larger requests.
