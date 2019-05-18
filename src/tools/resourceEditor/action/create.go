package action

import (
	"fmt"
	"os"
)

var ERR_INVALID_ARGS_LEN = "Invalid numbers of arguments (provided %d, expected %d)"
var ERR_FILE_EXISTS = "File %s already exists"

func Create(args []string) (int, string) {
	nb_args := len(args)
	expected_nb_args := 1
	if nb_args != expected_nb_args {
		msg := fmt.Sprintf(ERR_INVALID_ARGS_LEN, nb_args, expected_nb_args)
		return 1, msg
	}
	filename := args[0]
	if fileExists(filename) {
		msg := fmt.Sprintf(ERR_FILE_EXISTS, filename)
		return 2, msg
	}
	return 0, ""
}

func fileExists(filename string) bool {
	_, err := os.Stat(filename)
	return err == nil
}
