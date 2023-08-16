#include <string>
#include <vector>
#include <iostream>

#include "Util.h"

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

    return count / 4;
}