# Operating systems Three Easy Pieces: Chapter 32 solution

## Question 1

The order in which the threads run changes from run to run.

## Question 2

Deadlock never happens. Tried with higher value for `-l`, in a single core machine and multicore machine.

## Question 3

Deadlock happens more often with `-n` more than three.

## Question 4

The code avoids deadlock by using global order in acquiring the locks so that no circular wait happens. When the two vectors are same, waiting for the same lock for twice will cause deadlock. Hence the special case.

## Question 5

`./vector-global-order -t -n 10 -l 100000 -d` takes about .05s. Increasing loops increase time somewhat linearly. Increasing number of threads increase time linearly as well.

## Question 6

Performance increases as expected since the treads doesn't have to wait go acquire locks.

## Question 7

The first call to `pthread_mutex_trylock` was not really necessary. It probably decrease performance even, since a normal `pthread_mutex_lock` would have slept while waiting. But this one will keep jumping.

Performance is worse than global order approach and number of retries increase exponentially.

## Question 8

In this case, the problem arise only when `-p` flag is used. Performance decrease as all the threads has to wait for the global lock even though they are working on different vectors.

## Question 9

Not using locks at all makes the program much simpler with the same interface.

# Question 10

But surprisingly it is not a whole lot faster than other solutions. Slower that global order approach.
