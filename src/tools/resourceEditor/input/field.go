package input

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strconv"
	"strings"
)

import (
	"../common"
)

func PromptField(field *common.Field) bool {
	scanner := bufio.NewScanner(os.Stdin)
	field.Name = promptName(scanner)
	if field.Name == "" {
		return false
	}

	field.Type = promptType(scanner)

	if field.Type == common.StringField {
		field.Size = promptStringLength(scanner)
	} else if field.Type == common.BoolField {
		field.Size = 2
	}

	return true
}

func promptName(scanner *bufio.Scanner) string {
	fmt.Print("Field name (Empty to finish): ")
	scanner.Scan()
	return strings.TrimSpace(scanner.Text())
}

func promptType(scanner *bufio.Scanner) common.FieldType {
	var buffer bytes.Buffer
	var prefix = ""
	for typeID, typeLabel := range common.FieldTypeLabels {
		label := "%s%d: %s"
		buffer.WriteString(fmt.Sprintf(label, prefix, typeID, typeLabel))
		if prefix == "" {
			prefix = ", "
		}
	}
	for {
		fmt.Printf("Field type (%s): ", buffer.String())
		scanner.Scan()
		val, err := strconv.Atoi(strings.TrimSpace(scanner.Text()))
		if err != nil || val >= len(common.FieldTypeLabels) {
			continue
		}
		return common.FieldType(val)
	}
}

func promptStringLength(scanner *bufio.Scanner) int {
	for {
		fmt.Printf("Max length: ")
		scanner.Scan()
		val, err := strconv.Atoi(scanner.Text())
		if err != nil || val <= 0 {
			continue
		}
		return val
	}
}
