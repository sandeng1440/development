package main

import (
	"fmt"
	"sync"
)

// NOTE: This program flips the rows of a matrix
func main() {
	arr := [][]int{
		{0, 1, 2},
		{1, 2, 3},
		{2, 3, 4},
	}
	str := "-"
	fmt.Printf("\nUnreflected array\n")
	printTwenty := printNTimes(20)
	printTwenty(str)
	printArr(arr)
	reflectHorizontal(arr)
	fmt.Printf("\nReflected array\n")
	printTwenty(str)
	printArr(arr)
}

func printArr(arr [][]int) {
	fmt.Println("-")
	for i := 0; i < len(arr); i++ {
		fmt.Println(arr[i])
	}
}

func reflectHorizontal(ar [][]int) [][]int {
	for i := 0; i < len(ar); i++ { // NOTE: i < number of rows
		left := 0
		right := len(ar[i]) - 1 // NOTE: number of columns
		for left < right {
			temp := ar[i][left]
			ar[i][left] = ar[i][right]
			ar[i][right] = temp
			left++
			right--
		}
	}
	return ar
}

func printNTimes(n int) func(string) {
	f := func(s string) {
		for i := 0; i < n; i++ {
			fmt.Printf("%v", s)
		}
	}
	return f
}
