package main

func maxMessages(thresh int) int {
	t := 0
	for i := 0; ; i++ {
		t += 100 + i
		if t > thresh {
			return i
		}
		if t == thresh {
			return i + 1
		}
	}
}
