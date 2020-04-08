# Operating systems Three Easy Pieces: Chapter 30 solution

## Question 1

## Question 2

Behavior doesn't change with larger buffer. NF is always 0 or 1. When `-C 0,0,0,0,0,0,1` is used, consumer sleeps for 1 second after every consumption. The producer fills whole the buffer in that time.

## Question 3

## Question 4

`./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,1,0,0,0:0,0,0,1,0,0,0:0,0,0,1,0,0,0 -l 10 -v -t`

The first consumer gets a value without waiting and thus without sleeping. Then the second consumer gets to waiting, but when the producer release the lock after producing, the first consumer again acquires the lock. So when the second consumer wakes up, it doesn't get a value and sleeps for a second holding the lock. In this way, the second and third consumer sleeps for 9 second in total. And at end of stream, all three consumers sleeps for 1 second each. So, the program takes total 12 seconds and some for for the actual executing.

## Question 5

Now it takes 11 seconds. Since there is only producers, there isn't much change. But since there is enough buffer slot now, one of the threads (the one that didn't come to c2 before main produced those EOS) doesn't have to wait for the EOS.

## Question 6

`./main-two-cvs-while -p 1 -c 3 -m 1 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t`

5 seconds. 9 consumption happen in three batches with every consumer sleeping 1 second after a batch, since the consumers don't hold the lock while sleeping. After that 1 consumer has to consume the last value and sleep for one second while the other two consumes EOS and sleeps for 1 second after that. Then the consumer consuming the last value wakes up, consumes EOS and sleeps for 1 second.

## Question 7

`./main-two-cvs-while -p 1 -c 3 -m 3 -C 0,0,0,0,0,0,1:0,0,0,0,0,0,1:0,0,0,0,0,0,1 -l 10 -v -t`

Same as last time.

## Question 8

It's not possible. Because there's only a single producers and a single consumer here. So one condition variable is enough.

## Question 9

Maybe because of scheduling priority or execution speed of different CPUs I couldn't put the consumers and producers to sleep at the same time but did manage to put the main thread and one consumer to sleep at the same time.

`./main-one-cv-while -l 3 -m 1 -p 1 -c 2 -v -t -P 0,0,0,0,0,0,1`

## Question 10

Not possible with one consumer. With many consumers, problem happen without any sleeping.

## Question 11

Problem should occur when two producers try to `do_fill` at the same time or two consumers try to `do_get` at the same time. Or one consumer checks that one value is available but when the lock is released before `do_get`, gets interrupted and another consumer consumes it by the time it resumes.

But I failed to produce such a case with the provided tools. However modifying the code a little, it is easy.

The code:

```diff
void *consumer(void *arg) {
    int id = (int) arg;
    int tmp = 0;
    int consumed_count = 0;
    while (tmp != END_OF_STREAM) { c0;
	Mutex_lock(&m);            c1;
	while (num_full == 0) {    c2;
	    Cond_wait(&fill, &m);  c3;
        }
        
-	Mutex_unlock(&m);
-	tmp = do_get();            c4;
+	Mutex_unlock(&m);          c4;
+	tmp = do_get();
	Mutex_lock(&m);
	Cond_signal(&empty);       c5;
	Mutex_unlock(&m);          c6;
	consumed_count++;
    }

    // return consumer_count-1 because END_OF_STREAM does not count
    return (void *) (long long) (consumed_count - 1);
}
```

Case:
`./main-two-cvs-while-extra-unlock -p 1 -c 2 -m 2 -l 100 -v -C 0,0,0,0,1,0,0:0,0,0,0,1,0,0`
