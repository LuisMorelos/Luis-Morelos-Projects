#pragma once
#include "AbstractFile.h"

// abstract file factory class that other file factories, such as the simple file factory, inherit from
class AbstractFileFactory {
public:
	// creates a file
	virtual AbstractFile* createFile(string fileName) = 0;
};