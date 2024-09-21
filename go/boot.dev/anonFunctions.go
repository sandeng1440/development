// Anonymous functions
/*Complete the printReports function. It takes as input a sequence of messages, intro, body, outro. 
It should call printCostReport once for each message. 
Give it a function that returns the cost of a message as an integer. Here are the costs:

	Into: 2*len(intro) 
	Body: 3*len(body)
	Outro: 4*len(outro)
*/

package main

import "fmt"

func printReports(intro, body, outro string) {
	printCostReport(func (string) int {
		return 2*len(intro)
	}, intro)
	printCostReport(func (string) int {
		return 3*len(body)
	}, body)
	printCostReport(func (string) int {
		return 4*len(outro)
	}, outro)
}

// don't touch below this line

func main() {
	printReports(
		"Welcome to the Hotel California",
		"Such a lovely place",
		"Plenty of room at the Hotel California",
	)
}

func printCostReport(costCalculator func(string) int, message string) {
	cost := costCalculator(message)
	fmt.Printf(`Message: "%s" Cost: %v cents`, message, cost)
	fmt.Println()
}
