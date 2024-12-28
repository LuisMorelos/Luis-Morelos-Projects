#include "../include/mockos/CommandPrompt.h"
#include <sstream>

enum Errors {
    SUCCESS = 0,
    USER_QUIT = 9
};

// sets the file system member variable to be the file system given
void CommandPrompt::setFileSystem(AbstractFileSystem* inputFileSystem) {
	fileSystem = inputFileSystem;
}
// sets the file factory member variable to be the file factory given
void CommandPrompt::setFileFactory(AbstractFileFactory* inputFileFactory) {
	fileFactory = inputFileFactory;
}
// adds a command to the possible commands map member variable and returns success
int CommandPrompt::addCommand(string commandString, AbstractCommand* inputCommand) {
	commandObjects[commandString] = inputCommand;
    return SUCCESS;
}
// prints out all the names of the commands in the possible commands map member variable
void CommandPrompt::listCommands() {
	for (auto& pair : commandObjects) {
		cout << pair.first << endl;
	}
}
// repeatedly prompts the user to enter a command, help, or quit
string CommandPrompt::prompt() {
    cout << "Enter a command, q to quit, help for a list of commands, or\n"
        << "help followed by a command name for more information about\n"
        << "that command." << endl;
    cout << "$  ";
    string userInput;
    getline(cin, userInput);
    return userInput;
}
// runs the command prompt
int CommandPrompt::run() {
    // infinite loop
    while (true) {
        string input = prompt();

        // if the input is q, quit and return a unique non-zero value
        if (input == "q") {
            return USER_QUIT;
        }

        // if the input is help, use the list commands method
        if (input == "help") {
            listCommands();
            continue;
        }

        // if it doesn't match the previous answers, check to see if there is more than one argument
        // if there is only one argument
        if (input.find(' ') == string::npos) {
            auto it = commandObjects.find(input);
            // if there is only one argument, try to see if it's a command and run it. If not, return a unique non-zero value
            if (it != commandObjects.end()) {
                int success = it->second->execute("");
                if (success != SUCCESS) {
                    // if the command exists but did not run correctly
                    cout << "Command execution failed" << endl;
                }
            }
            else {
                // if the command does not exist
                cout << "Command not found" << endl;
            }
        }
        // if there is more than one argument
        else {
            istringstream iss(input);
            string command = "";
            iss >> command;

            // if the first word is help, try to see if the next word is a command and print its information
            if (command == "help") {
                string commandName = "";
                iss >> commandName;
                auto it = commandObjects.find(commandName);
                if (it != commandObjects.end()) {
                    it->second->displayInfo();
                }
                else {
                    // if the command is not found
                    cout << "Command not found for help" << endl;
                }
            }
            // if the first word is not help
            else {
                // try to find a command that matches the first word
                auto it = commandObjects.find(command);
                if (it != commandObjects.end()) {
                    string arguments = "";
                    // if the command is found, run the command with the second word as input
                    getline(iss >> ws, arguments);
                    int success = it->second->execute(arguments);
                    if (success != SUCCESS) {
                        // if the command cannot run correctly
                        cout << "Command execution failed" << endl;
                    }
                }
                else {
                    // if the command was not found
                    cout << "Command not found" << endl;
                }
            }
        }
    }
}