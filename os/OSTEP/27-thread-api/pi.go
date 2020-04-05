package main

import (
	"flag"
	"fmt"
	"math"
	"time"
)

func term(i int64) float64 {
	return (1.0 / float64(i)) * (1.0 / float64(i))
}

func segment(i int64, j int64, n int, c chan float64) {
	start := time.Now()
	sum := new(Float)
	for k := i; k <= j; k++ {
		sum += term(k)
	}
	fmt.Printf("Thread #%d finished in %s\n", n, time.Since(start))
	c <- sum
}

func main() {
	threads := flag.Int("threads", 4, "Number of threads")
	digits := flag.Int64("digits", 2, "Number of precise digits after decimal point")
	flag.Parse()
	iterations := int64(math.Pow(10, float64(*digits+1)))

	perThread := iterations / int64(*threads)

	c := make(chan Float)

	start := time.Now()
	for i := 0; i < *threads; i++ {
		var j int64 = 0
		if i == *threads-1 {
			j = iterations
		} else {
			j = int64(i+1) * perThread
		}
		go segment(int64(i)*perThread+1, j, i, c)
	}
	var sum float64 = 0
	for i := 0; i < *threads; i++ {
		sum += <-c
	}
	pi := math.Sqrt(sum * 6)
	fmt.Printf("\nPI: %.*f\n", *digits, pi)
	fmt.Println("Threads: ", *threads)
	fmt.Println("Iterations: ", iterations)
	fmt.Println("Time: ", time.Since(start))
}
