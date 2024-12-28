#pragma once
#include "AbstractCommand.h"
#include "AbstractFileSystem.h"

class CatCommand : public AbstractCommand {
private:
	AbstractFileSystem* fileSystem;
public:
	// default constructor
	CatCommand(AbstractFileSystem* fs) : fileSystem(fs) {}
	// overrides abstract command methods
	int execute(string command) override;
	void displayInfo() override;
};