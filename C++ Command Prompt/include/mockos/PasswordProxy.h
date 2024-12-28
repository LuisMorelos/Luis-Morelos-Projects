#pragma once
#include "AbstractFile.h"

// password proxy class that assigns a password to a file and makes sure the file can only be accessed using that password
class PasswordProxy : public AbstractFile {
private:
	// a pointer to the file that should be protected by the password and the password
	AbstractFile* protectedFile;
	string password;
public:
	// default constructor and destructor that deletes the pointer to the protected file in order to avoid life time memory issues
	PasswordProxy(AbstractFile* pf, string p) : protectedFile(pf), password(p) {}
	~PasswordProxy() {
		delete protectedFile;
	}
	// overrides the abstract file methods
	vector<char> read() override;
	int write(vector<char> word) override;
	int append(vector<char> word) override;
	unsigned int getSize() override;
	string getName() override;
	void accept(AbstractFileVisitor* visitor) override;
	AbstractFile* clone(string fileName) override;
protected:
	// prompts the user for a password and uses the matches password helper method to see if it matches the real password
	string passwordPrompt();
	bool matchesPassword(string input);
};