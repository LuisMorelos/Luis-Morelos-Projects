#include "../include/mockos/RemoveCommand.h"

// runs the remove command
int RemoveCommand::execute(string command) {
	return fileSystem->deleteFile(command);
}
// prints remove command info
void RemoveCommand::displayInfo() {
	cout << "rm removes a file from the file system. rm can be invoked with the command : rm <filename>" << endl;
}