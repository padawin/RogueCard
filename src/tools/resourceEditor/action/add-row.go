package action

import (
	"bufio"
	"fmt"
	"os"

	"../common"
)

const ERR_FILE_NOT_FOUND = "File %s not found"

func AddRow(args []string) (int, string) {
	nb_args := len(args)
	expected_nb_args := 1
	if nb_args != expected_nb_args {
		msg := fmt.Sprintf(ERR_INVALID_ARGS_LEN, nb_args, expected_nb_args)
		return 1, msg
	}
	filename := args[0]
	if !FileExists(filename) {
		msg := fmt.Sprintf(ERR_FILE_NOT_FOUND, filename)
		return 2, msg
	}

	file, err := os.Open(filename)
	defer file.Close()
	if err != nil {
		return 3, err.Error()
	}

	scanner := bufio.NewScanner(file)

	fields, rows, comments, err := common.LoadFile(scanner)
	if err != nil {
		return 4, err.Error()
	}
	fmt.Println(fields, rows, comments)

	file.Close()
	return 0, ""
}
