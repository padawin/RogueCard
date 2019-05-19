package action

import (
	"bufio"
	"fmt"
	"os"

	"../common"
)

func AddRow(args []string) (int, string) {
	if res, msg := ValidateArgs(args, 1, true); !res {
		return 1, msg
	}
	filename := args[0]
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
