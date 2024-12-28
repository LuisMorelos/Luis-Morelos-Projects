#include "../include/mockos/DisplayCommand.h"

enum Errors {
	SUCCESS = 0,
	INVALID_ARGUMENTS = -3,
	INVALID_FILENAME = -4
};

// runs the command
int DisplayCommand::execute(string command) {
	// variables for later us
	string beforeSpace;
	bool notFormatted = false;
	AbstractFile* currentFile;
	// find the position of the space if any
	size_t spacePos = command.find(' ');
	// check if a space exists in the string
	if (spacePos != string::npos) {
		beforeSpace = command.substr(0, spacePos);
		string afterSpace = command.substr(spacePos + 1);
		// check if the arguments are valid
		if (afterSpace != "-d") {
			return INVALID_ARGUMENTS;
		}
		notFormatted = true;
	}
	// open the file based on if we are formatting it or not
	if (notFormatted == true) {
		currentFile = fileSystem->openFile(beforeSpace);
	}
	else {
		currentFile = fileSystem->openFile(command);
	}
	// check if the file was opened correctly
	if (currentFile == nullptr) {
		return INVALID_FILENAME;
	}
	// if it doesn't need formatting just display the contents directly
	if (notFormatted == true) {
		vector<char> fileContents = currentFile->read();
		for (int i = 0; i < fileContents.size(); i++) {
			cout << fileContents[i];
		}
		cout << endl;
	}
	// if it does require formatting, use the basic display visitor
	else {
		AbstractFileVisitor* basicDisplay = new BasicDisplayVisitor();
		currentFile->accept(basicDisplay);
		delete basicDisplay;
	}
	// close the file and return success
	fileSystem->closeFile(currentFile);
	return SUCCESS;
}
// displays info about the command
void DisplayCommand::displayInfo() {
	cout << "ds displays the contents of a file. ds can be invoked with the command : ds <filename>" << endl;
	cout << "ds can also display the contents without formatting them. this can be invoked with the command : ds <filename> -d" << endl;
}