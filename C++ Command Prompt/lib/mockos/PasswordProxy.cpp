#include "../include/mockos/PasswordProxy.h"

enum Errors {
	INCORRECT_PASSWORD = 8
};

// prompts the user to enter a password
string PasswordProxy::passwordPrompt() {
	cout << "Please enter password: " << endl;
	string userInput;
	getline(cin, userInput);
	// stores that password in a string and returns it
	return userInput;
}
// check if the input matches the password member variable
bool PasswordProxy::matchesPassword(string input) {
	return password == input;
}
// reads the contents of the file, but only if the password given matches the password member variable.
vector<char> PasswordProxy::read() {
	vector<char> fileContents;
	if (matchesPassword(passwordPrompt())) {
		fileContents = protectedFile->read();
	}
	return fileContents;
}
// writes to the file but only if the correct password is given. Returns a unique non-zero value if it isn't correct
int PasswordProxy::write(vector<char> word) {
	if (matchesPassword(passwordPrompt())) {
		return protectedFile->write(word);
	}
	return INCORRECT_PASSWORD;
}
// appends to the file but only if the correct password is given
int PasswordProxy::append(vector<char> word) {
	if (matchesPassword(passwordPrompt())) {
		return protectedFile->append(word);
	}
	return INCORRECT_PASSWORD;
}
// returns the size of the file
unsigned int PasswordProxy::getSize() {
	return protectedFile->getSize();
}
// returns the name of the file
string PasswordProxy::getName() {
	return protectedFile->getName();
}
// accepts a visitor but only if the correct password is given
void PasswordProxy::accept(AbstractFileVisitor* visitor) {
	if (matchesPassword(passwordPrompt())) {
		protectedFile->accept(visitor);
	}
}
// creates a copy of the proxy
AbstractFile* PasswordProxy::clone(string fileName) {
	// clone the file this proxy is attached to first, and then clone the proxy using that file copy
	AbstractFile* fileCopy = this->protectedFile->clone(fileName);
	return new PasswordProxy(fileCopy, this->password);
}