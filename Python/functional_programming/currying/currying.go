package main

import (
	"fmt"
)

func main() {
	fmt.Println(add(5)(3))
}

func add(a int) func(int) int {
	return func(b int) int {
		return a + b
	}
}
