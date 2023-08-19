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
        void buildTreeFromFile (const string&);
        void traverseDFS (TreeNode*, std::ofstream&);
        void writeTreeToFile (const string&);

    private:
        int countLeadingSpaces (const string&);
        int countIndentLevel (const string&);   

};