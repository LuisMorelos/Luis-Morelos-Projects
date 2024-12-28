#include "../include/mockos/SimpleFileSystem.h"
#include "../include/mockos/SimpleFileFactory.h"

int main(int argc, char* argv[]) {
	AbstractFileSystem* fileSystem = new SimpleFileSystem;
	AbstractFileFactory* fileFactory = new SimpleFileFactory;
	return 0;
}