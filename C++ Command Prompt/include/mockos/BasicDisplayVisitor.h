#pragma once
#include "AbstractFileVisitor.h"

// display visitor class that visits a file and displays its contents in a way specific to the file type
class BasicDisplayVisitor : public AbstractFileVisitor {
public:
	// visits and displays a text file's contents
	void visit_TextFile(TextFile* file) override;
	// visits and displays an image file's contents
	void visit_ImageFile(ImageFile* file) override;
};