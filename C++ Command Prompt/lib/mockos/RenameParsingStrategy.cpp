#include "../include/mockos/RenameParsingStrategy.h"
#include <sstream>

// parses the input string
vector<string> RenameParsingStrategy::parse(string input) {
	vector<string> commandArgs;
	// push the original and newfile names into the vector to be used by the copy command
	commandArgs.push_back(input);
	// split the arguments into two words: the original and new file names
	istringstream stream(input);
	string fileName, fileCopyName;
	stream >> fileName >> fileCopyName;
	// push the original file name to be used by the remove command
	commandArgs.push_back(fileName);
	// return the vector of strings to be used by the macro command
	return commandArgs;
}