#!/bin/bash
echo "Pages, Accessing all of them 100000 times"

i=1
while [ $i -le 63 ]
do
    echo "$i, $(./tlb $i)"
    i=$(( $i + 1 ));
done

while [ $i -le 65536 ]
do
    echo "$i, $(./tlb $i)"
    i=$(( $i * 2 ));
done
