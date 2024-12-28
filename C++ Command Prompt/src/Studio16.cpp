#include "../include/mockos/TextFile.h"

int main(int argc, char* argv[]) {
	TextFile file("Test File");
	AbstractFile& baseClassObj = file;
	vector<char> word = { 'H', 'e', 'l', 'l', 'o' };
	vector<char> otherWord = { 'N', 'e' , 'w' };
	baseClassObj.write(word);
	baseClassObj.read();
	baseClassObj.write(otherWord);
	baseClassObj.read();
	baseClassObj.append(word);
	baseClassObj.read();
	cout << baseClassObj.getName() << baseClassObj.getSize() << endl;
	return 0;
}