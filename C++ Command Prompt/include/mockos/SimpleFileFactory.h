#pragma once
#include "AbstractFileFactory.h"

// simple file factory class that creates files
class SimpleFileFactory : public AbstractFileFactory {
public:
	// overrides the abstract file factory method
	AbstractFile* createFile(string fileName) override;
};