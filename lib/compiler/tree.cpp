#include <iostream>
#include <string>
#include <vector>

#include "tree.h"

using std::string, std::vector;

// Constructor
Node::Node (string data)
{
    this->data = data;
    this->children = vector<Node>();
}

// Getters
const vector<Node>* Node::getChildren ()
{
    return &children;
}

const string* Node::getData () 
{
    return &data;
}

// Setters
void Node::setData (string data)
{
    this->data = data;
}

void Node::setChildren (vector<Node> children)
{
    this->children = children;
}