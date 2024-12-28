#pragma once
#include "AbstractParsingStrategy.h"

class WriteToNewParsingStrategy : public AbstractParsingStrategy {
public:
	vector<string> parse(string input) override;
};