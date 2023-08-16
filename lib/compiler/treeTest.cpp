#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "tree.h"

using std::string, std::vector;


vector<string> readInput ()
{
    std::ifstream inputFile("./treeTest.mock");

    if (!inputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return vector<string>();
    }

    string line;
    vector<string> lineData;
    while (std::getline(inputFile, line)) {
        lineData.push_back(line);
    }

    inputFile.close();
    return lineData;
}

void writeOutput (vector<string> fileData)
{
    std::ofstream outputFile ("./output.html");

    if (!outputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    for (const auto& lineData : fileData) {
        outputFile << lineData << std::endl;
    }

    outputFile.close();
}

int main ()
{
    Node root {"<html>"};
    // Read each line and add them into the tree
    // When an indent is found, add it as a child to the most recent parent node

    vector<string> inputData = readInput();
    vector<string> upDatedData;

    for (const string str : inputData) {

    }


    writeOutput(inputData);
    
    return 0;    
}