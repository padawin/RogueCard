package common

import (
	"bufio"
	"errors"
	"fmt"
)

func LoadFile(
	scanner *bufio.Scanner,
) (
	fields []Field, rows []Row, commentRows []CommentRow, err error,
) {
	fields, metaErr := loadMeta(scanner)
	if metaErr != nil {
		err = metaErr
		return
	}

	return
}

func loadMeta(scanner *bufio.Scanner) ([]Field, error) {
	var fields []Field
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
			var field Field
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
			} else {
				fields = append(fields, field)
			}
		}
	}

	return fields, nil
}
