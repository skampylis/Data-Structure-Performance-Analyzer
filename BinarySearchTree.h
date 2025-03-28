#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::nothrow;

class BinarySearchTree
{
    public:
        BinarySearchTree();
        ~BinarySearchTree();
        void Insert(string);
        bool Search(string);
        bool PrintSearch(string, ofstream&); //prints in a text file the word passed to it, if found
        bool Delete(string);
        void PreorderPrint(); //For the traversal methods we use two definitions of each method, one that is called by main and one by the class,
        void InorderPrint();   //as main does not have access to the root
        void PostorderPrint();

    private:
        class Node
        {
            public:
                Node(string key) {word = key; occurrences = 1;right = left = nullptr;}
                void Print(ofstream &out) {out<<word<<" ["<<occurrences<<"]"<<endl;} //file print

                int occurrences;
                string word;
                Node* right;
                Node* left;
        };

        Node* root;

        bool Search(string, Node*&, Node*&); //2nd definition of search: this method will only be used by the class to search for a node to be deleted and finds both the node and its parent
        void PreorderPrint(Node*, ofstream&);
        void InorderPrint(Node*, ofstream&);
        void PostorderPrint(Node*, ofstream&);
        void Clear(Node*); //deleter of the tree called by the destructor
        void FindMinOfRight(Node*, Node*&, Node*&); //this method will be used to delete a node that has two subtrees and it finds the minimum node (and its parent) of the right subtree of the node passed to it
        void Delete(Node*, Node*);//2nd definition of delete: this is called if the first definition of delete finds the node that has the given parameter string as its word and deletes it
};

#endif // BINARYSEARCHTREE_H
