# Operating systems Three Easy Pieces: Chapter 45 solution

## Question 1

Sum: 71
Xor: 51
Fletcher: 73 196

## Question 3

`./checksum.py -D 136,68,34,17 -c`

It can happen when there is only one `1` in a position in all the bytes.

## Question 4

`./checksum.py -D 134,129,1,8 -c`

## Question 5

Additive checksum will be same for any data set if their summation is same is same. For example

```
./checksum.py -D 134,129,1,8 -c
./checksum.py -D 131,130,2,9 -c
```

## Question 6

```
./checksum.py -D 88,145,37,168 -c
./checksum.py -D 216,149,33,40 -c
```

In general it can happen if bit flip happens in a complementary way in any two of the bytes.

## Question 7

Fletcher respects the order of the data unlike the other two.

## Question 8

```
./checksum.py -D 0,1,2,258 -c
./checksum.py -D 0,1,2,3 -c
```
