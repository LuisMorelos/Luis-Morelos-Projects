#include "../include/mockos/ImageFile.h"
#include "../include/mockos/AbstractFileVisitor.h"

enum Errors {
	SUCCESS = 0,
	INCORRECT_VECTOR = 1,
	CANNOT_APPEND = 2
};

// returns the file contents member variable
unsigned int ImageFile::getSize() {
	return fileContents.size();
}
// returns the file name member variable
string ImageFile::getName() {
	return fileName;
}
// replaces the contents of the file with a vector that represents an image
int ImageFile::write(vector<char> image) {
	// finds the last item in the vector, subtracts the character '0' to convert it to a number, and assigns
	// that to the image size member variable
	imageSize = image[image.size() - 1] - '0';
	// if the vector is not of the correct size or does not contain only the characters 'X' and space, then clear the file contents
	// and return a unique non-zero value
	if ((imageSize * imageSize) != image.size() - 1 || any_of(image.begin(), image.end() - 1, [](char c) { return c != ' ' && c != 'X'; })) {
		fileContents.clear();
		imageSize = 0;
		return INCORRECT_VECTOR;
	}
	// replace the file contents and return success
	fileContents.assign(image.begin(), image.end() - 1);
	return SUCCESS;
}
// you cannot append
int ImageFile::append(vector<char> word) {
	return CANNOT_APPEND;
}
// returns the file contents member variable so it can be used by the display visitor
vector<char> ImageFile::read() {
	/*for (int y = 0; y < imageSize; y++) {
		for (int x = 0; x < imageSize; x++) {
			int index = getIndex(x, y);
			cout << fileContents[index];
		}
		cout << endl;
	}*/
	return fileContents;
}
// helper method to calculate index using the row and column
unsigned int ImageFile::getIndex(unsigned int x, unsigned int y) {
	return y * imageSize + x;
}
// accepts visitors and calls the visit image file method
void ImageFile::accept(AbstractFileVisitor* visitor) {
	visitor->visit_ImageFile(this);
}
// creates a copy of the file
AbstractFile* ImageFile::clone(string fileName) {
	ImageFile* copy = new ImageFile(fileName);
	copy->fileContents = vector<char>(this->fileContents.begin(), this->fileContents.end());
	copy->imageSize = this->imageSize;
	return copy;
}