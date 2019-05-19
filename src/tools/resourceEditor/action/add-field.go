package action

import (
	"bufio"
	"io"
	"os"
)

import (
	"../common"
	"../input"
)

func AddField(filename string, args []string) (int, string) {
	file, err := os.OpenFile(filename, os.O_RDWR, 0644)
	if err != nil {
		return 3, err.Error()
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	fields, rows, comments, err := LoadFile(scanner)
	if err != nil {
		return 4, err.Error()
	}

	var field common.Field
	if input.PromptField(&field) {
		position := input.PromptFieldPosition(len(fields))
		defaultVal := input.PromptDefaultValue(field)
		rowValue := common.RowValue{&field, defaultVal}
		// @XXX Duplicated with inside loop,
		fields = append(fields, field)
		copy(fields[position+1:], fields[position:])
		fields[position] = field
		for i := 0; i < len(rows); i++ {
			values := rows[i].Values
			values = append(values, rowValue)
			copy(values[position+1:], values[position:])
			values[position] = rowValue
			rows[i].Values = values
		}
		file.Seek(0, io.SeekStart)
		WriteMetas(file, fields)
		WriteContent(file, rows, comments)
	}

	return 0, ""
}
