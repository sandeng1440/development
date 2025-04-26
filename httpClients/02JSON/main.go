package main

import "sync"

const issueList = `
[
	{
		"id": 0,
		"name": "Fix the thing",
		"estimate": 0.5,
		"completed": false
	},
	{
		"id": 1,
		"name": "Unstick the widget",
		"estimate": 0.9,
		"completed": true
	}
]
`
const userObject = `{
	"name": "Romero Bughdan",
	"role": "Dev",
	"remote": false
}
`
