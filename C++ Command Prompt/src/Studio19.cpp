#include "../include//mockos/ImageFile.h"
#include "../include/mockos/BasicDisplayVisitor.h"

int main(int argc, char* argv[]) {
	std::string fileName = "FileName.img";
	ImageFile t(fileName);
	std::vector<char> v = { 'X', ' ', 'X', ' ', 'X', ' ', 'X',' ', 'X', '3' };
	t.write(v);
	AbstractFileVisitor* bdv = new BasicDisplayVisitor;
	t.accept(bdv);
	return 0;
}