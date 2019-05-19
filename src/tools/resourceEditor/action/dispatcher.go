package action

import "fmt"

type binFunc func([]string) (int, string)

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
	}
	if res, msg := ValidateFile(args[0], action != "create"); !res {
		fmt.Println(msg)
		return
	}
	res, msg := actionCb(args)
	if res != 0 {
		fmt.Println(msg)
	}
}
