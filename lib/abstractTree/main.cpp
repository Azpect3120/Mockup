#include <iostream>
#include <string>
#include <vector>

#include "ASTNode.h"

int main ()
{
    ASTNode root {"ROOT", 0};

    ASTNode sub1 {"SUB 1", 1};
    ASTNode sub2 {"SUB 2", 1};
    ASTNode sub3 {"SUB 3", 1};
    ASTNode sub4 {"SUB 4", 1};

    ASTNode sub5  {"SUB 5", 2};    
    ASTNode sub6  {"SUB 6", 2};    
    ASTNode sub7  {"SUB 7", 2};    

    sub1.setChildren(vector<ASTNode> {sub5, sub6});
    sub2.setChildren(vector<ASTNode> {sub7});

    root.setChildren(vector<ASTNode> {sub1, sub2, sub3, sub4});

    root.printTree(root);
    





    return 0;
}