package action

import (
	"bufio"
	"bytes"
	"errors"
	"fmt"
	"regexp"
)

import (
	"../common"
)

func LoadFile(
	scanner *bufio.Scanner,
) (
	fields []common.Field, rows []common.Row, commentRows []common.CommentRow, err error,
) {
	fields, metaErr := LoadMeta(scanner)
	if metaErr != nil {
		err = metaErr
		return
	}

	// read file
	rows, commentRows, err = loadRows(scanner, fields)
	if err != nil {
		return
	}
	return
}

func LoadMeta(scanner *bufio.Scanner) ([]common.Field, error) {
	var fields []common.Field
	var expected, line string
	if !scanner.Scan() {
		return fields, errors.New("Can't read line")
	}
	line = scanner.Text()
	expected = "# %META START%"
	if line != expected {
		msg := fmt.Sprintf("Expected \"%s\", got \"%s\"", expected, line)
		return fields, errors.New(msg)
	}

	var meta_end_found bool = false
	var meta_end = "# %META END%"
	for !meta_end_found {
		if !scanner.Scan() {
			return fields, errors.New("Can't read line")
		}
		line = scanner.Text()
		if line == meta_end {
			meta_end_found = true
		} else {
			var field common.Field
			cnt, err := fmt.Sscanf(
				line,
				"# %%META FIELD%% %s %d %d\n",
				&field.Name,
				&field.Type,
				&field.Size,
			)
			if cnt != 3 {
				return fields, errors.New(
					fmt.Sprintf("Invalid Meta field line: %s", line),
				)
			} else if err != nil {
				return fields, err
			}
			fields = append(fields, field)
		}
	}

	return fields, nil
}

func loadRows(
	scanner *bufio.Scanner, fields []common.Field,
) ([]common.Row, []common.CommentRow, error) {
	var rows []common.Row
	var commentRows []common.CommentRow
	var currLine int = 1
	regex := getLineExpectedRegex(fields)
	r := regexp.MustCompile(regex)
	for scanner.Scan() {
		line := scanner.Text()
		if line[0] == '#' {
			commentRows = append(commentRows, common.CommentRow{currLine, line})
		} else {
			row, valid := lineToRow(line, r, fields)
			row.Line = currLine
			if !valid {
				return nil, nil, errors.New(fmt.Sprintf("Invalid line %d: %s", currLine, line))
			}
			rows = append(rows, row)
		}
		currLine++
	}
	return rows, commentRows, nil
}

func getLineExpectedRegex(fields []common.Field) string {
	var buffer bytes.Buffer
	buffer.WriteString("^")
	for idx, field := range fields {
		if idx > 0 {
			buffer.WriteString(" ")
		}
		if field.Type == common.StringField {
			buffer.WriteString(fmt.Sprintf("\"(.{1,%d})\"", field.Size))
		} else if field.Type == common.BoolField {
			buffer.WriteString("([01])")
		} else if field.Type == common.IntField {
			buffer.WriteString("(\\d+)")
		}
	}
	buffer.WriteString("$")
	return buffer.String()
}

func lineToRow(
	line string, formatRegex *regexp.Regexp, fields []common.Field,
) (row common.Row, valid bool) {
	matches := formatRegex.FindStringSubmatch(line)
	if len(matches) != len(fields)+1 { // the extra match is the whole string
		return row, false
	}

	for i := 0; i < len(fields); i++ {
		value := matches[i+1]
		row.Values = append(row.Values, common.RowValue{&fields[i], value})
	}
	return row, true
}
