package main

import (
	"fmt"
	"log"
	"github.com/LVKinyanjui/Golang/greetings"
)

func main() {
    // Set properties of the predefined Logger, including
    // the log entry prefix and a flag to disable printing
    // the time, source file, and line number.
    log.SetPrefix("greetings: ")
    log.SetFlags(0)

	// Request a greeting message
	message, err := greetings.Hello("")

	// If an error was returned, print to console and exit
	if err != nil {
		log.Fatal(err)
	}

	// If no error, print the message to console
	fmt.Println(message)
}
