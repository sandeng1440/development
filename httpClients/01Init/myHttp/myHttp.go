package myHttp

import (
	"bytes"
	"encoding/json"
	"fmt"
	"io"
	"net/http"
)

func GetIssueData(url string) ([]byte, error) {
	res, err := http.Get(url)
	if err != nil {
		return nil, fmt.Errorf("error creating request: %w", err)
	}
	defer res.Body.Close()

	data, err := io.ReadAll(res.Body)
	if err != nil {
		return nil, fmt.Errorf("error reading response: %w", err)
	}
	return data, nil
}

func Prettify(data []byte) (string, error) {
	var prettyJSON bytes.Buffer
	err := json.Indent(&prettyJSON, data, "", "  ")
	if err != nil {
		return "", fmt.Errorf("error prettifying json: %w", err)
	}
	return prettyJSON.String(), nil
}
