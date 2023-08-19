#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class TreeNode {
public:
    std::string data;
    TreeNode* parent;
    std::vector<TreeNode*> children;

    TreeNode(const std::string& val) : data(val), parent(nullptr) {}

    // Add a child node to this node
    void addChild(TreeNode* child) {
        child->parent = this;
        children.push_back(child);
    }
};

class ScopeTree {
public:
    TreeNode* root;

    ScopeTree() : root(new TreeNode("Root")) {}

    // Build the tree from a text file
    void buildTreeFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            return;
        }

        TreeNode* currentParent = root;
        std::string line;

        while (std::getline(file, line)) {
            // Add a single indent padding to each line
            // As well as allow lines to be skipped
            line.insert(0, "    ");

            int indentLevel = countLeadingSpaces(line);
            TreeNode* newNode = new TreeNode(line);

            // Find the parent node based on the indentation level
            while (indentLevel <= countIndentLevel(currentParent->data)) {
                currentParent = currentParent->parent;
            }

            currentParent->addChild(newNode);
            currentParent = newNode;
        }

        file.close();
    }

    // Traversal: Depth-First Search (DFS) - Preorder
    void traverseDFS(TreeNode* node, std::ofstream& outFile) {
        if (!node) return;

        // Write the node's data to the file
        outFile << node->data << std::endl;

        for (TreeNode* child : node->children) {
            traverseDFS(child, outFile);
        }
    }

    // Write the tree to a file
    void writeTreeToFile(const std::string& filename) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Unable to open file for writing: " << filename << std::endl;
            return;
        }

        // Start traversal from the root node
        traverseDFS(root, outFile);

        outFile.close();
    }

private:
    int countLeadingSpaces(const std::string& line) {
        int count = 0;
        while (count < line.size() && line[count] == ' ') {
            count++;
        }
        return count;
    }

    int countIndentLevel(const std::string& line) {
        int spaces = countLeadingSpaces(line);
        return spaces / 4; // Assuming 4 spaces per indentation level
    }
};

int main() {
    ScopeTree scopeTree;
    scopeTree.buildTreeFromFile("test.mock");

    // Write the tree to a file
    scopeTree.writeTreeToFile("output.txt");

    return 0;
}