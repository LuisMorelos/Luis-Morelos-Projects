#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "AbstractFileFactory.h"
#include "PasswordProxy.h"

// touch command class that creates a file and adds it to the file system
class TouchCommand : public AbstractCommand {
private:
	// the file factory to create a file and the file system that file should be added to
	AbstractFileSystem* fileSystem;
	AbstractFileFactory* fileFactory;
public:
	// default constructor
	TouchCommand(AbstractFileSystem* fs, AbstractFileFactory* ff) : fileSystem(fs), fileFactory(ff) {}
	// overrides abstract command methods
	int execute(string command) override;
	void displayInfo() override;
};