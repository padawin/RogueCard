package action

import (
	"os"
)

const ERR_INVALID_ARGS_LEN = "Invalid numbers of arguments (provided %d, expected %d)"

func FileExists(filename string) bool {
	_, err := os.Stat(filename)
	return err == nil
}
