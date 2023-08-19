#pragma once // Ensures the file is only included once
#include <iostream>
#include <vector>


using std::string;
using std::vector;

class Compiler
{    
    private:
        string inputPath;
        string outputPath;

    public:
        // File handling
        vector<string> readInput ();
        void writeOutput (vector<string>);

        // Compiler functions
        vector<string> interpretLineData (vector<string>);
        string getIDandClassParams (string, int);
        string replaceAnchors (string);

        // Utility functions
        vector<string> splitString (string&, char);
        void trim (string&);

        // Setters
        void setInputPath (string path);
        void setOutputPath (string path);

        // Getters
        string getInputPath ();
        string getOutputPath ();
};