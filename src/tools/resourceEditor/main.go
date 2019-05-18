package main

import "os"
import "./action"

func main() {
	actionName := os.Args[1]
	// @XXX How to know where is `Run` defined?
	action.Run(actionName, os.Args[2:])
}
