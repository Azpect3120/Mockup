#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "compiler.h"


using std::string;
using std::vector;

// File handling
// Read <lineData> from the inputPath
vector<string> Compiler::readInput ()
{
    // Set inputFile variable to an inputFileStream
    std::ifstream inputFile(this->getInputPath());

    // File was not found: return an empty vector
    if (!inputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return vector<string>();
    }

    // Read the lines in the inputFile
    string line;
    vector<string> lineData;
    while (std::getline(inputFile, line)) {
        // std::cout << line << std::endl;
        lineData.push_back(line);
    }

    // Close the file
    inputFile.close();

    return lineData;
}

// Write <fileData> into the outputPath
void Compiler::writeOutput (vector<string> fileData)
{
    // Open a file and store it in the outputFile variable
    std::ofstream outputFile (this->getOutputPath());

    // Output file could not be opened
    if (!outputFile) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    // Write <fileData> into the file
    for (const auto& lineData : fileData) {
        outputFile << lineData << std::endl;
    }

    // Close the file
    outputFile.close();
}

// Setters
void Compiler::setInputPath (string path)
{
    this->inputPath = path;
}

void Compiler::setOutputPath (string path)
{
    this->outputPath = path;
}

// Getters
string Compiler::getInputPath ()
{
    return this->inputPath;
}

string Compiler::getOutputPath ()
{
    return this->outputPath;
}

// Returns a split string
vector<string> Compiler::splitString (string& input, char delimiter) 
{
    vector<string> result;
    size_t start = 0;
    size_t end = input.find(delimiter);

    while (end != std::string::npos) {
        result.push_back(input.substr(start, end - start));
        start = end + 1;
        end = input.find(delimiter, start);
    }

    // Push the last part of the string after the last delimiter
    result.push_back(input.substr(start));

    return result;
}

// Returns a string with all whitespaces removed
void Compiler::trim (string& str)
{
    int i = 0;
    while (i < str.length()) {
        if (str.at(i) == ' ') {
            str.erase(i, 1);
        } else {
            i++;
        }
    }
}

// Takes a string and returns the ID and CLASS provided
string Compiler::getIDandClassParams (string lineData, int last_index)
{
    // Holds final return value
    string paramString = "";
    int paramStart = lineData.find_first_of('{');
    int paramEnd = lineData.find_last_of('}');

    // Start and end parameters were found and in valid range
    if (paramStart != std::string::npos && paramEnd != std::string::npos && paramStart < last_index) {
        string params = lineData.substr(paramStart, (paramEnd - paramStart) + 1);

        // ID and Class names
        string idName;
        string className;

        // Find index of the '#' and '.' used to determine the start of the id/class definiton 
        int idIndex = params.find('#');
        int classIndex = params.find('.');

        // Both found
        if (idIndex > 0 && classIndex > 0) {
            if (idIndex < classIndex) {
                idName = params.substr(idIndex + 1, classIndex - idIndex - 1); 
                className = params.substr(classIndex + 1, params.length() - classIndex - 2);
            } else if (idIndex > classIndex) {
                className = params.substr(classIndex + 1, idIndex - classIndex - 1);
                idName = params.substr(idIndex + 1, params.length() - idIndex - 2);
            }
            paramString.append(" id=\"" + idName + "\" class=\"" + className + "\"");

        // Only ID found
        } else if (idIndex > 0 && classIndex < 0) {
            idName = params.substr(idIndex + 1, params.length() - idIndex - 2);
            paramString.append(" id=\"" + idName + "\"");

        // Only class Found
        } else if (classIndex > 0 && idIndex < 0) {
            className = params.substr(classIndex + 1, params.length() - classIndex - 2);                    
            paramString.append(" class=\"" + className + "\"");
        }
    }
    return paramString;
}

