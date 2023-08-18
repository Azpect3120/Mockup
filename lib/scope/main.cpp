#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "treeNode.h"

using std::string, std::vector;

int main ()
{
    // Input file stream
    std::ifstream inputFile ("./input.mock");

    // Most recent node
    TreeNode rootNode ("{ROOT NODE}");
    TreeNode currentNode = rootNode;
    TreeNode* pRootNode = &rootNode;

    // Read lines input file
    string line;
    while (std::getline(inputFile, line)) {
        // std::cout << line << std::endl; // DEBUGGING

        // Create new node
        TreeNode newNode (line);

        // Current node has a greater indent: is a child of most recent node
        if (newNode.getIndentCount() > currentNode.getIndentCount()) {
            // Add new node as a child to the current node
            currentNode.addChild(newNode);
            newNode.setParent(&currentNode);

            // Set current node to the newly created node
            currentNode = newNode;

        // Current node has equal indent: is a child of recent nodes parent
        } else  if (newNode.getIndentCount() == currentNode.getIndentCount()) {
            // Set current node to be the parent of the current node
            currentNode = *currentNode.getParent();

            // Add new node as a child to the current node
            currentNode.addChild(newNode);
            newNode.setParent(&currentNode);

            // Set current node to the newly created node
            currentNode = newNode;

        // Current node has smaller indent: is a child of x (difference between current node indent and most recent nodes indent) nodes parent
        } else if (newNode.getIndentCount() < currentNode.getIndentCount()) {
            std::cout << "New Node: " << newNode.getData() << std::endl;
            // Loop back to first element that has an indent less than the new nodes indent value
            while (newNode.getIndentCount() < currentNode.getParent()->getIndentCount()) {
                currentNode = *currentNode.getParent();
                std::cout << "CURRENT NODE NOW = " << currentNode.getData() << std::endl;
            }

            std::cout << " New Parent: " << currentNode.getData() << std::endl;

        }

    }

    /*
    // Loop current node back to root via parent hoping
    while (currentNode.getData() != "{ROOT NODE}") {
        currentNode = *currentNode.getParent();
        std::cout << currentNode.getData() << std::endl; 
    }
    */

    currentNode.printTree(rootNode);

    return 0;
}