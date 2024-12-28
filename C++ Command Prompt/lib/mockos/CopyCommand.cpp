#include "../include/mockos/CopyCommand.h"
#include <sstream>

enum Errors {
	SUCCESS = 0,
	INVALID_FILE_NAME = -7,
	COPY_NOT_ADDED = -8,
	INVALID_ARGUMENTS = -9
};

// runs the command
int CopyCommand::execute(string command) {
	// split the arguments into two words: the original and new file names
	istringstream stream(command);
	string fileName, fileCopyName, fileExtension;
	// attempt to grab the first and second file names, return an error if unsuccessful
	if (!(stream >> fileName >> fileCopyName)) {
		return INVALID_ARGUMENTS;
	}
	// grab the file extension
	size_t periodPos = fileName.find('.');
	if (periodPos != string::npos) {
		fileExtension = fileName.substr(periodPos);
	}
	// if there is an error grabbing the file extension, return an error
	else {
		return INVALID_FILE_NAME;
	}
	// add the file extension to the copy name
	fileCopyName += fileExtension;
	// open the file
	AbstractFile* currentFile = fileSystem->openFile(fileName);
	// if there is an error opening it, return an error
	if (currentFile == nullptr) {
		fileSystem->closeFile(currentFile);
		return INVALID_FILE_NAME;
	}
	// clone the file using the new copy name
	AbstractFile* copiedFilePtr = currentFile->clone(fileCopyName);
	// add the copy file and return an error if it can't be added
	if (fileSystem->addFile(fileCopyName, copiedFilePtr) != SUCCESS) {
		fileSystem->closeFile(currentFile);
		return COPY_NOT_ADDED;
	}
	// close the original file
	fileSystem->closeFile(currentFile);
	return SUCCESS;
}
// displays info about the command
void CopyCommand::displayInfo() {
	cout << "cp creates a copy of a file. cp can be invoked with the command : cp <file_to_be_copied> <name_of_copy_no_extensions>" << endl;
}