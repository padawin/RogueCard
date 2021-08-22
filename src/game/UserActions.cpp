#include "UserActions.hpp"
#include <fstream>
#include <cstdlib>
#include <cstring>
using std::ifstream;


const int MAX_CHAR_COMMAND = 128;
const int MAX_CHARS_PER_LINE = 134; // 128 + 6
const char* const DELIMITER = ";";

UserActions::UserActions(std::shared_ptr<InputHandler> inputHandler) :
	m_inputHandler(inputHandler),
	m_mMappings({})
{}

void UserActions::add(std::string name, S_Command c) {
	if (!m_mMappings.count(name)) {
		std::vector<S_Command> tempCommands;
		m_mMappings[name] = tempCommands;
	}

	m_mMappings[name].push_back(c);
}

ActionState UserActions::getActionState(std::string name) {
	if (!m_mMappings.count(name)) {
		return ActionState::ACTION_UNKNOWN;
	}

	std::vector<S_Command> commands = m_mMappings[name];
	ActionState ret = ActionState::ACTION_REST;
	for (unsigned int c = 0; c < commands.size(); c++) {
		if (commands[c].type == KEYBOARD_KEY) {
			if (m_inputHandler->isKeyPressed(commands[c].key)) {
				ret = ActionState::ACTION_PRESSED;
			}
			else if (m_inputHandler->isKeyReleased(commands[c].key)) {
				ret = ActionState::ACTION_RELEASED;
			}
			else if (m_inputHandler->isKeyDown(commands[c].key)) {
				ret = ActionState::ACTION_DOWN;
			}
		}
		else if (commands[c].type == MOUSE_BUTTON) {
			if (m_inputHandler->isMouseButtonReleased(commands[c].key)) {
				ret = ActionState::ACTION_RELEASED;
			}
			else if (m_inputHandler->isMouseButtonPressed(commands[c].key)) {
				ret = ActionState::ACTION_PRESSED;
			}
		}

		if (ret != 0) {
			break;
		}
	}

	return ret;
}

bool UserActions::is(std::string name, int states) {
	return getActionState(name) & states;
}

int UserActions::setActionsFromFile(const char* mappingFile) {
	// create a file-reading object
	ifstream fin;
	fin.open(mappingFile); // open a file
	if (!fin.good()) {
		fin.close();
		return NO_FILE_FOUND; // exit if file not found
	}

	// read each line of the file
	while (!fin.eof()) {
		// read an entire line into memory
		char buf[MAX_CHARS_PER_LINE];
		// @check too long lines
		fin.getline(buf, MAX_CHARS_PER_LINE);

		if (buf[0] == '\0' || buf[0] == '#') {
			continue;
		}

		char commandName[MAX_CHAR_COMMAND];
		char* token;
		int type;
		int value;

		// @TODO Check buffer overflow
		token = strtok(buf, DELIMITER);
		strncpy(commandName, token, MAX_CHAR_COMMAND - 1);

		// @TODO check missing values
		token = strtok(0, DELIMITER);
		if (token == 0) {
			return NO_TYPE_FOUND;
		}

		type = atoi(token);
		token = strtok(0, DELIMITER);
		if (token == 0) {
			return NO_VALUE_FOUND;
		}

		value = atoi(token);
		token = strtok(0, DELIMITER);

		S_Command c;
		if (type >= 0 && type < InputType::NULL_TYPE) {
			c.type = (InputType) type;
			c.key = value;
		}
		else {
			return INVALID_TYPE;
		}
		add(commandName, c);
	}

	fin.close();
	return 0;
}
