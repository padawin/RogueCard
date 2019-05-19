package action

import "fmt"

type binFunc func(string, []string) (int, string)

func Run(action string, args []string) {
	actions := map[string]binFunc{
		"create":  Create,
		"add-row": AddRow,
		"fields":  ListFields,
	}

	actionCb, exists := actions[action]
	if !exists {
		fmt.Println("Unknown action " + action)
		return
	} else if len(args) == 0 {
		fmt.Println("File path needed as first argument")
		return
	}
	filename := args[0]
	if res, msg := ValidateFile(filename, action != "create"); !res {
		fmt.Println(msg)
		return
	}
	res, msg := actionCb(filename, args[1:])
	if res != 0 {
		fmt.Println(msg)
	}
}
