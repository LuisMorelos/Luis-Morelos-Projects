#include "../include/mockos/TouchCommand.h"

enum Errors {
    SUCCESS = 0,
    FILE_NOT_CREATED = -1,
    INVALID_ARGUMENTS = -2
};

// runs the touch command
int TouchCommand::execute(string command) {
    // variables we will need later
    bool hasPassword = false;
    string userInput;
    string beforeSpace;
    AbstractFile* newFile = nullptr;
    // check if file should be password protected
    // find the position of the space in the arguments passed, if any
    size_t spacePos = command.find(' ');

    // check if a space exists in the string
    if (spacePos != string::npos) {
        // get the substring before and after the space
        beforeSpace = command.substr(0, spacePos);
        string afterSpace = command.substr(spacePos + 1);
        // check if the substring after the space is "-p"
        if (afterSpace == "-p") {
            // prompt user for password
            cout << "Please enter a password for the file: " << endl;
            getline(cin, userInput);
            // say that the file is password protected so that we can create the proxy later
            hasPassword = true;
            // create a file with the substring before the space
            newFile = fileFactory->createFile(beforeSpace);
        }
        else {
            // there was another argument but it was not "-p"
            return INVALID_ARGUMENTS;
        }
    }
    // if there is no space in the arguments
    else {
        newFile = fileFactory->createFile(command);
    }

    // if the new file cannot be created return a unique non-zero value
    if (newFile == nullptr) {
        return FILE_NOT_CREATED;
    }

    // check if a proxy is needed
    int result;
    if (hasPassword == true) {
        // if it is needed, create the object and set a pointer to it that we can use to add to the system
        AbstractFile* protectedFile = new PasswordProxy(newFile, userInput);
        result = fileSystem->addFile(beforeSpace, protectedFile);
    }
    // if no proxy is needed just create the file
    else {
        result = fileSystem->addFile(command, newFile);
    }

    // if it cannot be added, say so and return a unique non-zero value
    if (result != SUCCESS) {
        cout << "File '" << command << "' could not be added to the file system." << endl;
        delete newFile;
        return result;
    }

    // if everything goes well, say that the file was created and added and return success
    cout << "File '" << command << "' successfully created and added to the file system." << endl;
    return SUCCESS;
}
// prints out what the command does and how to use it
void TouchCommand::displayInfo() {
	cout << "touch creates a file and adds it to the file system. touch can be invoked with the command : touch <filename>" << endl;
    cout << "touch can also create a password protected file. this can be invoked with the command : touch <filename> -p" << endl;
}