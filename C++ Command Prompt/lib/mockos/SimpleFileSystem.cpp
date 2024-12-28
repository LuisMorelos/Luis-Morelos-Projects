#include "../include/mockos/SimpleFileSystem.h"
#include "../include/mockos/TextFile.h"
#include "../include/mockos/ImageFile.h"

enum Errors {
    SUCCESS = 0,
    FILE_ALREADY_IN_SYSTEM = 3,
    FILE_DOES_NOT_EXIST = 4,
    FILE_NOT_OPEN = 6,
    FILE_NOT_FOUND = 7,
    FILE_ALREADY_OPEN = 8
};

// adds a file to the system
int SimpleFileSystem::addFile(string fileName, AbstractFile* file) {
    // if the file exists in the system already, return a unique non-zero value
    if (files.find(fileName) != files.end()) {
        return FILE_ALREADY_IN_SYSTEM;
    }
    // if file does not exist then return a unique non-zero value
    if (file == nullptr) {
        return FILE_DOES_NOT_EXIST;
    }
    // if the file exists and is not already in the system, add it to the system and return success
    files[fileName] = file;
    return SUCCESS;
}
// deletes a file from the system
int SimpleFileSystem::deleteFile(string fileName) {
    auto it = files.find(fileName);
    // if we do not find the file, return a unique non-zero value
    if (it == files.end()) {
        return FILE_NOT_FOUND;
    }
    // if file is open, return a unique non-zero value
    if (openFiles.find(it->second) != openFiles.end()) {
        return FILE_ALREADY_OPEN;
    }
    // delete the file from the system and return success
    delete it->second;
    files.erase(it);
    return SUCCESS;
}
// opens a file from the system
AbstractFile* SimpleFileSystem::openFile(string fileName) {
    auto it = files.find(fileName);
    // if file is not found, return a null pointer
    if (it == files.end()) {
        return nullptr;
    }
    // if file is already open, return a null pointer
    if (openFiles.find(it->second) != openFiles.end()) {
        return nullptr;
    }
    // open the file and add it to the open files set
    openFiles.insert(it->second);
    return it->second;
}
// closes a file that is open
int SimpleFileSystem::closeFile(AbstractFile* file) {
    // if the file is not open, return a unique non-zero file
    if (openFiles.find(file) == openFiles.end()) {
        return FILE_NOT_OPEN;
    }
    // close the file and remove it from the open files set
    openFiles.erase(file);
    return SUCCESS;
}
// returns a set of all files in the system
set<string> SimpleFileSystem::getFileNames() {
    // make a set to contain the file names
    set<string> fileNames;
    // go through the files map and put the names into the set
    for (auto& entry : files) {
        fileNames.insert(entry.first);
    }
    return fileNames;
}