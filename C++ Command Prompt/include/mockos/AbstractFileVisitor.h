#pragma once
#include "TextFile.h"
#include "ImageFile.h"

// abstract file visitor class that other file visitors, such as the display visitor, inherit from
class AbstractFileVisitor {
public:
	// visits a text file
	virtual void visit_TextFile(TextFile* file) = 0;
	// visits an image file
	virtual void visit_ImageFile(ImageFile* file) = 0;
};