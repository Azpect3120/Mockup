#include <iostream>
#include <string>

#include "./treeNode.h"
#include "./scopeTree.h"

using std::string;

int main ()
{
    ScopeTree scopeTree;
    scopeTree.buildTreeFromFile("../../test.mock");
    scopeTree.writeTreeToFile("../../output.html");

    return 0;
}