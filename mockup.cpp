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
    // std::cout << "Raw tree:" << std::endl;
    // tree.printTree(tree.root);

    // Compile tree
    // Writes to file
    std::cout << "Compiling..." << std::endl;
    compileTree(tree.root, "./output.html");
    std::cout << "Compilation complete!" << std::endl;

    return 0;
}