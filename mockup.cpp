#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "./lib/compiler/compiler.h"
#include "./lib/scopeTree/scopeTree.h"
#include "./lib/scopeTree/treeNode.h"
#include "./lib/scopeTree/treeBuilder.h"

int main ()
{
    // Create scope tree
    ScopeTree tree;

    // Create tree from file
    tree.root = TreeBuilder::buildTree("./test/example.mock", tree.root);
    // tree.root = TreeBuilder::buildTree("./test/includeTest.mock", tree.root);

    // Print tree to console
    // std::cout << "Raw tree:" << std::endl;
    // tree.printTree(tree.root);

    // Get current time and convert to string
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    std::tm* ptm = std::localtime(&now_c);
    std::ostringstream oss;
    oss << std::put_time(ptm, "%m-%d-%H:%M:%S");
    std::string timestamp = oss.str();

    // Create output path from timestamp
    std::string outputPath = "./build/output-" + timestamp + ".html";

    // Compile tree
    // Writes to file
    std::cout << "Compiling..." << std::endl;
    compileTree(tree.root, outputPath);
    std::cout << "Compilation complete!" << std::endl;

    return 0;
}