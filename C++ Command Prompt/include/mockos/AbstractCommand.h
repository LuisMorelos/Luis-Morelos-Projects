#pragma once
#include <iostream>
#include <string>

using namespace std;

// abstract command class that other command classes, such as the copy command or cat command, will inherit from
class AbstractCommand {
public:
	// destructor as well as pure virtual execute and display info methods that run a command and display information 
	// about what the command does/how to use it
	virtual ~AbstractCommand() = default;
	virtual int execute(string command) = 0;
	virtual void displayInfo() = 0;
};