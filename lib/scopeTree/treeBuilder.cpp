#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "treeNode.h"
#include "treeBuilder.h"

using std::string;
using std::vector;

// Build the tree and return the root
TreeNode* TreeBuilder::buildTree (const string& path, TreeNode* root)
{
    // Open file
    std::ifstream file(path);
    
    // Error opening file
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << path << std::endl;
        return root;
    }

    // Set the current parent to be the root
    TreeNode* currentParent = root;
    std::string line;

    // Read lines in file
    while (std::getline(file, line)) {
        // Skips blank lines
        if (!line.empty()) {
            // Add extra indent
            // Allows the tree to read data that has no indents and still apply it to the tree
            line.insert(0, "    ");
        
            int indentLevel = countIndentLevel(line);
            TreeNode* newNode = new TreeNode(line);

            // Find the parent node based on the indentation level
            while (indentLevel <= countIndentLevel(currentParent->data)) {
                currentParent = currentParent->parent;
            }

            currentParent->addChild(newNode);
            currentParent = newNode;
        }
    }

    // Close file
    file.close();

    // Return root with tree
    return root;
}

// Return the number of leading spaces in a string
int TreeBuilder::countLeadingSpaces(const string& line)
{
    int count = 0;
    while (count < line.size() && line[count] == ' ') {
        count++;
    }
    return count;
}

// Return the number of leading indents in a string
int TreeBuilder::countIndentLevel(const string& line) 
{
    int spaces = countLeadingSpaces(line);
    return (spaces / 4) + 1; // Assuming 4 spaces per indentation level
}