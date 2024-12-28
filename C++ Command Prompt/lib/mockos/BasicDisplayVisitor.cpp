#include "../include/mockos/BasicDisplayVisitor.h"
#include <cmath>

// prints out the contents of a text file
void BasicDisplayVisitor::visit_TextFile(TextFile* file) {
	// goes through each character in the vector of the file contents and prints it out
	for (char letter : file->read()) {
		cout << letter;
	}
}
// prints out the contents of an image file
void BasicDisplayVisitor::visit_ImageFile(ImageFile* file) {
	// grabs the file contents vector of characters and the size of the image
	vector<char> fileContents = file->read();
	int imageSize = sqrt(file->getSize());
	// prints out the file contents as a square by printing characters in a 2D array fashion and stopping when it reaches
	// the image size
	for (int y = 0; y < imageSize; y++) {
		for (int x = 0; x < imageSize; x++) {
			int index = file->getIndex(x, y);
			cout << fileContents[index];
		}
		cout << endl;
	}
}