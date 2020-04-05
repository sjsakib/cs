# Operating systems Three Easy Pieces: Chapter 27 solution

## Question 1

It does points to the right line of code. Additionally it provides where the threads were created.

## Question 2

Removing one of them make the reports go away as expected.

Adding locks around the two operations makes the report go away when the thread is declared at global scope, i.e. the lock is the same lock for both cases. Initializing the lock after the second thread was created should be problematic, `helgrind` failed to report that.

## Question 3

If both of the new threads start running at the same time, that would be a problem. Both of them will acquire one and wait for the other. Which they will never get.

## Question 4

`helgrind` reports that lock order is violated.

## Question 5

The problem should go away now. With the third lock, only one thread will be able to enter the code specific for only that thread. Then that thread will easily acquire both locks and then release them. Then the other thread can do the same.

But `helgrind` still reports violation.

## Question 6

It is inefficient because the parent keeps checking a condition repeatedly while the child id running.

## Question 7

`helgrind` reports data race because of the `done = 1` write.

## Question 8

Performance is is clearing a reason. Because the waiting thread will to sleep and thus will not keep using the CPU. But to me, it doesn't seem to be more correct. 

## Question 9

Doesn't report any problem.

