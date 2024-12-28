#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

class RemoveCommand : public AbstractCommand {
private:
	// file system we can remove files from
	AbstractFileSystem* fileSystem;
public:
	// default constructor
	RemoveCommand(AbstractFileSystem* fs) : fileSystem(fs) {}
	// overrides abstract command methods
	int execute(string command) override;
	void displayInfo() override;
};