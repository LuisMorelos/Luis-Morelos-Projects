#pragma once
#include "AbstractFileSystem.h"
#include <map>
#include <set>

// simple file system class that manages files
class SimpleFileSystem : public AbstractFileSystem {
private:
    // map of files and their names, as well as a set of files that are currently open
    map<string, AbstractFile*> files;
    set<AbstractFile*> openFiles;
public:
    // overrides abstract file system methods
    int addFile(string fileName, AbstractFile* file) override;
    int deleteFile(string fileName) override;
    AbstractFile* openFile(string fileName) override;
    int closeFile(AbstractFile* file) override;
    set<string> getFileNames() override;
};