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

// JSON
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

func MarshalAll[T any](items []T) ([][]byte, error) {
	var obj [][]byte
	for _, item := range items {
		data, err := json.Marshal(item)
		if err != nil {
			return nil, fmt.Errorf("error marshalling items: %w", err)
		}
		obj = append(obj, data)
	}
	return obj, nil
}

// map[string]interface{}
func GetResources(url string) ([]map[string]any, error) {
	var resources []map[string]any
	res, err := http.Get(url)
	if err != nil {
		return nil, fmt.Errorf("error fetching data: %w", err)
	}
	defer res.Body.Close()
	err = json.NewDecoder(res.Body).Decode(&resources)
	if err != nil {
		return nil, fmt.Errorf("error decoding response: %w", err)
	}
	return resources, nil
}

func LogResources(resources []map[string]any) {
	var formattedStrings []string
	for _, obj := range resources {
		fstr := ""
		for key, val := range obj {
			switch val.(type) {
			case map[string]any:
				fstr = fmt.Sprintf("%sKey: %s - Value: [\n", fstr, key)
				for k, v := range val.(map[string]any) {
					fstr = fmt.Sprintf("%s\tKey: %s - Value: %v\n", fstr, k, v)
				}
				fstr = fmt.Sprintf("%s]\n", fstr)
			default:
				fstr = fmt.Sprintf("%sKey: %s - Value: %v\n", fstr, key, val)
			}
		}
		formattedStrings = append(formattedStrings, fstr)
	}
	for _, str := range formattedStrings {
		fmt.Println(str)
	}
}
