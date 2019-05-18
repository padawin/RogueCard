package action

import "fmt"

func Create(args []string) (int, string) {
	nb_args := len(args)
	expected_nb_args := 1
	if nb_args != expected_nb_args {
		msg := fmt.Sprintf("Invalid numbers of arguments (provided %d, expected %d)", nb_args, expected_nb_args)
		return 1, msg
	}
	fmt.Println("Create file", args[0])
	return 0, ""
}
