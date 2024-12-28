#pragma once
#include "AbstractFileVisitor.h"

// metadata display visitor class that visits a file and displays its metadata (file type, name, size, etc.
class MetadataDisplayVisitor : public AbstractFileVisitor {
public:
	// override the abstract file visitor methods
	void visit_TextFile(TextFile* file) override;
	void visit_ImageFile(ImageFile* file) override;
};