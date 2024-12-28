#include "../include/mockos/CatCommand.h"

enum Errors {
	SUCCESS = 0,
	INVALID_ARGUMENTS = -3,
	INVALID_FILENAME = -4,
	ERROR_APPENDING = -5,
	ERROR_WRITING = -6
};

// runs the cat command
int CatCommand::execute(string command) {
	// variables for later
	bool hasAppend = false;
	string beforeSpace;
	AbstractFile* currentFile;
	string totalUserInput;
	// find the position of the space if any
	size_t spacePos = command.find(' ');
	// check if a space exists in the string
	if (spacePos != string::npos) {
		beforeSpace = command.substr(0, spacePos);
		string afterSpace = command.substr(spacePos + 1);
		// check if the arguments are valid
		if (afterSpace != "-a") {
			return INVALID_ARGUMENTS;
		}
		hasAppend = true;
	}
	// obtain a pointer to the file
	if (hasAppend == true) {
		currentFile = fileSystem->openFile(beforeSpace);
	}
	else {
		currentFile = fileSystem->openFile(command);
	}
	// check if the pointer was obtained successfully
	if (currentFile == nullptr) {
		return INVALID_FILENAME;
	}
	// if we need to append, display the contents of the file
	if (hasAppend == true) {
		vector<char> fileContents = currentFile->read();
		for (int i = 0; i < fileContents.size(); i++) {
			cout << fileContents[i];
		}
		cout << endl;
	}
	// repeatedly prompt user to write into the file
	cout << "Enter data you would like to write to the file. Enter :wq to save and quit. Enter :q to quit without saving." << endl;
	while (true) {
		string currentUserInput = "";
		getline(cin, currentUserInput);
		// if the user quits
		if (currentUserInput == ":q") {
			return SUCCESS;
		}
		// if the user saves and quits
		else if (currentUserInput == ":wq") {
			// convert user input into a vector of chars
			vector<char> charVector(totalUserInput.begin(), totalUserInput.end() - 1);
			// if the user wants to append to the file
			if (hasAppend == true) {
				// check if the append was successful
				if (currentFile->append(charVector) != SUCCESS) {
					fileSystem->closeFile(currentFile);
					return ERROR_APPENDING;
				}
				fileSystem->closeFile(currentFile);
				return SUCCESS;
			}
			// if the user just wants to write to the file
			// check if the write was successful
			if (currentFile->write(charVector) != SUCCESS) {
				fileSystem->closeFile(currentFile);
				return ERROR_WRITING;
			}
			fileSystem->closeFile(currentFile);
			return SUCCESS;
		}
		// save the user inputs into one large string and add a new line character
		totalUserInput += currentUserInput + "\n";
	}
}
// displays info about cat command
void CatCommand::displayInfo() {
	cout << "cat allows you to write to a file, replacing its current contents. cat can be invoked using the command : cat <filename>" << endl;
	cout << "cat also allows you to write without replacing the current contents. this can be invoked using the command : cat <filename> -a" << endl;
}