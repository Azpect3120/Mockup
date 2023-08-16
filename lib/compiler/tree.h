#pragma once

#include <vector>
#include <string>

using std::string, std::vector;

class Node 
{
    private:
        string data;
        vector<Node> children;

    public:
        // Getters
        const vector<Node>* getChildren ();
        const string* getData ();

        // Setters
        void setChildren (vector<Node>);
        void setData (string);

        // Constructor
        Node (string);


};