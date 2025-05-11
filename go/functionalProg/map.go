package main

import (
	"fmt"
	"iter"
)

// Normal map function
func Map[T any](slice []T, transform func(T) T) []T {
	result := make([]T, len(slice))
	for _, elem := range slice {
		result = append(result, transform(elem))
	}
	return result
}

// Map functions that return an iterator instead of an array
func MapIter[T any](slice []T, transform func(T) T) iter.Seq[T] {
	return func(yield func(T) bool) {
		for _, v := range slice {
			if !yield(transform(v)) {
				return
			}
		}
	}
}

func MapIter2[T any](slice []T, transform func(T) T) iter.Seq2[int, T] {
	return func(yield func(int, T) bool) {
		for i, v := range slice {
			if !yield(i, transform(v)) {
				return
			}
		}
	}
}

func main() {
	nums := []int{0, 1, 2, 3, 4, 5}
	doubleNums1 := MapIter(nums, func(v int) int {
		return v * 2
	})
	doubleNums2 := MapIter2(nums, func(v int) int {
		return v * 2
	})
	fmt.Print("Nums 1: ")
	for n := range doubleNums1 {
		fmt.Print(n, " ")
	}
	fmt.Println("Nums 2")
	for i, v := range doubleNums2 {
		fmt.Println(i, v)
	}
	numsNorm := Map(nums, func(elem int) int {
		return elem * 2
	})
	fmt.Println("Nums Normal: ", numsNorm)
}
