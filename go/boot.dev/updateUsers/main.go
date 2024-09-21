
package main

type User struct {
	Name string
	Membership
}
type Membership struct {
	MessageCharLimit int
	Type string
}

func newUser(name string, membershipType string) User {
	char := 100
	if membershipType == "premium" {
		char = 1000
	}
	return User {
		Name: name,
		Membership: Membership {
			MessageCharLimit: char,
			Type: membershipType,
		},
	}
}
