# Operating systems Three Easy Pieces: Chapter 22 solution

## Question 1

```
./paging-policy.py -s 0 -n 10
ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Assuming a replacement policy of FIFO, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 8  Hit/Miss?  State of Memory?
Access: 7  Hit/Miss?  State of Memory?
Access: 4  Hit/Miss?  State of Memory?
Access: 2  Hit/Miss?  State of Memory?
Access: 5  Hit/Miss?  State of Memory?
Access: 4  Hit/Miss?  State of Memory?
Access: 7  Hit/Miss?  State of Memory?
Access: 3  Hit/Miss?  State of Memory?
Access: 4  Hit/Miss?  State of Memory?
Access: 5  Hit/Miss?  State of Memory?
```
1. With FIFO
   | Access | Cache       | Outcome |
   | ------ | ----------- | ------- |
   | 8      | []          | miss    |
   | 7      | \[8]        | miss    |
   | 4      | \[8, 7]     | miss    |
   | 2      | \[8, 7, 4]  | miss    |
   | 5      | \[7, 4, 2]  | miss    |
   | 4      | \[4, 2, 5]  | hit     |
   | 7      | \[4, 2, 5]  | miss    |
   | 3      | \[2, 5, 7 ] | miss    |
   | 4      | \[5, 7, 3 ] | miss    |
   | 5      | \[7, 3, 4 ] | miss    |

2. With LRU
   | Access | Cache       | Outcome |
   | ------ | ----------- | ------- |
   | 8      | []          | miss    |
   | 7      | \[8]        | miss    |
   | 4      | \[8, 7]     | miss    |
   | 2      | \[8, 7, 4]  | miss    |
   | 5      | \[7, 4, 2]  | miss    |
   | 4      | \[4, 2, 5]  | hit     |
   | 7      | \[4, 2, 5]  | miss    |
   | 3      | \[4, 5, 7 ] | miss    |
   | 4      | \[4, 7, 3 ] | hit     |
   | 5      | \[4, 7, 3 ] | miss    |

3. With OPT
   | Access | Cache       | Outcome |
   | ------ | ----------- | ------- |
   | 8      | []          | miss    |
   | 7      | \[8]        | miss    |
   | 4      | \[8, 7]     | miss    |
   | 2      | \[8, 7, 4]  | miss    |
   | 5      | \[7, 4, 2]  | miss    |
   | 4      | \[7, 4, 5]  | hit     |
   | 7      | \[7, 4, 5]  | hit     |
   | 3      | \[7, 4, 5]  | miss    |
   | 4      | \[4, 5, 3]  | hit     |
   | 5      | \[4, 7, 3 ] | hit     |


## Question 2
* FIFO: `./paging-policy.py -s 0 --policy=FIFO -C 5 -a 0,1,2,3,4,5,0,1,2,3,4,5,0,1,2,3,4,5 -c`
* LRU: The same input is worst case for LRU as well. Increasing cache size by 1 gives result identical to OPT in both cases.
* MRU: `./paging-policy.py -s 0 --policy=MRU -C 5 -a 0,1,2,3,4,5,4,5,4,5,4,5,4,5,4,5,4,5 -c`
  
## Question 3
`./paging-policy.py -s 0 --policy=LRU -C 4 -a 7,5,1,5,1,7,5,3,3,0,4,1,3,5,2,5,6,0,1,2,3,0,8,1,0,1,3,1,6,1,5,1 -c`

LRU, MRU, FIFO has equal chance of performing good or bad in random sequences. In this particular sequence, FIFO does best with 50% hit rate. LRU does slightly worse with 43%. MRU does worst with 25%

## Question 4

This script gives us a normal distribution sequence with every access being likely to be close to the last access.
```py
import random

arr = [10]

for i in range(32): 
    arr.append(abs(int(random.normalvariate(arr[-1], 2))))
print(','.join(str(x) for x in arr))

```
`10,9,9,11,7,6,6,7,6,3,4,6,6,5,5,6,6,2,2,1,2,3,3,1,1,2,0,3,4,3,6,5,8`

FIFO and LRU performs similarly in this, close to OPT. But MRU performs much worse as expected.

This script gives a rough 20-80 workload
```py
import random
random.seed(0)

total = 10

hot = int(total*.2)

arr = []

for i in range(80):
    arr.append(random.randint(0, hot))

for i in range(20):
   arr.append(random.randint(hot, total))

random.shuffle(arr)

print(','.join(str(x) for x in arr))
```

LRU gives 60, where RAND gives 53. CLOCK with one bit performs just like RAND. But clock with 2 bits can perform better than LRU, 62. CLOCK with more bits can get as high as 65.

## Question 5

![Chart](FIFO,&#32;RAND,&#32;LRU&#32;and&#32;CLOCK.png)

Thanks to paging, even with a cache size of 1 gives 50% hits. How do I find a working set?
