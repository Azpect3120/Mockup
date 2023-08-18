#include <iostream>
#include <string>
#include <vector>

#include "treeNode.h"

using std::string, std::vector;

// Constructor
TreeNode::TreeNode (string data)
{
    // Define traversal values
    this->parent = NULL;
    this->children = vector<TreeNode>();
    
    // Define node values    
    int count = 0;
    while (true) {
        if (data.at(0) == ' ') {
            data.erase(0, 1);
            count++;
        } else {
            break;
        }
    }
    this->data = data;
    this->indentCount = count / 4;
}


// Getters
// ------------------------------------------
string TreeNode::getData ()
{
    return data;
}

int TreeNode::getIndentCount ()
{
    return indentCount;
}

TreeNode* TreeNode::getParent ()
{
    return parent;
}

vector<TreeNode> TreeNode::getChildren ()
{
    return children;
}



// Setters
// ------------------------------------------
void TreeNode::setData (string data)
{
    this->data = data;
}

void TreeNode::setIndentCount (int indentCount)
{
    this->indentCount = indentCount;
}

void TreeNode::setParent (TreeNode* parent)
{
    this->parent = parent;
}

void TreeNode::setChildren (vector<TreeNode> children)
{
    this->children = children;
}



// Utils
// ------------------------------------------
void TreeNode::addChild (TreeNode child)
{
    this->getChildren().push_back(child);
}

void TreeNode::printTree (TreeNode node)
{
    int indentCount = node.getIndentCount();

    for (int i = 0; i < indentCount; i++) {
        std::cout << "   ";
    }

    std::cout << node.getData() << std::endl;

    for (const TreeNode child : node.getChildren()) {
        printTree(child);
    }
}