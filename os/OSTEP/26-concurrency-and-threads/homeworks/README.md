# Operating systems Three Easy Pieces: Chapter 26 solution

## Question 1

Assuming the initial value of `%dx` is 0, `%dx` will be -1 after executing the first line.

## Question 2

`./x86.py -p loop.s -t 2 -i 100 -R dx -a dx=3,dx=3`
No loading from memory is involved here. So as expected, in both threads, `%dx` will be 3,2,1,0 and then -1 and then the thread will exit.

## Question 3

`./x86.py -p loop.s -t 2 -i 3 -r -R dx -a dx=3,dx=3`
Still nothing, because register states are preserved on thread switches.

## Question 4

`./x86.py -p looping-race-nolock.s -t 1 -M 2000`

Value at 2000 changes to 1 when `%ax` is moved back to 2000 at line 8.

## Question 5

`./x86.py -p looping-race-nolock.s -t 2 -M 2000 -a bx=3`

Each thread keeps it own register state. So both of them loops three times.
The final value would be simply 6 because the interruption frequency is too high for the threads to be interrupted after register is updated but before moved back to memory.

## Question 6

`./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0`

The final value would be 2. In this case the timing is safe. Both registers moves the value back before any interruptions happen.

Not so in this case:
`./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0`

The critical section is this:

```
mov 2000, %ax  # get 'value' at address 2000
add $1, %ax    # increment it
mov %ax, 2000  # store it back
```

## Question 7

`./x86.py -p looping-race-nolock.s -t 2 -a bx=1 -M 2000 -i 1`

If interruption frequency is at least 3 the program will give correct result provided the program runs in a single CPU. Because length if the critical section is 3 which is at the beginning of the program.

## Question 8

`./x86.py -p looping-race-nolock.s -t 2 -a bx=100 -M 2000 -i 1`

Even with higher loops, interrupt frequency 3 gives correct result. Because length of the non-critical section is 3 too.

## Question 9

`./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000`

The final value has to be 1. Because the first thead just waits for the value to be 1 and no matter when it is started, the second thread sets it to 1.

## Question 10

`./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000`

Thread 0 is just waiting for thread 1 to set the value to 1. If thread 0 runs before thead 1, it waits until interruption happens. Thats is a waste of CPU. Sorter interruption frequency will improve performance.
