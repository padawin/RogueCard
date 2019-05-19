package action

import (
	"bufio"
	"fmt"
	"os"

	"../common"
	"../input"
	"../output"
)

func AddRow(filename string, _ []string) (int, string) {
	file, err := os.OpenFile(filename, os.O_RDWR|os.O_APPEND, 0644)
	defer file.Close()
	if err != nil {
		return 3, err.Error()
	}

	scanner := bufio.NewScanner(file)

	fields, rows, comments, err := common.LoadFile(scanner)
	if err != nil {
		return 4, err.Error()
	}

	newRow := input.PromptRow(fields)
	newRow.Line = maxRowLine(rows[len(rows)-1], comments[len(comments)-1]) + 1
	rows = append(rows, newRow)
	_, err = file.WriteString(output.RowToString(newRow))
	if err != nil {
		fmt.Println(err.Error())
	}

	return 0, ""
}

func maxRowLine(row common.Row, comment common.CommentRow) int {
	if row.Line < comment.Line {
		return comment.Line
	} else {
		return row.Line
	}
}
