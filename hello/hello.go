package main

import (
	"fmt"
	"github.com/LVKinyanjui/Golang/greetings"
)

func main() {
	// Get a greeting message and print it
	message := greetings.Hello("Devin")
	fmt.Println(message)
}
