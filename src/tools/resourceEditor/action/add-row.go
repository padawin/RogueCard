package action

import (
	"bufio"
	"errors"
	"fmt"
	"os"

	"../common"
)

const ERR_FILE_NOT_FOUND = "File %s not found"

func AddRow(args []string) (int, string) {
	nb_args := len(args)
	expected_nb_args := 1
	if nb_args != expected_nb_args {
		msg := fmt.Sprintf(ERR_INVALID_ARGS_LEN, nb_args, expected_nb_args)
		return 1, msg
	}
	filename := args[0]
	if !FileExists(filename) {
		msg := fmt.Sprintf(ERR_FILE_NOT_FOUND, filename)
		return 2, msg
	}

	file, err := os.Open(filename)
	defer file.Close()
	if err != nil {
		return 3, err.Error()
	}

	scanner := bufio.NewScanner(file)

	fields, err := loadMeta(scanner)
	if err != nil {
		return 4, err.Error()
	}

	fmt.Println(fields)

	file.Close()
	return 0, ""
}

func loadMeta(scanner *bufio.Scanner) ([]common.Field, error) {
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
			} else {
				fields = append(fields, field)
			}
		}
	}

	return fields, nil
}
