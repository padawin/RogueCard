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

func PromptDefaultValue(field common.Field) (val string) {
	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Print("Default value: ")
		scanner.Scan()
		val = scanner.Text()
		if field.Type == common.IntField {
			_, err := strconv.Atoi(val)
			if err != nil {
				continue
			}
		} else if field.Type == common.BoolField {
			if val != "0" && val != "1" {
				continue
			}
		}
		break
	}
	return val
}

func PromptFieldPosition(maxPos int) int {
	scanner := bufio.NewScanner(os.Stdin)
	for {
		fmt.Printf("Position (between 0 and %d): ", maxPos)
		scanner.Scan()
		pos, err := strconv.Atoi(scanner.Text())
		if err == nil && pos >= 0 && pos <= maxPos {
			return pos
		}
	}
}

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
		if err == nil && val > 0 {
			return val
		}
	}
}
