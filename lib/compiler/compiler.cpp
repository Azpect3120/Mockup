#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "./compiler.h"

#include "../scopeTree/scopeTree.h"
#include "../scopeTree/treeNode.h"

using std::string;
using std::vector;

// Compile the entire tree starting at <node>
void compileTree (TreeNode* root, string path)
{
    std::ofstream outputFile(path);


    outputFile <<  "<DOCTYPE! html>\n<html lang=\"en\">" << std::endl;

    for (TreeNode* child : root->children) {
        compileNode(child, outputFile, 0);
    }

    outputFile <<  "</html>";
}

// Compile the data in the <node>
void compileNode (TreeNode* node, std::ofstream& outputFile, int indentBooster)
{
    // Create indent booster
    string boost;
    for (int i = 0; i < indentBooster; i++) {boost.append("    ");};

    // Line was blank, return
    if (node->data.find_first_not_of(' ') == string::npos) return;

    // Check if first character is the block character (@)
    if (node->data.at(node->data.find_first_not_of(' ')) == '@') {
        // Erase block character (@)
        node->data.erase(node->data.find_first_of('@'), 1);

        // DIV tag
        if (node->data.find("DIV") != string::npos) {
            // Remove div identifier
            node->data.replace(node->data.find("DIV"), 3, "<div>");
            
            // Write nodes data
            outputFile << boost <<  node->data << std::endl;
            
            // Write nodes childrens data
            for (TreeNode* child : node->children) {
                compileNode(child, outputFile, indentBooster);
            }

            // Write nodes closing data
            int indentCount = countIndentLevel(node->data) - 1;
            for (int i = 0; i < indentCount; i++) {outputFile <<  "    ";}
            outputFile << boost <<  "</div>" << std::endl;
        
        // HTML tag
        } else if (node->data.find("HTML") != string::npos) {
            // Remove html identifier
            node->data.clear();

            // Use helper to write raw html for each file
            for (TreeNode* child : node->children) {
                writeRawHtml(child, outputFile, 1);
            }

        // UL tag
        } else if (node->data.find("UL") != string::npos) {
            node->data.replace(node->data.find("UL"), 2, "<ul>");
            
            // Write node data
            outputFile << boost <<  node->data << std::endl;
            
            // Write nodes childrens data
            for (TreeNode* child : node->children) {
                // Add $LI to child if not exist
                if (child->data.find("$LI") == string::npos) {
                    child->data.insert(child->data.find_first_not_of(' '), "$LI ");
                }
                compileNode(child, outputFile, indentBooster);
            }

            // Write nodes closing data
            int indentCount = countIndentLevel(node->data) - 1;
            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}  
            outputFile << boost <<  "</ul>" << std::endl;
        

        // OL tag
        } else if (node->data.find("OL") != string::npos) {
            node->data.replace(node->data.find("OL"), 2, "<ol>");
            
            // Write node data
            outputFile << boost <<  node->data << std::endl;
            
            // Write nodes childrens data
            for (TreeNode* child : node->children) {
                // Add $LI to child if not exist
                if (child->data.find("$LI") == string::npos) {
                    child->data.insert(child->data.find_first_not_of(' '), "$LI ");
                }
                compileNode(child, outputFile, indentBooster);
            }

            // Write nodes closing data
            int indentCount = countIndentLevel(node->data) - 1;
            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "</ol>" << std::endl;

        // BODY tag
        } else if (node->data.find("BODY") != string::npos) { 
            node->data.replace(node->data.find("BODY"), 4, "<body>");

            // Write node data
            outputFile << boost <<  node->data << std::endl;
            
            // Write nodes childrens data
            for (TreeNode* child : node->children) {
                compileNode(child, outputFile, indentBooster);
            }

            // Write nodes closing data
            int indentCount = countIndentLevel(node->data) - 1;
            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "</body>" << std::endl;

        
        // HEAD tag
        } else if (node->data.find("HEAD") != string::npos) {
            node->data.replace(node->data.find("HEAD"), 4, "<head>");

            // Write node data
            outputFile << boost <<  node->data << std::endl;

            // Determine indent count
            int indentCount = countIndentLevel(node->data);

            // Add standard meta-data
            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "<meta charset=\"UTF-8\">" << std::endl;

            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">" << std::endl;            
            
            // Write nodes childrens data
            for (TreeNode* child : node->children) {
                compileNode(child, outputFile, indentBooster);
            }

            // Write nodes closing data
            for (int i = 1; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "</head>" << std::endl;

        // Line was not handled with other syntax
        } else {
            outputFile << boost <<  node->data << std::endl;

            for (TreeNode* child : node->children) {
                compileNode(child, outputFile, indentBooster);
            }
        }

    // Check if first character is the inline character ($)
    } else if (node->data.at(node->data.find_first_not_of(' ')) == '$') {
        // Remove inline character ($)
        node->data.erase(node->data.find_first_of('$'), 1);

        // TITLE tag
        if (node->data.find("TITLE") != string::npos) {
            // Remove title tag
            node->data.replace(node->data.find("TITLE"), 6, "<title>");

            // Add closing tag
            node->data.append("</title>");

            // Write node data
            outputFile << boost <<  node->data << std::endl;

        // STYLE tag
        } else if (node->data.find("STYLE") != string::npos) {
            // Remove style tag
            node->data.replace(node->data.find("STYLE"), 6, "<link rel=\"stylesheet\" href=\"");

            // Add closing tag
            node->data.append("\">");

            // Write node data
            outputFile << boost <<  node->data << std::endl;

        // SCRIPT tag
        } else if (node->data.find("SCRIPT") != string::npos) {
            // Remove script tag
            node->data.replace(node->data.find("SCRIPT"), 7, "<script src=\"");

            // Add closing tag
            node->data.append("\"></script>");

            // Write node data
            outputFile << boost <<  node->data << std::endl;

        // HTML tag
        } else if (node->data.find("HTML") != string::npos) {
            /// Remove html tag
            node->data.erase(node->data.find("HTML"), 5);

            // Write node data
            outputFile << boost << node->data << std::endl;

        // LIST ITEM tag
        } else if (node->data.find("LI") != string::npos) {
            // Get the indent count
            int indentCount = countIndentLevel(node->data) - 1;

            // Write opening tag
            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "<li>" << std::endl;

            // Remove $LI tag
            node->data.erase(node->data.find_first_of("$LI"), 3);

            // Write node data
            compileNode(node, outputFile, indentBooster + 1);

            // Write closing tag
            for (int i = 0; i < indentCount; i++) {outputFile << boost <<  "    ";}
            outputFile << boost <<  "</li>" << std::endl;

        // Unhandled 
        } else {
            outputFile << boost <<  node->data << std::endl;
        }

    // Check if first character is a heading (#<1-6>)
    } else if (node->data.at(node->data.find_first_not_of(' ')) == '#') {
        // Determine the size of the heading 
        char size = node->data.at(node->data.find_first_of('#') + 1);

        // Ensure valid size
        if (size > '6') {
            size = '6';
        } else if (size < '1') {
            size = '1';
        }

        // Convert char to h<size> string
        string tag = "h" + std::to_string(size - '0');

        // Remove heading identifier
        node->data.erase(node->data.find_first_of('#'), 3);

        // Add heading tags
        node->data.insert(node->data.find_first_not_of(' '), "<" + tag + ">");
        node->data.append("</" + tag + ">");

        // Write node data
        outputFile << boost <<  node->data << std::endl;

        // Write nodes childrens data
        for (TreeNode* child : node->children) {
            compileNode(child, outputFile, indentBooster);
        }

    // Check if node is a comment (//)
    } else if (node->data.at(node->data.find_first_not_of(' ')) == '/' && node->data.at(node->data.find_first_not_of(' ') + 1) == '/') {
        // Add <!-- --> tags
        node->data.replace(node->data.find_first_of("//"), 2 , "<!--");
        node->data.append(" -->");

        // Write node data
        outputFile << boost <<  node->data << std::endl;

        // Write childrens data
        for (TreeNode* child : node->children) {
            compileNode(child, outputFile, indentBooster);
        }
    
    // Node was not handled by other syntax: assume paragraph (p)    
    } else {
        // Add p tags
        node->data.insert(node->data.find_first_not_of(' '), "<p>");
        node->data.append("</p>");

        // Write node data
        outputFile << boost <<  node->data << std::endl;

        // Write nodes childrens data
        for (TreeNode* child : node->children) {
            compileNode(child, outputFile, indentBooster);
        }
    }


}

// Used to write raw html data
void writeRawHtml (TreeNode* node, std::ofstream& outputFile, int indentDecrement)
{
    // Handle indent Decrement
    node->data.erase(0, 4 * indentDecrement);

    // Write node data
    outputFile << node->data << std::endl;

    // Write child data
    for (TreeNode* child : node->children) {
        writeRawHtml(child, outputFile, indentDecrement);
    }
}


// Returns the number of leading indents in <str>
int countIndentLevel (string& str)
{
    int count = 0;
    while (count < str.size() && str[count] == ' ') {
        count++;
    }
    return (count / 4) + 1;
}