# Operating systems Three Easy Pieces: Chapter 20 solution

## Question 1

Just one should be enough. Because only address to the first level page directory base address needs to be stored in a register. The page directory entries can point to other page directories or tables.

## Question 2

- `0x611c` -> `0b 11000 01000 11100`
- `0b11000` -> 24, `0b01000` -> 8, `0b11100` -> 28
- `pages[108][24`] -> `0xa1` -> `0b 1 0100001`, valid.
- `0b0100001` -> 33
- `pages[33][8]` -> `0xb5` -> `0b1 0110101`, valid.
- `0b0110101` -> 53
- `pages[53][28]` -> `0x8` -> 8

So that's three memory access as expected.

## Question 3

If I understand the question correctly, the way multi level page directories work so far, memory references to page tables aren't stored in TLB. TLB stores physical address against VPN. Page directories don't have VPN, they are stored outside the memory space of the current program by the system.

So every TLB miss will result in two more TLB miss.
