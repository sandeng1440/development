package myHttp

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
)

type Issue struct {
	Title    string `json:"title"`
	Estimate int    `json:"estimate"`
}

func (i Issue) String() string {
	return fmt.Sprintf("{ Title: %s, Estimate: %d }", i.Title, i.Estimate)
}

func GetIssues(url string) ([]Issue, error) {
	res, err := http.Get(url)
	if err != nil {
		return nil, fmt.Errorf("error creating request: %w", err)
	}
	defer res.Body.Close()

	var issues []Issue
	decoder := json.NewDecoder(res.Body)
	if err := decoder.Decode(&issues); err != nil {
		return nil, fmt.Errorf("error decoding json: %w", err)
	}
	return issues, nil
}

func GetIssueData(url string) ([]Issue, error) {
	res, err := http.Get(url)
	if err != nil {
		return nil, fmt.Errorf("error creating request: %w", err)
	}
	defer res.Body.Close()
	data, err := io.ReadAll(res.Body)
	if err != nil {
		return nil, fmt.Errorf("error reading response: %w", err)
	}
	var issues []Issue
	err = json.Unmarshal(data, &issues)
	if err != nil {
		return nil, fmt.Errorf("error unmarshalling json: %w", err)
	}
	return issues, nil
}

func Prettify(data []byte) (string, error) {
	var prettyJSON bytes.Buffer
	err := json.Indent(&prettyJSON, data, "", "  ")
	if err != nil {
		return "", fmt.Errorf("error prettifying json: %w", err)
	}
	return prettyJSON.String(), nil
}
