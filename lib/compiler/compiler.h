#pragma once

#include <string>
#include <fstream>

#include "../scopeTree/scopeTree.h"
#include "../scopeTree/treeNode.h"


#ifndef COMPILER_H
#define COMPILER_H

void compileTree (TreeNode*, std::string);
void compileNode (TreeNode*, std::ofstream&);
void trim (std::string&);

int countIndentLevel (std::string&);

#endif