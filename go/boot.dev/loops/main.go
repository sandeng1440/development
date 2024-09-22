package main

func bulkSend(numMessages int) float64 {
	cost := float64(numMessages)
	for i := 0; i < numMessages; i++ {
		cost += float64(i) / float64(100)
	}
	return cost
}
