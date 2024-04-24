package main

import "fmt"

func main() {
	arr := []int{2, 10, 17, 5, 3, 1, 18, 15, 20, 9, 7, 12, 13, 8, 4, 11, 0, 14, 6, 16, 19}
	fmt.Println(arr)
	merge_sort(arr)
	fmt.Println(arr)
}

func merge_sort(arr []int) {
	arr_size := len(arr)
	if arr_size <= 1 {
		return // base case
	}

	var middle int = arr_size / 2

	l_arr := make([]int, middle)
	r_arr := make([]int, arr_size-middle)

	l, r := 0, 0
	for i := 0; i < arr_size; i++ {
		if i < middle {
			l_arr[l] = arr[i]
			l++
		} else {
			r_arr[r] = arr[i]
			r++
		}
	}

	merge_sort(l_arr)
	merge_sort(r_arr)
	merge(l_arr, r_arr, arr)
}

func merge(l_arr []int, r_arr []int, arr []int) {
	i, l, r := 0, 0, 0
	for l < len(l_arr) && r < len(r_arr) {
		if l_arr[l] < r_arr[r] {
			arr[i] = l_arr[l]
			l++
			i++
		} else {
			arr[i] = r_arr[r]
			r++
			i++
		}
	}
	for ; l < len(l_arr); l++ {
		arr[i] = l_arr[l]
		i++
	}
	for ; r < len(r_arr); r++ {
		arr[i] = r_arr[r]
		i++
	}
}

func display(arr []int) {
	fmt.Printf("\n[")
	for i := 0; i < len(arr); i++ {
		fmt.Printf(" %v ", arr[i])
	}
	fmt.Printf("]")
}
