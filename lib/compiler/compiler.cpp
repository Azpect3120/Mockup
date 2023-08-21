#include <string>
#include <vector>
#include <iostream>

#include "./compiler.h"

#include "../scopeTree/scopeTree.h"
#include "../scopeTree/treeNode.h"

using std::string;
using std::vector;

// Compile the entire tree starting at <node>
void compileTree (TreeNode* root)
{
    compileNode(root);
}

// Compile the data in the <node>
void compileNode (TreeNode* node)
{
    if (node->data.find_first_not_of(' ') == string::npos) return;

    // Check if first character is the block character (@)
    if (node->data.at(node->data.find_first_not_of(' ')) == '@') {
        node->data.erase(node->data.find_first_of("@"), 1);

        // DIV tag
        if (node->data.find("DIV") != string::npos) {
            node->data.replace(node->data.find("DIV"), 3, "<div>");
            
            std::cout << node->data << std::endl;
            
            for (TreeNode* child : node->children) {
                compileNode(child);
            }

            //std::cout << node->data.insert(node->data.find("div"), "/") << std::endl;
        }

        // UL tag
        if (node->data.find("UL") != string::npos) {
            node->data.replace(node->data.find("UL"), 2, "<ul>");
            std::cout << node->data << std::endl;
            
            for (TreeNode* child : node->children) {
                compileNode(child);
            }

            // std::cout << node->data.insert(node->data.find("ul"), "/") << std::endl;
        }

        // OL tag
        if (node->data.find("OL") != string::npos) {
            node->data.replace(node->data.find("OL"), 2, "<ol>");
            
            std::cout << node->data << std::endl;
            
            for (TreeNode* child : node->children) {
                compileNode(child);
            }

            // std::cout << node->data.insert(node->data.find("ol"), "/") << std::endl;
        }
    } else {
        std::cout << node->data << std::endl;

        for (TreeNode* child : node->children) {
            compileNode(child);
        }
    }



}

// Trim whitespace before and after <str>
void trim (string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) {
        str.clear();
        return;
    }

    size_t last = str.find_last_not_of(' ');
    str = str.substr(first, (last - first + 1));
}