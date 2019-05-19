package action

import (
	"fmt"
	"os"
)

const ERR_FILE_NOT_FOUND = "File %s not found"
const ERR_FILE_EXISTS = "File %s already exists"

const ERR_INVALID_ARGS_LEN = "Invalid numbers of arguments (provided %d, expected %d)"

func ValidateFile(filename string, existingFile bool) (bool, string) {
	exists := fileExists(filename)
	errors := map[bool]string{
		false: ERR_FILE_NOT_FOUND,
		true:  ERR_FILE_EXISTS,
	}
	if exists != existingFile {
		msg := fmt.Sprintf(errors[exists], filename)
		return false, msg
	}
	return true, ""
}

func ValidateArgs(args []string, expectedNbArgs int) (bool, string) {
	nbArgs := len(args)
	if nbArgs != expectedNbArgs {
		msg := fmt.Sprintf(ERR_INVALID_ARGS_LEN, nbArgs, expectedNbArgs)
		return false, msg
	}
	return true, ""
}

func fileExists(filename string) bool {
	_, err := os.Stat(filename)
	return err == nil
}
