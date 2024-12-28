#include "../include/mockos/SimpleFileFactory.h"
#include "../include/mockos/TextFile.h"
#include "../include/mockos/ImageFile.h"

// creates a file
AbstractFile* SimpleFileFactory::createFile(string fileName) {
    // finds the ".something" extension at the end of the file name
    string extension = fileName.substr(fileName.find_last_of('.') + 1);
    // set the file to null in case it does not end in "txt" or "img"
    AbstractFile* newFile = nullptr;
    // if it ends in "txt", create a text file. If it ends with "img", create an image file
    if (extension == "txt") {
        newFile = new TextFile(fileName);
    }
    else if (extension == "img") {
        newFile = new ImageFile(fileName);
    }
    // return the file
    return newFile;
}