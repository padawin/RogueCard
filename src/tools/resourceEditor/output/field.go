package output

import (
	"fmt"
)

import (
	"../common"
)

func FieldToString(field common.Field) string {
	return fmt.Sprintf(
		"%s (%d - %s)",
		field.Name, field.Type, common.FieldTypeLabels[field.Type],
	)
}
