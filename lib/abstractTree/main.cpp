#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stack>
#include <fstream>


#include "ASTNode.h"
#include "Util.h"

using std::string, std::vector, std::stack;

int main ()
{
    /*  
    // FROM VECTOR
    // ------------------------------------------------------------------  
    vector<string> strings {
        "ROOT",
        "   SUB 1",
        "   SUB 2",
        "       SUB 3",
        "       SUB 4",
        "           SUB 5",
        "       SUB 6",
        "       SUB 7",
        "   SUB 8",
        "SUB 9",
        "       SUB 10"
    };

    // List of nodes
    vector<ASTNode> nodes;

    // Create nodes
    for (string& str : strings) {
        ASTNode node = createNode(str);
        nodes.push_back(node); 
    }

    // Root node tree            
    ASTNode& root = nodes.front();

    // Place nodes
    for (int i = 1; i < nodes.size(); i++) {
        ASTNode node = nodes[i];
        int* indentCount = node.getIndentCount();

        root.addChild(node);

        // node.printNode();
    }

    root.printChildren();
    */

    // Display tree
    // root.printTree(root);

    // MANUAL
    // ------------------------------------------------------------
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

    // READING FILE
    // ----------------------------------------
    string inputPath = "./test.mock";   // Input file path

    std::ifstream inputFile (inputPath);    // Open file as stream

    ASTNode ROOT = {"ROOT NODE", 0};    // Create root node for AST
    
    stack<ASTNode> nodeStack ({ROOT});  // Node stack. Initialized with ROOT

    string line;    // Holds line data
    while (std::getline(inputFile, line)) {
        // std::cout << line << std::endl;  // Print each line: DEBUGGING

        ASTNode node = createNode(line);    // Create a new node using the line data

        // node.printNode();   // Print each node: DEBUGGING
        
        int currIndent = *node.getIndentCount();    // Current indent value
        int lastIndent = *nodeStack.top().getIndentCount(); // Most recent stack item value
        
        std::cout << "Curr: " << currIndent << " Last: " << lastIndent << std::endl;

        // Current item is a child of the most recent stack item
        // add current as a child of the top of stack
        if (currIndent > lastIndent) {
            ASTNode& top = nodeStack.top();  // Top item in stack

            top.addChild(node);    // Add new node to top item on stack

            nodeStack.push(node);   // Add new node to top of stack

            std::cout << "NODE ADDED TO LAST ELEMENT" << std::endl;


        // Current item is not a child of most recent stack item
        // remove stack top and add new element as a child of the stacks new top 
        } else if (currIndent == lastIndent) {
            nodeStack.pop();    // Remove top item

            ASTNode& top = nodeStack.top();    // Top item in stack 

            top.addChild(node);

            nodeStack.push(node);

            std::cout << "NODE WAS ADDED LAST'S PARENT ELEMENT" << std::endl;

        // Current item is not a child of most recent stack item
        // remove stack top 'n' times (n = difference between curr and last) and add new element as a child of the stacks new top
        } else if (currIndent < lastIndent) {



        }
    }


    inputFile.close();  // Close input file

    std::cout << "\nTree: " << std::endl;
    ROOT.printTree(ROOT);   // Display final tree

    return 0;
}