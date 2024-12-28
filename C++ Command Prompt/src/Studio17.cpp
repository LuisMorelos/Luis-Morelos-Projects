#include "../include/mockos/SimpleFileSystem.h"
#include "../include/mockos/TextFile.h"
#include "../include/mockos/ImageFile.h"

int main(int argc, char* argv[]) {
    SimpleFileSystem fileSystem;
    fileSystem.createFile("textFileSystem.txt");
    fileSystem.createFile("imageFileSystem.img");
    TextFile textFile("textFile.txt");
    ImageFile imageFile("imageFile.img");

    TextFile* textFilePtr = &textFile;
    ImageFile* imageFilePtr = &imageFile;
    fileSystem.addFile("textFile.txt", textFilePtr);
    fileSystem.addFile("imageFile.img", imageFilePtr);

    AbstractFile* textFilePtr1 = fileSystem.openFile("textFileSystem.txt");
    AbstractFile* imageFilePtr1 = fileSystem.openFile("imageFileSystem.img");
    AbstractFile* textFilePtr2 = fileSystem.openFile("textFile.txt");
    AbstractFile* imageFilePtr2 = fileSystem.openFile("imageFile.img");

    fileSystem.closeFile(textFilePtr1);
    fileSystem.closeFile(textFilePtr1);
    fileSystem.closeFile(textFilePtr2);
    fileSystem.closeFile(imageFilePtr2);

    /*fileSystem.deleteFile("textFileSystem.txt");
    fileSystem.deleteFile("imageFileSystem.img");
    fileSystem.deleteFile("textFile.txt");
    fileSystem.deleteFile("imageFile.img");*/
    return 0;
}