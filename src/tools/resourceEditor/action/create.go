package action

import (
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

	WriteMetas(file, fields)
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
