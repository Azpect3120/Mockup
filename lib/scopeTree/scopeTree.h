#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "./treeNode.h"

using std::string, std::vector;

class ScopeTree
{
    public:
        TreeNode* root;
        ScopeTree ();
        void printTree (TreeNode*);
};