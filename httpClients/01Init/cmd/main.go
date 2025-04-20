package main

import (
	"01Init/myHttp"
	"fmt"
	"log"
)

func main() {
	issues, err := myHttp.GetIssueData()
	if err != nil {
		log.Fatalf("error getting issue data: %v", err)
	}

	// Don't edit above this line

	fmt.Println(string(issues))
}
