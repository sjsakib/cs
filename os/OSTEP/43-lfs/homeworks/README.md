# Operating systems Three Easy Pieces: Chapter 43 solution

## Question 1

```
 ./lfs.py -n 3

INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

command?
command?
command?

FINAL file system contents:
[   0 ]  ?   checkpoint: 14 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ]  ?   [.,0] [..,0] -- -- -- -- -- --
[   2 ]  ?   type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ]  ?   chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ]  ?   [.,0] [..,0] [ku3,1] -- -- -- -- --
[   5 ]  ?   type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ]  ?   type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ]  ?   chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ]  ?   z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0
[   9 ]  ?   type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 8
[  10 ]  ?   chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  11 ]  ?   [.,0] [..,0] [ku3,1] [qg9,2] -- -- -- --
[  12 ]  ?   type:dir size:1 refs:2 ptrs: 11 -- -- -- -- -- -- --
[  13 ]  ?   type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  14 ]  ?   chunk(imap): 12 9 13 -- -- -- -- -- -- -- -- -- -- -- -- --
```

Commands:

```
creat('/ku3')
open('/ku3'); write(); close('/ku3');
creat('/qg9');
```

Block 0,8,9,11,12,13,14 are active.

## Question 2

The `-i` flag definitely makes it easier to understand the commands.

## Question 3

```
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

create file /us7
write file  /us7 offset=4 size=0
write file  /us7 offset=7 size=7
```

```
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
---
[   4 ] live [.,0] [..,0] [us7, 1]
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ]      type: reg, size: 0, refs: 0, ptrs: -- -- -- -- -- -- -- --
[   7 ]      chunk(imap) 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ]      type:reg size:4 refs:1 ptrs: -- -- -- -- -- -- -- --
[   9 ]      chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  10 ] live i0i0i0i0i0i0i0i0i0i0i0i0i0i0i0i0
[  11 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 10
[  12 ] live chunk(imap): 5 11 -- -- -- -- -- -- -- -- -- -- -- -- -- --
```


## Question 4

One needs to look into the last imap to find out the active files and directories.

## Question 5

` ./lfs.py -o  -L c,/foo:w,/foo,0,1:w,/foo,1,1:w,/foo,2,1:w,/foo,3,1`

Block 0,4,5,8,11,14,17,18,19 are live. Again the last imap helps.

## Question 6

Apart from producing more write operations, small writes produce produce more garbage.

## Question 7

`./lfs.py -L c,/foo:w,/foo,0,1`
`./lfs.py -L c,/foo:w,/foo,7,1`

The later writes with an offset, which makes the size in inode offset+write size.

## Question 8

With directory creation, data block has to be written immediately. With file, data block is allocated and written when the file is written to.

## Question 9

`./lfs.py -L c,/foo:l,/foo,/bar:l,/foo,/goo -o -i`

In both cases, a new entry is added to the parent directory. But with a link, no new inodes are required. The old inode has to be updated and thus copied though with the new ref count.

## Question 10

A random policy creates more fragmentation.
