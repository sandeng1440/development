package main

func Filter[T any](slice []T, filter func(T) bool) []T {
	var result []T
	for _, elem := range slice {
		if filter(elem) {
			result = append(result, elem)
		}
	}
	return result
}
