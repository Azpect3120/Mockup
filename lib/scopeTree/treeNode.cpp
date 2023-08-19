#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "./treeNode.h"

using std::string, std::vector;

TreeNode::TreeNode (const string& data)
{
    this->data = data;
    parent = nullptr;
}

void TreeNode::addChild (TreeNode* child)
{
    child->parent = this;
    children.push_back(child);
}