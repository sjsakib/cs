# Operating systems Three Easy Pieces: Chapter 40 solution

## Question 1
```
./vsfs.py  -s 17
ARG seed 17
ARG numInodes 8
ARG numData 8
ARG numRequests 10
ARG reverse False
ARG printFinal False

Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11100000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1) (a,2)] [(.,1) (..,0)] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (u,1)] [(.,1) (..,0)] [] [] [] [] [] [] 

Which operation took place?

inode bitmap  11100000
inodes        [d a:0 r:4] [d a:1 r:2] [d a:2 r:2] [] [] [] [] [] 
data bitmap   11100000
data          [(.,0) (..,0) (u,1) (z,2)] [(.,1) (..,0)] [(.,2) (..,0)] [] [] [] [] [] 

Which operation took place?

inode bitmap  11110000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0)] [(.,3) (..,0)] [] [] [] [] 

Which operation took place?

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 

Which operation took place?

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:2] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0) (b,4)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 

Which operation took place?

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [] [] [] [] 

Which operation took place?

inode bitmap  11111000
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:4 r:1] [] [] [] 
data bitmap   11111000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [v] [] [] [] 

Which operation took place?

inode bitmap  11111100
inodes        [d a:0 r:5] [d a:1 r:2] [d a:2 r:2] [d a:3 r:2] [f a:4 r:1] [f a:-1 r:1] [] [] 
data bitmap   11111000
data          [(.,0) (..,0) (u,1) (z,2) (s,3)] [(.,1) (..,0) (b,5)] [(.,2) (..,0) (x,4)] [(.,3) (..,0)] [v] [] [] [] 
```

1. `mkdir('/u')`
2. `creat('/a')`
3. `unlink('/a')`
4. `mkdir('/z')`
5. `mkdir('/s')`
6. `creat('/z/x')`
7. `link('/z/x', '/u/b')`
8. `unlink('/u/b')`
9. `fd=open("/z/x", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);`
10. `creat('/u/b')`


## Question 2

```
./vsfs.py  -s 21 -r
ARG seed 21
ARG numInodes 8
ARG numData 8
ARG numRequests 10
ARG reverse True
ARG printFinal False

Initial state

inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 

mkdir("/o");

  State of file system (inode bitmap, inodes, data bitmap, data)?

creat("/b");

  State of file system (inode bitmap, inodes, data bitmap, data)?

creat("/o/q");

  State of file system (inode bitmap, inodes, data bitmap, data)?

fd=open("/b", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

fd=open("/o/q", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

creat("/o/j");

  State of file system (inode bitmap, inodes, data bitmap, data)?

unlink("/b");

  State of file system (inode bitmap, inodes, data bitmap, data)?

fd=open("/o/j", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

  State of file system (inode bitmap, inodes, data bitmap, data)?

creat("/o/x");

  State of file system (inode bitmap, inodes, data bitmap, data)?

mkdir("/o/t");

  State of file system (inode bitmap, inodes, data bitmap, data)?
```

```
inode bitmap  10000000
inodes        [d a:0 r:2] [] [] [] [] [] [] [] 
data bitmap   10000000
data          [(.,0) (..,0)] [] [] [] [] [] [] [] 
```

```
inode bitmap  11000000
inodes        [d a:0 r:3] [d a:1 r:2] [] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0)] [] [] [] [] [] [] 
```

```
inode bitmap  11100000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0)] [] [] [] [] [] [] 
```

```
inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:-1 r:1] [f a:-1 r:1] [] [] [] [] 
data bitmap   11000000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [] [] [] [] [] [] 
```

```
inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:-1 r:1] [] [] [] [] 
data bitmap   11100000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [m] [] [] [] [] [] 
```

```
inode bitmap  11110000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:3 r:1] [] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3)] [m] [j] [] [] [] [] 
```

```
inode bitmap  11111000
inodes        [d a:0 r:3] [d a:1 r:2] [f a:2 r:1] [f a:3 r:1] [f a:-1 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1) (b,2)] [(.,1) (..,0) (q,3) (j,4)] [m] [j] [] [] [] [] 
```

```
inode bitmap  11011000
inodes        [d a:0 r:3] [d a:1 r:2] [] [f a:3 r:1] [f a:-1 r:1] [] [] [] 
data bitmap   11010000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4)] [] [j] [] [] [] [] 
```

```
inode bitmap  11011000
inodes        [d a:0 r:3] [d a:1 r:2] [] [f a:3 r:1] [f a:2 r:1] [] [] [] 
data bitmap   11110000
data          [(.,0) (..,0) (o,1)] [(.,1) (..,0) (q,3) (j,4)] [g] [j] [] [] [] []
```

The algorithm prefers to allocate the first available block for data.

## Question 3

The system will end up with mostly directories and empty files. Naturally, `creat`, `mkdir`, `write` operations will fail afterwards.

## Question 4

With fewer inodes, `mkdir`, `creat` operations will start failing.


One aspect of the simulated file system is that it allows only one data block file and as soon as one operation fails, it stops. So availability of  either inode or data block alone does not make much of a difference.