#pragma once

#include <iostream>
#include <fstream> 
#include <string>
#include <vector>

using std::string, std::vector;

class TreeNode {
    public:
        string data;
        TreeNode* parent;
        vector<TreeNode*> children;

        TreeNode (const string&);
        void addChild (TreeNode*);
        void insertChild (TreeNode*, int);
};