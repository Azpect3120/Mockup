#include <string>
#include <vector>
#include <iostream>

#include "ASTNode.h"

using std::string, std::vector;

// Constructor
ASTNode::ASTNode (ASTNode& parent, string data, int indentCount)
{
    this->data = data;
    this->parent = &parent;
    this->indentCount = indentCount;
    this->children = vector<ASTNode>();
}

// Getters
string* ASTNode::getData ()
{
    return &data;
}

int* ASTNode::getIndentCount ()
{
    return &indentCount;
}

vector<ASTNode>* ASTNode::getChildren ()
{
    return &children;
}

ASTNode* ASTNode::getParent ()
{
    return parent;
}

// Setters
void ASTNode::setData (string data)
{
    this->data = data;
}

void ASTNode::setIndentCount (int indentCount)
{
    this->indentCount = indentCount;
}

void ASTNode::setChildren (vector<ASTNode> children)
{
    this->children = children;
}

void ASTNode::addChild (ASTNode child)
{
    this->children.push_back(child);
}

void ASTNode::setParent (ASTNode parent)
{
    this->parent = &parent;
}

// Utils
void ASTNode::printNode ()
{
    std::cout << this->data << " (" << this->indentCount << ")" << std::endl;
}

void ASTNode::printChildren ()
{
    vector<ASTNode>& children = *this->getChildren();
    for (const ASTNode& node : children) {
        std::cout << node.data << std::endl;
    }
}

void ASTNode::printTree (ASTNode node)
{
    int* indentCount = node.getIndentCount();
    
    for (int i = 0; i < *indentCount; i++) {
        std::cout << "  ";
    }

    std::cout << node.data << std::endl;
    vector<ASTNode>& children = *node.getChildren();
    for (const ASTNode& node : children) {
        printTree(node);
    }

}