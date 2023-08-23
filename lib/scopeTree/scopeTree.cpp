#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "./treeNode.h"
#include "./scopeTree.h"

using std::string;
using std::vector;

// Object constructor
ScopeTree::ScopeTree ()
{
    this->root = new TreeNode("Root");
}

// Print the tree to the console
void ScopeTree::printTree (TreeNode* node)
{
    if (!node) return;

    std::cout << node->data << " (" << node->children.size() << ")" << std::endl;

    for (TreeNode* child : node->children) {
        printTree(child);
    }
}