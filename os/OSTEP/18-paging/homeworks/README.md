# Operating systems Three Easy Pieces: Chapter 18 solution

## Question 1

Table size will decrease as page size increase. But the problem with larger page would be internal fragmentation in the pages.

## Question 2

`./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 0`

All the addresses are invalid as none of the pages are allocated

`./paging-linear-translate.py -P 1k -a 16k -p 32k -v -u 25`

Page size is 1k, `log(1k) = 10` bits are required to describe every address. Address space size is 16k. There can be 16 pages in total, so `log(16) = 4` more bits are required to describe a page number.

- 14726 -> 0b11100110000110. First four bit 0b1110 -> 14. Page 14 is not valid. So address not valid.
- 11206 -> 0b10101111000110. First four bit 0b1010 -> 10. Page 10 is valid. PPN for page 10 is 0x13 -> 0b10011. So physical address is `0b10011 1111000110` -> 20422
- 7735 -> 0b01111000110111. VPN: 0b0111 -> 7. Not valid.

## Question 3

The first one is unrealistically small.

## Question 4

The program doesn't work when:

- Physical memory size is less or equal to the address space size.
- Page is is bigger that address space size.
- Page size or address space size is not power of 2. This is because it will result in discountinuous addresses.
- Page or address space size is zero
