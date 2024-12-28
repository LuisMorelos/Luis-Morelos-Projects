#include "../include/mockos/MacroCommand.h"
#include "../include/mockos/RenameParsingStrategy.h"
#include "../include/mockos/CopyCommand.h"
#include "../include/mockos/RemoveCommand.h"
#include "../include/mockos/SimpleFileSystem.h"
#include "../include/mockos/CommandPrompt.h"
#include "../include/mockos/TouchCommand.h"
#include "../include/mockos/SimpleFileFactory.h"
#include "../include/mockos/LSCommand.h"
#include "../include/mockos/CatCommand.h"
#include "../include/mockos/DisplayCommand.h"
#include "../include/mockos/WriteToNewParsingStrategy.h"
#include "../include/mockos/PasswordProxy.h"

enum Errors {
	SUCCESS = 0
};

int main(int argc, char* argv) {
	AbstractParsingStrategy* parsingStrategy = new RenameParsingStrategy();
	AbstractFileSystem* fileSystem = new SimpleFileSystem();
	AbstractFileFactory* fileFactory = new SimpleFileFactory();
	MacroCommand* renameMacroCommand = new MacroCommand(fileSystem);
	AbstractCommand* copyCommand = new CopyCommand(fileSystem);
	AbstractCommand* removeCommand = new RemoveCommand(fileSystem);
	CommandPrompt* commandPrompt = new CommandPrompt();
	AbstractCommand* touchCommand = new TouchCommand(fileSystem, fileFactory);
	AbstractCommand* lsCommand = new LSCommand(fileSystem);
	AbstractCommand* catCommand = new CatCommand(fileSystem);
	AbstractCommand* displayCommand = new DisplayCommand(fileSystem);
	MacroCommand* writeToNewMC = new MacroCommand(fileSystem);

	writeToNewMC->setParseStrategy(parsingStrategy);
	writeToNewMC->addCommand(touchCommand);
	writeToNewMC->addCommand(catCommand);
	renameMacroCommand->setParseStrategy(parsingStrategy);
	renameMacroCommand->addCommand(copyCommand);
	renameMacroCommand->addCommand(removeCommand);
	commandPrompt->setFileFactory(fileFactory);
	commandPrompt->setFileSystem(fileSystem);
	commandPrompt->addCommand("rn", renameMacroCommand);
	commandPrompt->addCommand("touchcat", writeToNewMC);
	commandPrompt->addCommand("cp", copyCommand);
	commandPrompt->addCommand("rm", removeCommand);
	commandPrompt->addCommand("touch", touchCommand);
	commandPrompt->addCommand("ls", lsCommand);
	commandPrompt->addCommand("ds", displayCommand);
	commandPrompt->addCommand("cat", catCommand);
	return commandPrompt->run();
}