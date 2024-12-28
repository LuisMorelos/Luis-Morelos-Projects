#include "../include/mockos/LSCommand.h"
#include <iomanip>

enum Errors {
    SUCCESS = 0,
    INVALID_ARGUMENT = -1
};

// runs the ls command
int LSCommand::execute(string command) {
	// use the getFileNames function from the file system to create a set of all file names
	set<string> fileNames = fileSystem->getFileNames();
	// print files and their metadata if given -m
    if (command == "-m") {
        AbstractFileVisitor* metadataDisplay = new MetadataDisplayVisitor();
        // print metadata by opening the file to get a pointer, calling the metadata visitor, and then closing the file
        for (set<string>::iterator it = fileNames.begin(); it != fileNames.end(); ++it) {
            AbstractFile* currentFile = fileSystem->openFile(*it);
            currentFile->accept(metadataDisplay);
            fileSystem->closeFile(currentFile);
        }
        delete metadataDisplay;
        return SUCCESS;
    }
    // if an invalid argument was passed
    if (command != "") {
        return INVALID_ARGUMENT;
    }
	// print two file names per line if not given -m
    // create an iterator to go through the set
    auto it = fileNames.begin();
    while (it != fileNames.end()) {
        // print the first name in the pair
        cout << *it;
        // move to the next name
        ++it;
        // if there's another name to print calculate the space to separate them
        if (it != fileNames.end()) {
            int spaces = 21 - (*it).length() - (*prev(it)).length();
            // print the required spaces
            cout << setw(spaces) << " ";
            // print the second name
            cout << *it << endl;
            // move to the next name
            ++it;
        }
        else {
            // if only one name remains just print it without extra spaces
            cout << endl;
        }
    }
    return SUCCESS;
}
// prints out what the command is and how to use it
void LSCommand::displayInfo() {
	cout << "ls lists the names of all the files currently in the file system. ls can be invoked with the command : ls" << endl;
}