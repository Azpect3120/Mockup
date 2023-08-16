#include <string>
#include <vector>
#include <iostream>

#include "ASTNode.h"

using std::string, std::vector;

// Constructor
ASTNode::ASTNode (string data, int indentCount)
{
    this->data = data;
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

// Utils
void ASTNode::printNode ()
{
    std::cout << this->data << std::endl;
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