#pragma once

#include <iostream>
#include <string>
#include <vector>

class TreeNode
{
    private:
        std::string data;
        int indentCount;
        TreeNode* parent;
        std::vector<TreeNode*> children;

    public:
        TreeNode (std::string);
        std::string getData ();
        int getIndentCount ();
        TreeNode* getParent ();
        std::vector<TreeNode*> getChildren ();
        void setData (std::string);
        void setIndentCount (int);
        void setParent (TreeNode*);
        void setChildren (std::vector<TreeNode*>);
        void addChild (TreeNode*);
        void printTree (TreeNode*, std::string);
};