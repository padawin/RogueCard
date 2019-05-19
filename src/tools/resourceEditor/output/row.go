package output

import (
	"bytes"
	"fmt"
)

import (
	"../common"
)

func RowToString(row common.Row) string {
	var buffer bytes.Buffer
	for index, val := range row.Values {
		if index > 0 {
			buffer.WriteString(" ")
		}
		if val.Type.Type == common.StringField {
			buffer.WriteString(fmt.Sprintf("\"%s\"", val.Value))
		} else {
			buffer.WriteString(val.Value)
		}
	}
	buffer.WriteString("\n")
	return buffer.String()
}
