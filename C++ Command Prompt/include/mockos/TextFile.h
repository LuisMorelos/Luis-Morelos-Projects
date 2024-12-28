#pragma once
#include "AbstractFile.h"

// text file class that manages a file of type "text"
class TextFile : public AbstractFile {
private:
	// file contents as a vector of characters and the file name as a string
	vector<char> fileContents;
	string fileName;
public:
	// default constructor
	TextFile(string n) : fileName(n) {}
	// overrides abstract file methods
	unsigned int getSize() override;
	string getName() override;
	int write(vector<char> word) override;
	int append(vector<char> word) override;
	vector<char> read() override;
	void accept(AbstractFileVisitor* visitor) override;
	AbstractFile* clone(string fileName) override;
};