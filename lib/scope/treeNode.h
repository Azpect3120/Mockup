#pragma once

#include <string>
#include <vector>

using std::string, std::vector;


class TreeNode
{
    private:
        string data;
        int indentCount;
        TreeNode* parent;
        vector<TreeNode> children;

    public:
        // Constructor
        TreeNode (string);

        // Getters
        string getData ();
        int getIndentCount ();
        TreeNode* getParent (); 
        vector<TreeNode> getChildren();

        // Setters
        void setData (string); 
        void setIndentCount (int);
        void setParent (TreeNode*);
        void setChildren (vector<TreeNode>);

        // Utils
        void addChild (TreeNode);
        void printTree (TreeNode);

};