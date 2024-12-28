#include "../include/mockos/MetadataDisplayVisitor.h"
#include <iomanip>

// prints the name, type, and size of a text file
void MetadataDisplayVisitor::visit_TextFile(TextFile* file) {
	cout << setw(20) << file->getName() << setw(10) << "text" << setw(10) << file->getSize() << endl;
}
// prints the name, size, and type of an image file
void MetadataDisplayVisitor::visit_ImageFile(ImageFile* file) {
	cout << setw(20) << file->getName() << setw(10) << "image" << setw(10) << file->getSize() << endl;
}