#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"
#include "BasicDisplayVisitor.h"

class DisplayCommand : public AbstractCommand {
private:
	AbstractFileSystem* fileSystem;
public:
	// default constructor
	DisplayCommand(AbstractFileSystem* fs) : fileSystem(fs) {}
	// overrides abstract command methods
	int execute(string command) override;
	void displayInfo() override;
};