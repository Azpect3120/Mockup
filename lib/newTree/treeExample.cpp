#include <iostream>
#include <string>
#include <vector>

class TreeNode {
    private:
        std::string data;
        TreeNode* parent;
        std::vector<TreeNode*> children;

    public:
        TreeNode (std::string data)
        {
            this->data = data;
        }

        std::string getData ()
        {
            return data;
        }

        TreeNode* getParent ()
        {
            return parent;
        }

        std::vector<TreeNode*> getChildren ()
        {
            return children;
        }

        void setData (std::string data)
        {
            this->data = data;
        }

        void setParent (TreeNode* node)
        {
            parent = node;
        }

        void setChildren (std::vector<TreeNode*> nodes)
        {
            children = nodes;
        }

        void addChild (TreeNode* node)
        {
            children.push_back(node);
        }

        void printTree (TreeNode* node, std::string indent)
        {
            std::cout << indent << node->getData() << std::endl;

            indent.append("    ");
            for (TreeNode* sub : node->getChildren()) {
                printTree(sub, indent);
            }
        }

};

int main ()
{
    TreeNode root ("ROOT");
    root.setParent(NULL);

    TreeNode sub1 ("SUB 1");
    TreeNode sub2 ("SUB 2");
    TreeNode sub3 ("SUB 3");
    TreeNode sub4 ("SUB 4");

    std::vector<TreeNode*> children;
    children.push_back(&sub1);
    children.push_back(&sub2);
    children.push_back(&sub3);
    children.push_back(&sub4);

    sub1.setParent(&root);
    sub2.setParent(&root);
    sub3.setParent(&root);
    sub4.setParent(&root);

    TreeNode sub5 ("SUB 5");
    TreeNode sub6 ("SUB 6");

    std::vector<TreeNode*> subChildren;
    subChildren.push_back(&sub5);
    subChildren.push_back(&sub6);

    sub5.setParent(&sub1);
    sub6.setParent(&sub1);


    sub1.setChildren(subChildren);

    root.setChildren(children);


    root.printTree(&root, "");

    std::cout << "\n\n" << std::endl;
    
    TreeNode* curr = &sub6;

    std::cout << curr->getData() << std::endl;

    TreeNode* currParent = curr->getParent();
    std::cout << currParent->getData() << std::endl;

    // TreeNode* pRoot = &root;
    // std::cout << pRoot->getParent() << std::endl;

    TreeNode* pCurrNode = &sub6;
    while (pCurrNode->getParent() != 0) {
        std::cout << "BEFORE: " << pCurrNode->getData() << std::endl;
        pCurrNode = pCurrNode->getParent(); 
        std::cout << "AFTER: " << pCurrNode->getData() << std::endl;
    }

    pCurrNode->printTree(pCurrNode, "");

    return 0;
}