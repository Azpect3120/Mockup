#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./lib/compiler/compiler.h"
#include "./lib/scopeTree/scopeTree.h"
#include "./lib/scopeTree/treeNode.h"

int main ()
{
    // Create scope tree
    ScopeTree tree;

    // Create tree from file
    tree.buildTreeFromFile("./example.mock");
    
    // Print tree to console
    std::cout << "Tree:" << std::endl;
    tree.printTree(tree.root);

    std::cout << "\nRoot children: " << std::endl;
    for (TreeNode* children : tree.root->children) {
        std::cout << children->data << std::endl;
    }

    // Compile tree
    // std::cout << "\nCompiling tree: " << std::endl;
    // compileTree(tree.root);

    // Print compiled tree to console
    // tree.printTree(tree.root);

    // Print tree to new file
    // tree.writeTreeToFile("./output.html");

    return 0;
}