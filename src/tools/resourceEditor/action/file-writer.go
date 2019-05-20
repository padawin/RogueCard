package action

import (
	"fmt"
	"os"
)

import (
	"../common"
	"../output"
)

func WriteMetas(file *os.File, fields []common.Field) {
	file.WriteString("# %META START%\n")
	for _, field := range fields {
		file.WriteString(fmt.Sprintf(
			"# %%META FIELD%% %s %d %d\n", field.Name, field.Type, field.Size,
		))
	}
	file.WriteString("# %META END%\n")
}

func WriteContent(file *os.File, rows []common.Row, comments []common.CommentRow) {
	nbRows := len(rows) + len(comments)
	currRow := 0
	currComment := 0
	for i := 1; i <= nbRows; i++ {
		var line string
		if currRow < len(rows) && rows[currRow].Line == i {
			line = output.RowToString(rows[currRow])
			currRow++
		} else if currComment < len(comments) && comments[currComment].Line == i {
			line = fmt.Sprintf("%s\n", comments[currComment].Value)
			currComment++
		} else {
			fmt.Println("Oops")
		}
		file.WriteString(line)
	}
}
