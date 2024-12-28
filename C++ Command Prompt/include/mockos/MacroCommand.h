#pragma once
#include "AbstractCommand.h"
#include "AbstractParsingStrategy.h"
#include "AbstractFileSystem.h"

class MacroCommand : public AbstractCommand {
private:
	vector<AbstractCommand*> primitiveCommands;
	AbstractParsingStrategy* parsingStrategy;
	AbstractFileSystem* fileSystem;
public:
	// default constructor
	MacroCommand(AbstractFileSystem* fs) : fileSystem(fs) {}
	// overrides abstract command methods
	int execute(string command) override;
	void displayInfo() override;
	// added methods
	void addCommand(AbstractCommand* ac);
	void setParseStrategy(AbstractParsingStrategy* ps);
};