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

func ListFields(filename string, _ []string) (int, string) {
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
