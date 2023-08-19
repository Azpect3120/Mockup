#pragma once

#include <string>

#include "../scopeTree/scopeTree.h"
#include "../scopeTree/treeNode.h"


#ifndef COMPILER_H
#define COMPILER_H

void compileTree (TreeNode*);
void compileNode (TreeNode*);
void trim (std::string&);

#endif