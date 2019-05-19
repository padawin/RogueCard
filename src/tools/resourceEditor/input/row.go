package input

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

import (
	"../common"
)

func PromptRow(fields []common.Field) (row common.Row) {
	scanner := bufio.NewScanner(os.Stdin)
	for _, field := range fields {
		rowValue := promptField(scanner, field)
		row.Values = append(row.Values, rowValue)
	}
	return
}

func promptField(scanner *bufio.Scanner, field common.Field) common.RowValue {
	var fieldType string
	if field.Type == common.StringField {
		fieldType = fmt.Sprintf("String, max %d char", field.Size)
	} else if field.Type == common.BoolField {
		fieldType = "1 or 0"
	} else if field.Type == common.IntField {
		fieldType = "Number"
	}
	promptText := fmt.Sprintf("%s (%s): ", field.Name, fieldType)
	for {
		fmt.Print(promptText)
		scanner.Scan()
		value := strings.TrimSpace(scanner.Text())
		if valid(field, value) {
			return common.RowValue{&field, value}
		}
	}
}

func valid(field common.Field, value string) bool {
	if field.Type == common.StringField {
		return len(value) < field.Size
	} else if field.Type == common.BoolField {
		return value == "0" || value == "1"
	} else if field.Type == common.IntField {
		_, err := strconv.Atoi(value)
		return err == nil
	} else {
		return false
	}
}
