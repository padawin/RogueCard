package action

import "fmt"

type binFunc func([]string) (int, string)

func Run(action string, args []string) {
	actions := map[string]binFunc{
		"create": Create,
	}

	actionCb, exists := actions[action]
	if !exists {
		fmt.Println("Unknown action " + action)
		return
	}
	res, msg := actionCb(args)
	if res != 0 {
		fmt.Println(msg)
	}
}
