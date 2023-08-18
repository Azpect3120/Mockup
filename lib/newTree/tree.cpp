#include <iostream>
#include <string>
#include <vector>

#include "tree.h"

TreeNode::TreeNode (std::string data)
{
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

std::string TreeNode::getData ()
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

std::vector<TreeNode*> TreeNode::getChildren ()
{
    return children;
}

void TreeNode::setData (std::string data)
{
    this->data = data;
}

void TreeNode::setIndentCount (int indentCount)
{
    this->indentCount = indentCount;
}

void TreeNode::setParent (TreeNode* node)
{
   parent = node;
}

void TreeNode::setChildren (std::vector<TreeNode*> nodes)
{
    children = nodes;
}

void TreeNode::addChild (TreeNode* node)
{
    children.push_back(node);
}

void TreeNode::printTree (TreeNode* node, std::string indent)
{
    std::cout << indent << node->getData() << std::endl;

    indent.append("    ");
    for (TreeNode* subNode : node->getChildren()) {
        printTree(subNode, indent);
    }
}