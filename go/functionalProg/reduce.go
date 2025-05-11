package Reduce

func Reduce[T any](slice []T, reducer func(T, T) T) T {
	var accumulator T
	for i, x := range slice {
		if i == 0 {
			accumulator = x
		} else {
			accumulator = reducer(accumulator, x)
		}
	}
	return accumulator
}
