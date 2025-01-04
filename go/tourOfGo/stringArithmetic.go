package main

import (
	"io"
	"os"
	"strings"
)

type rot13Reader struct {
	r io.Reader
}

func (rt *rot13Reader) Read(b []byte) (int, error) {
	n, err := rt.r.Read(b)
	if err != nil {
		return n, err
	}
	// rot13
	for i := 0; i < n; i++ {
		if 'a' <= b[i] && b[i] <= 'z' { // single quotes for runes, double for strings
			b[i] = byte((int(b[i]-'a')+13)%26 + 'a')
		} else if 'A' <= b[i] && b[i] <= 'Z' {
			b[i] = byte((int(b[i]-'A')+13)%26 + 'A')
		}
	}
	return n, nil
}

func main() {
	s := strings.NewReader("Lbh penpxrq gur pbqr!")
	r := rot13Reader{s}
	io.Copy(os.Stdout, &r)
}
