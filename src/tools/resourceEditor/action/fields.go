package action

import (
	"bufio"
	"fmt"
	"os"
)

import (
	"../common"
	"../output"
)

func ListFields(args []string) (int, string) {
	if res, msg := ValidateArgs(args, 1); !res {
		return 1, msg
	}
	filename := args[0]
	file, err := os.Open(filename)
	if err != nil {
		return 3, err.Error()
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	fields, err := common.LoadMeta(scanner)
	if err != nil {
		return 4, err.Error()
	}

	for index, field := range fields {
		fmt.Printf("%d - %s\n", index, output.FieldToString(field))
	}
	return 0, ""
}
