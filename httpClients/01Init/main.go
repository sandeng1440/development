package main

import (
	"01Init/myHttp"
	"log"
)

// "encoding/json"
// "fmt"

const issueURL = "https://api.boot.dev/v1/courses_rest_api/learn-http/issues"
const resourceURL = "https://api.boot.dev/v1/courses_rest_api/learn-http/issues?limit=10"

func main() {
	resources, err := myHttp.GetResources(resourceURL)
	if err != nil {
		log.Fatalf("error getting resources: %v", err)
	}
	myHttp.LogResources(resources)
	// issues, err := myHttp.GetIssues(issueURL)
	// if err != nil {
	// 	log.Fatalf("error getting issue data: %v", err)
	// }
	// for _, issue := range issues {
	// 	fmt.Println(issue)
	// }
}
