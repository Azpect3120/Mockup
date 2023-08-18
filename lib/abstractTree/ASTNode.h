#pragma once

#include <vector>
#include <string>

using std::string, std::vector;

class ASTNode
{
    private:
        string data;
        ASTNode* parent;
        int indentCount;
        vector<ASTNode> children;

    public:
        // Constructor
        ASTNode (ASTNode&, string, int);

        // Getters
        string* getData ();
        int* getIndentCount ();
        vector<ASTNode>* getChildren ();
        ASTNode* getParent ();

        // Setters
        void setData (string);
        void setParent (ASTNode);
        void setIndentCount (int);
        void setChildren (vector<ASTNode>);
        void addChild (ASTNode);

        // Utils
        void printNode ();
        void printChildren ();
        void printTree (ASTNode);
};