#pragma once
#include "AbstractFile.h"

// image file class that is used to manage files that have a type of "image"
class ImageFile : public AbstractFile {
private:
	// the file name, contents, and size
	string fileName;
	vector<char> fileContents;
	char imageSize;
public:
	// default constuctor
	ImageFile(string n) : fileName(n) {
		imageSize = 0;
	}
	// overrides the methods from the abstract file class
	unsigned int getSize() override;
	string getName() override;
	int write(vector<char> image) override;
	int append(vector<char> word) override;
	vector<char> read() override;
	// get index helper method that is used to obtain the index of a symbol based on its row/column and print it out correctly
	unsigned int getIndex(unsigned int x, unsigned int y);
	void accept(AbstractFileVisitor* visitor) override;
	AbstractFile* clone(string fileName) override;
};