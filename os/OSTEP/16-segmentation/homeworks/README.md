# Operating systems Three Easy Pieces: Chapter 16 solution

## Question 1

`segmentation.py -a 128 -p 512 -b 0 -l 20 -B 512 -L 20 -s 0`

```
ARG seed 0
ARG address space size 128
ARG phys mem size 512

Segment register information:

  Segment 0 base  (grows positive) : 0x00000000 (decimal 0)
  Segment 0 limit                  : 20

  Segment 1 base  (grows negative) : 0x00000200 (decimal 512)
  Segment 1 limit                  : 59

Virtual Address Trace
  VA  0: 0x00000061 (decimal:   97) --> PA or segmentation violation?
  VA  1: 0x00000035 (decimal:   53) --> PA or segmentation violation?
  VA  2: 0x00000021 (decimal:   33) --> PA or segmentation violation?
  VA  3: 0x00000041 (decimal:   65) --> PA or segmentation violation?
  VA  4: 0x00000033 (decimal:   51) --> PA or segmentation violation?

For each virtual address, either write down the physical address it translates to
OR write down that it is an out-of-bounds address (a segmentation violation). For
this problem, you should assume a simple address space with two segments: the top
bit of the virtual address can thus be used to check whether the virtual address
is in segment 0 (topbit=0) or segment 1 (topbit=1). Note that the base/limit pairs
given to you grow in different directions, depending on the segment, i.e., segment 0
grows in the positive direction, whereas segment 1 in the negative.
```

### The first address is 108

- In 7 bit binary: `1100001`. The first bit suggest it is of `seg1`.
- Without the first bit the address is 44 in decimal.
- Since `seg1` growth is negative, we need to calculate how many units we need to come from end to reach 44. That would be `44 - 64 = -20`. (Address space size is 128, so seg1 max size is `128/2 = 64`)
- `|-20| <= 20`. So the access is valid.
- The physical translation would be `512 - 31 = 481`

### The second address is 53

- In 7 bit binary: `1100001`. So in `seg0`
- Without first bit: 33
  `33 - 64 = -31`
- `|-31| > 20`. So invalid.

## Question 2

Highest in legal `seg0` is 19. Lowest legal in `seg1` is 108. Lowest illegal in whole space is 20, highest illegal 107.
Generate all the possible comma separated virtual address with this python script:

```py
','.join([str(i) for i in range(128)])
```

Then use them with the `-A` flag. Of course one doesn't need all of them. Only `19,20,107,108` is enough. But why not?

## Question 3

`./segmentation.py -a 16 -p 128 -A 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 --b0 0 --l0 2 --b1 16 --l1 2`

## Question 4

Generated address are all within the address space. So one needs to give `seg0` and `seg1` length of 90% of the address space in total.

`./segmentation.py -a 100 -p 512 -n 1000 --b0 0 --l0 45 --b1 100 --l1 45 -c`

## Question 5

`./segmentation.py -a 100 -p 512 -n 10 --b0 0 --l0 0 --b1 100 --l1 0 -c`
