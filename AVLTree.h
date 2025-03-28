#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::nothrow;

class AVLTree
{
    public:
        AVLTree();
        ~AVLTree();
        void PreorderPrint();
        void InorderPrint();    //the traversal methods are the same as BST's
        void PostorderPrint();
        void Insert(string); //1st definition of Insert that is called by the user
        bool Search(string);
        bool PrintSearch(string, ofstream&); //prints in a text file the word passed to it, if found
        bool Delete(string); //1st definition of delete that is called by the user

    private:
        class Node
        {
            public:
                Node(string key) {word = key; occurrences = 1;height = 0;right = left = nullptr;}
                void Print(ofstream &out) {out<<word<<" ["<<occurrences<<"]"<<endl;} //file print
                void UpdateHeight()
                {
                    if(this->right && this->left) //node has two children so height = 1 + max(height-right, height-left)
                    {
                        if(this->right->height >= this->left->height)
                            this->height = 1 + this->right->height;
                        else
                            this->height = 1 + this->left->height;
                    }
                    else if(!this->right && !this->left) //node is a leaf so height = 0
                        this->height = 0;
                    else if(!this->left)
                        this->height = 1 + this->right->height; //node has only a right subtree so height = 1 + height-right
                    else
                        this->height = 1 + this->left->height; //else node has only a left subtree so height = 1 + height-left
                }

                int GetBalance()
                {
                    int r, l;

                    if(!this->right)
                        r = 0;
                    else
                        r = 1 + this->right->height;

                    if(!this->left)
                        l = 0;
                    else
                        l = 1 + this->left->height;

                    return r - l; //+ balance means right subtree is heavier, - balance means left subtree is heavier
                }

                int occurrences;
                int height;
                string word;
                Node* right;
                Node* left;
        };

        Node* root;

        void Clear(Node*); //recursively deletes tree
        void PreorderPrint(Node*, ofstream&);
        void InorderPrint(Node*, ofstream&);
        void PostorderPrint(Node*, ofstream&);
        void Insert(string, Node*, Node*); //2nd definition of Insert that recursively inserts a new node and balances each node that was passed until the insertion
        void Balance(Node*); //checks if any rotation is needed on a node
        void RotateRight(Node*);
        void RotateLeft(Node*);
        void Delete(string, Node*, Node*, bool&); //2nd definition of delete that recursively searches for the node to be deleted and balances the tree
        void Delete(Node*, Node*); //3rd definition of delete that deletes the node passed to it
        void FindMinOfRight(Node*, Node*, string&, int&); //recursively finds the min node of the right subtree, stores its contents and and calls the 3rd delete on it, while maintaining the balance of the tree
};

#endif // AVLTREE_H
