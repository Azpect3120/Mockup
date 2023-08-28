#pragma once

#include <string>
#include <fstream>

#include "../scopeTree/scopeTree.h"
#include "../scopeTree/treeNode.h"


#ifndef COMPILER_H
#define COMPILER_H
struct Properties;

void compileTree (TreeNode*, std::string);
void compileNode (TreeNode*, std::ofstream&, int);
void writeRawHtml (TreeNode*, std::ofstream&, int);

Properties getProperties (TreeNode*);

int countIndentLevel (std::string&);

#endif