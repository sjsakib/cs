#!/bin/bash
# first hundred with precision 1
for i in {1..100..1}
do
    echo "$i, $(./tlb $i)";
done

for i in {100..1000..10}
do
    echo "$i, $(./tlb $i)";
done

for i in {1000..10000..1000}
do
    echo "$i, $(./tlb $i)";
done
