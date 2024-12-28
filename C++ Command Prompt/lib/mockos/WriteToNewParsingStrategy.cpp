#include "../include/mockos/WriteToNewParsingStrategy.h"
#include <sstream>

vector<string> WriteToNewParsingStrategy::parse(string input) {
	vector<string> commandArgs;
    // strings to store the touch and cat command arguments
    string touchArgs;
    string catArgs;
    // split the input string by spaces
    istringstream stream(input);
    string fileName;
    stream >> fileName;
    // start with the file name and check for flags
    touchArgs = fileName;
    catArgs = fileName;
    // grab the flags if they exist
    string firstFlag;
    string secondFlag;
    stream >> firstFlag >> secondFlag;
    // check if there is a flag and if it is -p or -a
    if (!firstFlag.empty()) {
        // if -a add to the cat arguments
        if (firstFlag == "-a") {
            catArgs += " " + firstFlag;
        }
        // if not, just add it to the touch arguments
        else {
            touchArgs += " " + firstFlag;
        }
    }
    // check if there is a second flag and add it to the cat arguments
    if (!secondFlag.empty()) {
        catArgs += " " + secondFlag;
    }
    // add the arguments to the vector
    commandArgs.push_back(touchArgs);
    commandArgs.push_back(catArgs);
    // return the arguments
    return commandArgs;
}