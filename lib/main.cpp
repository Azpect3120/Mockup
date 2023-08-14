#include <iostream>
#include <vector>
#include <string>

#include "./compiler/compiler.h"

using std::string;
using std::vector;

int main (int argc, char* argv[])
{
    // Print args given to the exe file
    /*
    for (int i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    } 
    */       

    // Create compiler object with this current path
    Compiler compiler;

    compiler.setInputPath("../../MockUp/test.mock");
    compiler.setOutputPath("../../MockUp/output.html");

    vector<string> inputLineData = compiler.readInput(); 

    vector<string> interpretedData = compiler.interpretLineData(inputLineData);

    compiler.writeOutput(interpretedData);

    return 0;
}