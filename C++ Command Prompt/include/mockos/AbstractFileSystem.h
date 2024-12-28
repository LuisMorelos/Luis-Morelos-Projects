#pragma once
#include "AbstractFile.h"
#include <set>

// abstract file system class that other file systems, such as the simple file system, will inherit from
class AbstractFileSystem {
public:
    // add file method that adds a file to the file system
    virtual int addFile(string fileName, AbstractFile* file) = 0;
    // delete file method that removes a file from the file system
    virtual int deleteFile(string fileName) = 0;
    // open file method that opens a file in the file system
    virtual AbstractFile* openFile(string fileName) = 0;
    // close file method that closes a file in the file system
    virtual int closeFile(AbstractFile* file) = 0;
    // return set of all files in the file system
    virtual set<string> getFileNames() = 0;
};