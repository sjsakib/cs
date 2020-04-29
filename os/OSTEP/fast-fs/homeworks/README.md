# Operating systems Three Easy Pieces: Chapter 41 solution

## Question 1

`-L 4` spreads out the file.

## Question 2

`-L 30` gives same result as without `-L` flag because each group can have at most 30 data blocks.

## Question 3

Filespan should decrease as `-L` increase up to 30.

## Question 4

Three groups should be used for the three directories.


## Question 5

It does pretty well. Can't get better if inodes and data blocks are kept separate. 

## Question 6

`dirspan` is affected badly. Besides a lot of data blocks in every group stays unused because small files.

## Question 7

This policy is better for `dirspan` because it prevents from another directory from getting in between a directory and its file inodes.

## Question 8

`i` is spread out in fragments.

## Question 9

`filspan` and `dirspan` is increased. But blocks of a file stays together.

