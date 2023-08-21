#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "./treeNode.h"
#include "./scopeTree.h"

using std::string, std::vector;

// Object constructor
ScopeTree::ScopeTree ()
{
    this->root = new TreeNode("Root");
}

// Build the tree from a text file
void ScopeTree::buildTreeFromFile(const string& filename)
{
    // Open file
    std::ifstream file(filename);
    
    // Error opening file
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    // Set the current parent to be the root
    TreeNode* currentParent = root;
    std::string line;

    // Read lines in file
    while (std::getline(file, line)) {
        // Skips empty lines
        //if (line.empty()) {
            line.insert(0, "    ");
        //}

        int indentLevel = countIndentLevel(line);
        TreeNode* newNode = new TreeNode(line);

        // Find the parent node based on the indentation level
        while (indentLevel <= countIndentLevel(currentParent->data)) {
            currentParent = currentParent->parent;
        }

        currentParent->addChild(newNode);
        currentParent = newNode;
    }

    file.close();
}

// Traversal: Depth-First Search (DFS) - Preorder
void ScopeTree::traverseDFS (TreeNode* node, std::ofstream& outFile)
{
    if (!node) return;

    // Write the node's data to the file
    outFile << node->data << std::endl;

    for (TreeNode* child : node->children) {
        traverseDFS(child, outFile);
    }

    // Write closing tag here
}

// Write the tree to a file
void ScopeTree::writeTreeToFile (const string& filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Unable to open file for writing: " << filename << std::endl;
        return;
    }

    // Start traversal from the root node
    traverseDFS(root, outFile);

    outFile.close();
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

// Return the number of leading spaces in a string
int ScopeTree::countLeadingSpaces(const string& line) {
    int count = 0;
    while (count < line.size() && line[count] == ' ') {
        count++;
    }
    return count;
}

// Return the number of leading indents in a string
int ScopeTree::countIndentLevel(const string& line) {
    int spaces = countLeadingSpaces(line);
    return (spaces / 4) + 1; // Assuming 4 spaces per indentation level
}