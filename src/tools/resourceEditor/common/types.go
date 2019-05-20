package common

type FieldType int

const (
	StringField FieldType = iota
	IntField
	BoolField
)

var FieldTypeLabels []string = []string{
	"String",
	"Int",
	"Bool",
}

type Field struct {
	Name string
	Type FieldType
	Size int
}

type RowValue struct {
	Type  *Field
	Value string
}

type Row struct {
	Line   int
	Values []RowValue
}

type CommentRow struct {
	Line  int
	Value string
}
