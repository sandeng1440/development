package main

import (
	"fmt"
)

func main() {
	matrix := [][]int{
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9},
	}

	fmt.Println(pureReflectHorizontal(matrix))
	// fmt.Println(reflectHorizontal(matrix))
}

func pureReflectHorizontal(ar [][]int) [][]int {
	if len(ar) == 0 {
		return ar
	}
	return append([][]int{reverseSlice(ar[0])}, pureReflectHorizontal(ar[1:])...)
}

func reverseSlice(row []int) []int {
	if len(row) == 0 {
		return row
	}
	return append([]int{row[len(row)-1]}, reverseSlice(row[:len(row)-1])...)
}

// The impure function
func reflectHorizontal(ar [][]int) [][]int {
	for i := 0; i < len(ar); i++ { // i < number of rows
		left := 0
		right := len(ar[i]) - 1 // number of columns
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
