# UVa 120 - Stacks of Flapjacks

We need to sort a list of numbers with the flip operation mentioned in the problem statement.

The good news here is that `n` is `<=30` and we don't need to minimize the required steps. So, even a very pythonic `n^2` solution works. Here we traverse the list from last to first. At every step we need to put the largest number up to the current position at current position. For that, we find the largest number position up to current position. Then we do one flip (if necessary) so that the largest number comes at the first position. Then we do another flip so that the first position comes at out current position.

[Python solution](https://github.com/sjsakib/cs/blob/master/algorithms/the-algorithm-design-manual/programming-challenges/uva120/uva120.py)
