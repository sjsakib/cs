# Operating systems Three Easy Pieces: Chapter 42 solution

## Question 1
```
./fsck.py -D

ARG seed 0
ARG seedCorrupt 0
ARG numInodes 16
ARG numData 16
ARG numRequests 15
ARG printFinal False
ARG whichCorrupt -1
ARG dontCorrupt True

Final state of file system:

inode bitmap 1100100010000110
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] []
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]
```

```
- /
  |---- g (d)
  |---- t (f)
  |---- w (d)
  |     |---- p (f)
  |---- m (f)
```


## Question 2

```
ARG seed 0
ARG seedCorrupt 1
ARG numInodes 16
ARG numData 16
ARG numRequests 15
ARG printFinal False
ARG whichCorrupt -1
ARG dontCorrupt False

Final state of file system:

inode bitmap 1100100010000010
inodes       [d a:0 r:4] [f a:-1 r:1] [] [] [d a:8 r:2] [] [] [] [d a:6 r:2] [] [] [] [] [f a:15 r:1] [f a:12 r:1] []
data bitmap  1000001010001001
data         [(.,0) (..,0) (g,8) (t,14) (w,4) (m,13)] [] [] [] [] [] [(.,8) (..,0)] [] [(.,4) (..,0) (p,1)] [] [] [] [z] [] [] [g]

Can you figure out how the file system was corrupted?
```

Inode block 13 is wrongly marked as unused. Marking it used fixes the problem.

## Question 3

One corruption increase a reference count, while the other decreases one. Bot can be fixed by checking the contents of all the directories.

## Question 4

`./fsck.py -S 5`. Fixing this one will not be simple. The system has to check if all directories has reference to their parents and themselves. Then have to check all the entries, and update name if parent inode is referred. This sort of corruption is unlikely to arise naturally though.

`./fsck.py -S 38`, a file is simply renamed. Might be possible to detect from the name length in a real system. Not fixable.

`./fsck.py -S 642`, Another rename. Easily detectable, because there's another entry with the same name. Not fixable.


## Question 5

```
./fsck.py -S 6
./fsck.py -S 13
```

In both cases we have an inode that has data bus is not referred in any directory and is marked unused. In one case it is a file inode while in the other case it is a directory inode. They have to be cleared.

## Question 6

```
./fsck.py -S 9
```

The system can check data block 15 to check it really is directory. If not then then can change the type.

## Question 7

```
./fsck.py -S 15
```

Easily detectable and fixable. Inode 0 can not be file. No data is lost.

## Question 8

`./fsck.py -S 10`

The inode bitmap can help perhaps, but not if more than one such corruption happens.

## Question 9

`./fsck.py -S 16` The data bitmap can be used to fix this, only if one such corruption happens.

