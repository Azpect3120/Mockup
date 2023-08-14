#include <iostream>
#include <vector>
#include <string>

#include "./compiler/compiler.h"

using std::string;
using std::vector;

int main (int argc, char* argv[])
{
   if (argc != 2) {
    std::cerr << "Please provide a path." << std::endl;
    return 1;

   } else {
        Compiler compiler; // Create compiler object with this current path

        compiler.setInputPath(argv[1]); // Set the input file to the user defined path

        // Convert user defined path to output file
        string outputPath = argv[1];
        outputPath.replace(outputPath.length() - 4, 4, "html");

        compiler.setOutputPath(outputPath); // Set the output path
        vector<string> inputLineData = compiler.readInput(); // Read data from input file 
        vector<string> interpretedData = compiler.interpretLineData(inputLineData); // Compile input data
        compiler.writeOutput(interpretedData); // Write compiled data into output file.
   }
    return 0;
}