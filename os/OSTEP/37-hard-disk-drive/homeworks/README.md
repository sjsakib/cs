# Operating systems Three Easy Pieces: Chapter 37 solution

## Question 2

One issue here is that the rotation keeps going on while seeking is being done. That causes unnecessary rotations sometimes. Higher seek rate helps only when it prevents such unnecessary rotation. Lower seek rate causes more of these unnecessary rotations, and thus decreases overall performance. If the rotation stopped during seeking, seek rate would have had direct impact on performance. 

## Question 3

Rotation rate always has direct relation to performance. But sometimes fast rotations can cause extra rotation and decrease performance. For example `./disk.py -a 7,30,8 -c -S 1 -R 4` is slower than `./disk.py -a 7,30,8 -c -S 1 -R 3`


## Question 4

`-p SSSTF` performs better that `FIFO`.

## Question 5

`./disk.py -a 7,19,35 -c -p SATF` is faster than `./disk.py -a 7,19,35 -c -p SSTF`

When there is a request to sector that is close to seek, but requires more rotation, `SSTF` is slow. 

## Question 6

minium required skew = `(track_width / S) * (sector_per_track*R/360)`

## Question 7

`./disk.py -z 10,20,30 -A 5,-1,0 -a -1 -G`

Outer track bandwidth: `30/360 = .083`
Middle track bandwidth: `20/360 = .083`
Inner track bandwidth: `10/360 = .027`

## Question 8

The window needs to be of size of number of requests to maximize performance. Window size of 1 makes all policy equal.

## Question 9

`./disk.py -a 0,30,1,0,5,4,3,6`

Using small window size solves starvation.


## Question 10

`./disk.py  -a 9,20 -p SATF`
