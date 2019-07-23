package main

import "fmt"
import "os"
import "./action"

func main() {
	if len(os.Args) == 1 {
		fmt.Println("Action missing")
		return
	}

	actionName := os.Args[1]
	// @XXX How to know where is `Run` defined?
	action.Run(actionName, os.Args[2:])
}
