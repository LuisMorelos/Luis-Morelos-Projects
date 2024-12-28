#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

// forward declaration of this class so we can use it in the abstract file class but not run into 
// any circular inclusion errors
class AbstractFileVisitor;

// abstract file class that other file classes, such as the text and image files, will inherit from
class AbstractFile {
public:
	// default destructor is declared to avoid life time memory leaks
	virtual ~AbstractFile() = default;
	// read method that reads the contents of the file
	virtual vector<char> read() = 0;
	// write method that writes a vector of characters into the file and will remove the original contents
	virtual int write(vector<char> word) = 0;
	// append method that will write a vector of characters into the file but keep the original contents as well
	virtual int append(vector<char> word) = 0;
	// get size method that will return the size of the file contents. Differs for each file type
	virtual unsigned int getSize() = 0;
	// get name method that returns the name of the file
	virtual string getName() = 0;
	// accept method so that visitors can visit the files and perform certain actions
	virtual void accept(AbstractFileVisitor* visitor) = 0;
	// makes a copy of the file
	virtual AbstractFile* clone(string fileName) = 0;
};