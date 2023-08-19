#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "tree.h"

int main ()
{
    // Write lines from input file to vector
    std::ifstream inputFile ("./test.mock");

    std::vector<TreeNode> nodes;
    
    std::string line;
    while (std::getline(inputFile, line)) {
        nodes.push_back(TreeNode (line));
    }    

    // Create tree
    TreeNode root ("ROOT");

    for (TreeNode node : nodes) {
        if (node.getIndentCount() == 1) {
            root.addChild(&node);
            node.setParent(&root);
        }

    }

    for (TreeNode* node : root.getChildren()) {
        std::cout << node->getData() << std::endl;
    }

    root.printTree(&root, "");

    return 0;
}