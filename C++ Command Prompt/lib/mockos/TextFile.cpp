#include "../include/mockos/TextFile.h"
#include "../include/mockos/AbstractFileVisitor.h"

enum Errors {
	SUCCESS = 0
};

// returns the size of the file contents vector
unsigned int TextFile::getSize() {
	return fileContents.size();
}
// returns the name of the file as a string from the file name member variable
string TextFile::getName() {
	return fileName;
}
// replaces the file contents vector with a new vector provided to the method
int TextFile::write(vector<char> word) {
	fileContents = word;
	return SUCCESS;
}
// adds a provided vector to the file contents vector without replacing the original vector
int TextFile::append(vector<char> word) {
	// copy is used here to append the new vector to the old vector
	copy(word.begin(), word.end(), back_inserter(fileContents));
	return SUCCESS;
}
// returns the file contents vector so that the display visitor can use it
vector<char> TextFile::read() {
	/*for (char letter : fileContents) {
		cout << letter;
	}*/
	return fileContents;
}
// accepts visitors by calling the visit file method on a given pointer to a visitor
void TextFile::accept(AbstractFileVisitor* visitor) {
	visitor->visit_TextFile(this);
}
// creates a copy of the file
AbstractFile* TextFile::clone(string fileName) {
	TextFile* copy = new TextFile(fileName);
	copy->fileContents = vector<char>(this->fileContents.begin(), this->fileContents.end());
	return copy;
}