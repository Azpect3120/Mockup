#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "./lib/compiler/compiler.h"
#include "./lib/scopeTree/scopeTree.h"
#include "./lib/scopeTree/treeNode.h"
#include "./lib/scopeTree/treeBuilder.h"

int main ()
{
    // Create scope tree
    ScopeTree tree;

    // Create tree from file
    tree.root = TreeBuilder::buildTree("./example.mock", tree.root);

    // Print tree to console
    // std::cout << "Raw tree:" << std::endl;
    tree.printTree(tree.root);

    // Compile tree
    // Writes to file
    std::cout << "Compiling..." << std::endl;
    compileTree(tree.root, "./build/output.html");
    std::cout << "Compilation complete!" << std::endl;

    return 0;
}