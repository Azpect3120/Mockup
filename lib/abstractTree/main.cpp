#include <iostream>
#include <string>
#include <vector>

#include "ASTNode.h"
#include "Util.h"

using std::string, std::vector;

int main ()
{
        
    vector<string> strings {
        "ROOT",
        "   SUB 1",
        "   SUB 2",
        "       SUB 3",
        "       SUB 4",
        "           SUB 5",
        "       SUB 6",
        "       SUB 7",
        "   SUB 8"
    };

    vector<ASTNode> nodes;

    for (string& str : strings) {
        ASTNode node = createNode(str);
        nodes.push_back(node); 
    }
    
    for (int i = 0; i < nodes.size(); i++) {
        ASTNode node = nodes[i];
        int* indentCount = node.getIndentCount();
        
        node.printNode();

    }

    // ASTNode root {"ROOT", 0};

    // ASTNode sub1 {"SUB 1", 1};
    // ASTNode sub2 {"SUB 2", 1};
    // ASTNode sub3 {"SUB 3", 1};
    // ASTNode sub4 {"SUB 4", 1};

    // ASTNode sub5  {"SUB 5", 2};    
    // ASTNode sub6  {"SUB 6", 2};    
    // ASTNode sub7  {"SUB 7", 2};    

    // sub1.setChildren(vector<ASTNode> {sub5, sub6});
    // sub2.setChildren(vector<ASTNode> {sub7});

    // root.setChildren(vector<ASTNode> {sub1, sub2, sub3, sub4});

    // root.printTree(root);
    return 0;
}