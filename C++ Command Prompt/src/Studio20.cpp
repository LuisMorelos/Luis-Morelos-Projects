#include "../include/mockos/PasswordProxy.h"
#include "../include/mockos/TextFile.h"

int main(int argc, char* argv[]) {
	AbstractFile* textFile = new TextFile("file.txt");
	string password = "hello";
	PasswordProxy proxy(textFile, password);
	proxy.getName();
	proxy.read();
	return 0;
}