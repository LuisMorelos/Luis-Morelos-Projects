#include "../include/mockos/TouchCommand.h"
#include "../include/mockos/CommandPrompt.h"
#include "../include/mockos/TextFile.h"

int main(int argc, char* argv[]) {
	std::string fileName = "FileName.txt";
	TextFile t(fileName);
	std::vector<char> v = { 'h', 'i' };
	t.write(v);
	return 0;
}