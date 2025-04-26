package main

import (
	"01Init/myHttp"
	"fmt"
	"log"
)

const issueURL = "https://api.boot.dev/v1/courses_rest_api/learn-http/issues"

func main() {
	issues, err := myHttp.GetIssues(issueURL)
	if err != nil {
		log.Fatalf("error getting issue data: %v", err)
	}
	for _, issue := range issues {
		fmt.Println(issue)
	}
}
