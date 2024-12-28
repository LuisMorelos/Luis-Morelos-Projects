#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "MetadataDisplayVisitor.h"

class LSCommand : public AbstractCommand {
private:
	// file system that will be used for the command
	AbstractFileSystem* fileSystem;
public:
	// default constructor
	LSCommand(AbstractFileSystem* fs) : fileSystem(fs) {}
	// overrides abstract command methods
	int execute(string command) override;
	void displayInfo() override;
};