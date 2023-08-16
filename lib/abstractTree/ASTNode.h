#pragma once

#include <vector>
#include <string>

using std::string, std::vector;

class ASTNode
{
    private:
        string data;
        int indentCount;
        vector<ASTNode> children;

    public:
        // Constructor
        ASTNode (string, int);

        // Getters
        string* getData ();
        int* getIndentCount ();
        vector<ASTNode>* getChildren ();

        // Setters
        void setData (string);
        void setIndentCount (int);
        void setChildren (vector<ASTNode>);

        // Utils
        void printNode ();
        void printChildren ();
        void printTree (ASTNode);
};