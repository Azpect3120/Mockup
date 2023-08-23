#pragma once

#include <string>
#include <vector>

#include "treeNode.h"
#include "scopeTree.h"

namespace TreeBuilder {
    TreeNode* buildTree (const std::string&, TreeNode*); 
    int countLeadingSpaces (const string&);
    int countIndentLevel (const string&);   
};