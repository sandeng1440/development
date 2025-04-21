package main

import (
	"01Init/myHttp"
	"fmt"
	"log"
)

const issueURL = "https://api.boot.dev/v1/courses_rest_api/learn-http/issues"

func main() {
	issues, err := myHttp.GetIssueData(issueURL)
	if err != nil {
		log.Fatalf("error getting issue data: %v", err)
	}

	prettyData, err := myHttp.Prettify(issues)
	if err != nil {
		log.Fatalf("error prettifying data: %v", err)
	}
	fmt.Println(prettyData)
}
