#include <string>
#include <vector>
#include <iostream>

#include "Util.h"
#include "ASTNode.h"

using std::string, std::vector;

int countIndents (string& str)
{
    int count = 0;
    for (char c : str) {
        if (c == ' ') {
            count++;
        } else {
            break;
        }
    }
    
    // Debugging
    // std::cout << count << "  ->  " << count / 3 <<  std::endl;

    return (count / 3);
}

void removeIndents (string& str)
{
    while (0 < str.length()) {
        if (str.at(0) == ' ') {
            str.erase(0, 1);
        } else {
            break;
        }
    }
}

ASTNode createNode (string& str)
{
    int indents = countIndents(str);

    // Debugging
    // std::cout << str << " (" << indents << ")" << std::endl;

    removeIndents(str);
    return ASTNode {str, indents};
}