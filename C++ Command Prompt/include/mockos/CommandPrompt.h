#pragma once
#include <map>
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"

// command prompt class that will manage a file system and file factory based off of given commands
class CommandPrompt {
private:
	// map to hold possible commands using their name and object
	map<string, AbstractCommand*> commandObjects;
	// file system to hold and manage files
	AbstractFileSystem* fileSystem;
	// file factory to create files
	AbstractFileFactory* fileFactory;
protected:
	// lists the possible commands in the map of possible commands
	void listCommands();
	// prompts the user to input a command
	string prompt();
public:
	// default constructor
	CommandPrompt() {
		fileSystem = nullptr;
		fileFactory = nullptr;
	}
	// sets the file system member variable to be the file system given
	void setFileSystem(AbstractFileSystem* inputFileSystem);
	// sets the file factory member variable to be the file factory given
	void setFileFactory(AbstractFileFactory* inputFileFactory);
	// adds a command to the map of possible commands
	int addCommand(string commandString, AbstractCommand* inputCommand);
	// runs the class methods to prompt the user
	int run();
};