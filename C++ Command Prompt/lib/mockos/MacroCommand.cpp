#include "../include/mockos/MacroCommand.h"

enum Errors {
	SUCCESS = 0,
	INVALID_ARGUMENTS = -3,
	COMMANDS_NOT_RUN = -6
};

// runs the command
int MacroCommand::execute(string command) {
	// call the parsing strategy to parse the given command
	vector<string> commandArgs = parsingStrategy->parse(command);
	// check if the amount of commands matches the amount of arguments passed
	if (commandArgs.size() != primitiveCommands.size()) {
		return INVALID_ARGUMENTS;
	}
	// run the commands one by one from the primitive commands member variable
	for (int i = 0; i < primitiveCommands.size(); i++) {
		// check if the command was run successfully
		if (primitiveCommands[i]->execute(commandArgs[i]) != SUCCESS) {
			return COMMANDS_NOT_RUN;
		}
	}
	// all commands were run successfully
	return SUCCESS;
}
// displays command info
void MacroCommand::displayInfo() {
	cout << "macro command takes in multiple commands and parses them to run all commands in order." << endl;
	cout <<	"macro command can be invoked by typing multiple commands in a row" << endl;
}
// adds a command to the member variable vector of possible commands
void MacroCommand::addCommand(AbstractCommand* ac) {
	primitiveCommands.push_back(ac);
}
// sets the parsing strategy member variable
void MacroCommand::setParseStrategy(AbstractParsingStrategy* ps) {
	parsingStrategy = ps;
}