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
