package action

import (
	"fmt"
	"os"

	"../common"
	"../input"
)

const ERR_FILE_EXISTS = "File %s already exists"

func Create(args []string) (int, string) {
	nb_args := len(args)
	expected_nb_args := 1
	if nb_args != expected_nb_args {
		msg := fmt.Sprintf(ERR_INVALID_ARGS_LEN, nb_args, expected_nb_args)
		return 1, msg
	}
	filename := args[0]
	if FileExists(filename) {
		msg := fmt.Sprintf(ERR_FILE_EXISTS, filename)
		return 2, msg
	}

	file, err := os.Create(filename)
	if err != nil {
		return 3, err.Error()
	}
	defer file.Close()

	fields := promptFields()
	if len(fields) == 0 {
		defer os.Remove(filename)
		return 0, "Cancelled"
	}

	saveFile(file, fields)
	return 0, ""
}

func promptFields() []common.Field {
	var fields []common.Field
	for {
		var field common.Field
		res := input.PromptField(&field)
		if !res {
			break
		}
		fields = append(fields, field)
	}

	return fields
}

func saveFile(file *os.File, fields []common.Field) {
	file.WriteString("# %META START%\n")
	for _, field := range fields {
		file.WriteString(fmt.Sprintf(
			"# %%META FIELD%% %s %d %d\n", field.Name, field.Type, field.Size,
		))
	}
	file.WriteString("# %META END%\n")
	file.Close()
}
