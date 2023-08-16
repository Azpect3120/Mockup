#pragma once

#include <string>
#include <vector>

#include "ASTNode.h"

using std::string, std::vector;


int countIndents (string&);
void removeIndents (string&);
ASTNode createNode (string&);