// Finds all anchor tags and replaces them
string Compiler::replaceAnchors(string lineData)
{
    // Indicies of various points
    int anchorStart = lineData.find('[');
    int anchorEnd = lineData.find(']');
    int linkStart = lineData.find('(');
    int linkEnd = lineData.find(')');

    // Ensure indicies match the syntax ']('
    if (anchorEnd == linkStart - 1) {
        // Get url from syntax
        string url = lineData.substr(linkStart + 1, linkEnd - linkStart - 1);
        
        // Check for ID/Class defintions
        string paramString = getIDandClassParams(lineData, lineData.length());

        // Replace [ with <a href="">
        lineData.replace(anchorStart, 1, "<a href=\"" + url + "\"" + paramString +">");

        // Replace ] with </a>
        lineData.replace(lineData.find(']'), 1, "</a>");
        
        // Remove url 
        lineData.erase(lineData.find('('), lineData.find(')') - lineData.find('(') + 1);
        
        // Remove parameters
        if (paramString != "") lineData.erase(lineData.find_first_of('{'), lineData.find_first_of('}') - lineData.find_first_of('{') + 1);
    }
    return lineData;
}

// Interprets the inputted file data and returns the new data
vector<string> Compiler::interpretLineData (vector<string> inputData)
{
    // Holds new data
    vector<string> interpretedData;

    // Header data
    interpretedData.push_back("<!DOCTYPE html>");
    interpretedData.push_back("<html lang=\"en\">");
    interpretedData.push_back("<head>");
    interpretedData.push_back("    <meta charset=\"UTF-8\">");
    interpretedData.push_back("    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");

    // Read file and search for header meta data
    for (string& lineData : inputData) {
        // @title meta data
        if (lineData.substr(0, 6) == "@title") {
            lineData.erase(0, 6);
            interpretedData.push_back("    <title>" + lineData + "</title>");
            lineData.insert(0, "@title");

        // @style meta data
        } else if (lineData.substr(0, 6) == "@style") {
            lineData.erase(0, 6);
            interpretedData.push_back("    <link rel=\"stylesheet\" href=\"" + lineData + "\">");
            lineData.insert(0, "@style");
        }
    }

    // Finish header data
    interpretedData.push_back("</head>");
    interpretedData.push_back("<body>");
    
    // Interpret each line
    for (string& lineData : inputData) {

        // DETERMINE THE NUMBER OF SPACES BEFORE THE TEXT
        int spaceCount = 0;
        string indent = "";

        // Determine size of indent
        for (int i = 0; i < lineData.length(); i++) {
            if (lineData.at(i) == ' ') {
                spaceCount++;
                indent.append(" ");
            } else {
                break;
            }
        }

        // Remove indents from the string
        lineData.replace(0, spaceCount, "");


        // META TAGS
        if (lineData.substr(0, 6) == "@style" || lineData.substr(0, 6) == "@title") {
            // SKIP
            continue;
            

        // HEADER TAG #<1-6>
        } else if (!lineData.empty() && lineData.at(0) == '#') {
            // Header size
            char size = lineData.at(1);
            
            // Ensure value is between 1 and 6
            if ((size - '0') > 6) {
                size = '6';
            } else if ((size - '0' < 1)) {
                size = '1';
            }
            
            // Returns a string with ID and CLASS name
            string paramString = getIDandClassParams(lineData, 4);

            // Parameters were given, remove parameters from string
            if (paramString != "") lineData.erase(lineData.find_first_of('{'), lineData.find_first_of('}') - lineData.find_first_of('{') + 1);

            // Replace #1 with <h1>
            lineData.replace(0, 2, "<h" + string(1, size) + paramString + ">");

            // Add closing tag
            lineData.append("</h" + string(1, size) + ">");

            // Find and replace anchors
            lineData = replaceAnchors(lineData);

            // Add indent
            lineData.insert(0, indent + "   ");
            
            // Add lineData to new vector
            interpretedData.push_back(lineData);


        // RAW HTML TAG @html
        } else if (lineData.substr(0, 5) == "@html") {
            // Remove @html tag
            lineData.erase(0, 5);

            // Remove whitespace between start of code and @html tag
            char curr = lineData.at(0);
            while (curr == ' ') {
                curr = lineData.at(1);
                lineData.erase(0, 1);
            }

            // Add indent
            lineData.insert(0, indent + "   "); 

            // Add new data back into vector
            interpretedData.push_back(lineData);


        // SCRIPT TAG
        } else if (lineData.substr(0, 7) == "@script") {
            // Remove @script tag
            lineData.erase(0, 7);
            
            // Remove whitespace between start of code and @script tag
            char curr = lineData.at(0);
            while (curr == ' ') {
                curr = lineData.at(1);
                lineData.erase(0, 1);
            }

            // Convert line to html script tag
            lineData.insert(0, "<script src=\"");
            lineData.append("\"></script>");

            // Add indent
            lineData.insert(0, indent + "   "); 

            // Add new data back into vector
            interpretedData.push_back(lineData);

        // COMMENTS <!-- -->
        } else if (lineData.substr(0, 2) == "//") {
            // Remove // tag
            lineData.erase(0, 2);

            // Remove whitespace between start of code and // tag
            char curr = lineData.at(0);
            while (curr == ' ') {
                curr = lineData.at(1);
                lineData.erase(0, 1);
            }
            
            // Convert to comment
            lineData.insert(0, "<!--");
            lineData.append("-->");

            // Add indent
            lineData.insert(0, indent + "   "); 

            // Add new data back into vector
            interpretedData.push_back(lineData);



        // BUTTON TAG <button>
        } else if (lineData.substr(0, 4) == "!BTN") {
            // Remove !BTN tag
            lineData.erase(0, 4);

            // Remove whitespace between start of code and !BTN tag
            char curr = lineData.at(0);
            while (curr == ' ') {
                curr = lineData.at(1);
                lineData.erase(0, 1);
            }

            // Get params
            string params = getIDandClassParams(lineData, 1); 

            // Remove param args
            if (params != "") lineData.erase(lineData.find_first_of('{'), lineData.find_first_of('}') - lineData.find_first_of('{') + 1);

            // Convert to <button> tag
            lineData.insert(0, "<button" + params + ">");
            lineData.append("</button>");

            // Add indent
            lineData.insert(0, indent + "   ");

            // Add new data back into vector
            interpretedData.push_back(lineData);

        // INPUT TAG <input>
        } else if (lineData.substr(0, 4) == "!INP") {
            // Remove !INP tag
            lineData.erase(0, 4);

            // Get input parameters
            string typeParamString = lineData.substr(lineData.find_first_of('[') + 1, lineData.find_first_of(']') - lineData.find_first_of('[') - 1);

            // Get ID/class parameters
            string classParams = getIDandClassParams(lineData, lineData.find_first_of(']') + 2);
            if (classParams != "") lineData.erase(lineData.find_first_of('{'), lineData.find_first_of('}') - lineData.find_first_of('{') + 1);

            // Remove input parameters
            lineData.erase(lineData.find_first_of('['), lineData.find_first_of(']') - lineData.find_first_of('[') + 1);

            // Remove whitespace before value
            for (int i = 0; i < lineData.length(); i++) {
                if (lineData.at(i) == ' ') {
                    lineData.erase(i, 1);
                    i--;
                } else break;
            }

            // Get vector with inputs
            vector<string> typeParamList = splitString(typeParamString, ',');

            // Holds the inputted values
            bool required = false;
            bool placeholder = false;
            string type = "";
            

            // Find values in string
            for (string& str : typeParamList) {
                trim(str);

                if (str == "r") required = true;
                else if (str == "placeholder") placeholder = true;
                else type = str;
            }

            string openTag = "<input type=\"" + type + "\"" + classParams;

            // Convert to <input> tag
            if (required) openTag.append(" required");
            if (placeholder) openTag.append(" placeholder=\"");
            else openTag.append(" value=\"");

            lineData.insert(0, openTag);
            lineData.append("\">");
            
            // Add indent
            lineData.insert(0, indent + "   ");

            // Add new data back into vector
            interpretedData.push_back(lineData); 

        // NOTHING, ASSUME P
        } else if (lineData != "") {
            // ID and Class name parameters
            string paramString = getIDandClassParams(lineData, 4);

            // Parameters were given, remove parameters from string
            if (paramString != "") lineData.erase(lineData.find_first_of('{'), lineData.find_last_of('}') - lineData.find_first_of('{') + 1);

            // Reformat string            
            lineData.insert(0, "<p" + paramString + ">");
            lineData.append("</p>");

            // Find and replace anchors
            lineData = replaceAnchors(lineData);

            // Add indent
            lineData.insert(0, indent + "   ");

            // Add lineData to new vector
            interpretedData.push_back(lineData);
        

        // BLANK LINE
        } else {
            interpretedData.push_back("    " + lineData);
        }

    }
    
    // CLOSE HTML BOILERPLATE
    interpretedData.push_back("</body>");
    interpretedData.push_back("</html>");
    
    // Return updated data
    return interpretedData;
}

