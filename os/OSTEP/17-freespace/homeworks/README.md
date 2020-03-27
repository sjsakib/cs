# Operating systems Three Easy Pieces: Chapter 17 solution

## Question 1

`./malloc.py -n 10 -H 0 -p BEST -s 0 -c`

Eventually we end up with size 1 free spaces as there is no coalesce.

## Question 2

When `-p WORST` is used, the space doesn't get congested at first like before. But the final outcome will be same.

## Question 3

Allocation gets fast with `-p FIRST` as one doesn't need to search of the best or worst match.

## Question 4

First fit is not effected by how the list is sorted. Best and worst fit is benefitted from `SIZESORT+` and `SIZESORT-` respectively. However if we did have coalescing, `ADDRSORT` would have helped coalescing.

## Question 5

Without coalescing and with higher `-n` we, end up with 1 sized free spaces. Which is not useful at all.

When coalescing is on, `ADDRSORT` obviously gives the best result with all of the fitting policies.

The other two sorting with coalescing:

1. Worst fit performs bad with either sorting. This is because the smaller free spaces doesn't get used until the larger free spaces get all chopped up. Over time, with sorting, these free spaces get separated from their contagious spaces. Which doesn't let them get coalesced. A different coalescing algorithm could solve this problem, but would coalescing much more time costly.

2. Best fit performs similarly with either sorting. Because smaller spaces get used more frequently and thus contagious spaces gets to stay together more compared to worst fit approach.

3. First fit with size sorting is just either worst fit or best fit. So, gives same result as them result.

## Question 6

If `P` is higher than 50 the system gets full eventually. When it is below 50, the simulator still produces 50% allocation requests. Because one cant not free memory that is not allocated.

## Question 7

Not possible with address sorting and coalescing on. 

* `./malloc.py -c -A +10,+15,+20,+25,+30,-0,-1,-2,-3,-4`
* `./malloc.py -c -A +10,+15,+20,+25,+30,-0,-1,-2,-3,-4 -l SIZESORT+ -C`
* `./malloc.py -c -A +10,+15,+20,+25,+30,-0,-1,-2,-3,-4 -l SIZESORT- -C`
