#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "tree.h"

int main ()
{
    // Read file
    std::ifstream InputFile ("./test.mock");

    // Create root node to hold tree
    TreeNode root ("ROOT");
    root.setParent(NULL);

    // Stores a pointer to the most recent node
    TreeNode* pCurrentNode = &root;

    std::string line;
    while (std::getline(InputFile, line)) {
        // std::cout << line << std::endl; // Debugging: PRINT LINES
        std::cout << "Current Node: " << pCurrentNode->getData() << " (" << pCurrentNode->getIndentCount() << ")" << std::endl;

        // Create new node
        TreeNode newNode (line);
        std::cout << newNode.getData() << " (" << newNode.getIndentCount() << ")" << std::endl; // Debugging: PRINT NODE VALUES

        // New node has an indent GREATER than the current node
        // Add new node as a child to the current node
        if (newNode.getIndentCount() > pCurrentNode->getIndentCount()) {
            pCurrentNode->addChild(&newNode); // Add new node to current node child vector
            newNode.setParent(pCurrentNode); // Add current node pointer to new node as parent
            pCurrentNode = &newNode; // Reset current node pointer to the newly created node 
        
        // New node has an indent EQUAL to the current node
        // Add new node as a child to the parent of the current node
        } else if (newNode.getIndentCount() == pCurrentNode->getIndentCount()) {
            pCurrentNode = pCurrentNode->getParent(); // Set current node to be current nodes parent
            pCurrentNode->addChild(&newNode); // Add new node to current node child vector
            newNode.setParent(pCurrentNode); // Add current node pointer to new node as parent
            pCurrentNode = &newNode; // Reset current node pointer to the newly created node

        // New node has an indent LESS than the current node
        // Add new node as a child to the first node found that has an indent value less than the new node
        } else if (newNode.getIndentCount() < pCurrentNode->getIndentCount()) {
            int currentIndentCount = pCurrentNode->getIndentCount();
            while (currentIndentCount != newNode.getIndentCount() - 1) {
                pCurrentNode = pCurrentNode->getParent();
                currentIndentCount = pCurrentNode->getIndentCount();
            }
            pCurrentNode->addChild(&newNode);
            newNode.setParent(pCurrentNode);
            pCurrentNode = &newNode;
        }


    }

    // Print the node tree
    // root.printTree(&root, "");

    // Loop back to top
    while (pCurrentNode->getParent() != 0) {
        pCurrentNode = pCurrentNode->getParent();
    }

    pCurrentNode->printTree(pCurrentNode, "");

    /*
    for (TreeNode* node : root.getChildren()) {
        std::cout << node->getData() << " (" << node->getIndentCount() << ")" << std::endl;
        for (TreeNode* subNode : node->getChildren()) {
            std::cout << "    " << subNode->getData() << " (" << subNode->getIndentCount() << ")" << std::endl;
        }
    }
    */

    return 0;
}