package action

import (
	"fmt"
	"os"

	"../common"
	"../input"
)

func Create(filename string, _ []string) (int, string) {
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
