# Operating systems Three Easy Pieces: Chapter 28 solution

## Question 1

Yes, it is quite simple.

## Question 2

`flag` will end up with 0

## Question 3

The loops run twice, but flag still ends up with 0.

## Question 4

The interrupt must not happen while the flag is being acquired. For higher values of `bx`, the program never works correctly, unless the interrupt frequency is lower that the whole time a thread needs to finish.

## Question 5

Test and set the lock variable, if the lock variable was 0 before setting, critical section starts. Otherwise wait in loop. Releasing lock is simply setting 0 to the lock variable.

## Question 6

It does work correctly all the time. But the CPU waste is high if the interrupt frequency is low.

## Question 7

It prevents acquisition of a acquired lock, but fairness is not guaranteed here.

## Question 8

It makes sense. The turn variable is there to make sure, two thread doesn't get stuck infinitely in attempt to acquire a lock. It's like one thread saying to the other: 'I am about to attempt acquiring the lock. But if I can't (because you already set your flag to 1) then you can go ahead even though my flag is set to 1.

## Question 9

It works. Can't see any different behavior.

## Question 10

We can use interrupt frequency from 1 to high number to show that no matter where one thread gets interrupted, it still produces correct result.

## Question 11

It is like described in the chapter. It does spend time on spin-waiting just like any spinning lock.

## Question 12

It still works with more threads.

## Question 13

With any low interrupt frequency, `yeild` can save about 40-50 percent CPU time.

## Question 14

It does some savings only if writing or the `xchg` is considered expensive
