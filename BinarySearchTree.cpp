#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
{
    root = nullptr;
}

BinarySearchTree::~BinarySearchTree()
{
    Clear(root);
}

void BinarySearchTree::FindMinOfRight(Node* currentNode, Node* &minNode, Node* &parentMinNode)
{
    Node* previousNode = currentNode;
    currentNode = currentNode->right;

    while(currentNode->left)
    {
        previousNode = currentNode;
        currentNode = currentNode->left;
    }

    minNode = currentNode;
    parentMinNode = previousNode;
}

void BinarySearchTree::Clear(Node* n)
{
    if(!n)
        return;

    Clear(n->left);
    Clear(n->right);
    delete n;
}

void BinarySearchTree::Insert(string key)
{
    if(root)
    {
        Node* currentNode = root;
        Node* previousNode = nullptr;

        while(currentNode)
        {
            previousNode = currentNode;

            if(key > currentNode->word)
                currentNode = currentNode->right;
            else if(key < currentNode->word)
                currentNode = currentNode->left;
            else
            {
                currentNode->occurrences++;
                return;
            }
        }

        //if we have found a null pointer, the new word that will be inserted will be a child of the previousNode
        if(key > previousNode->word)
        {
            previousNode->right = new(nothrow) Node(key);

            if(!previousNode->right)
            {
                cout<<"BST memory allocation failed"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            previousNode->left = new(nothrow) Node(key);

            if(!previousNode->left)
            {
                cout<<"BST memory allocation failed"<<endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    else
    {
        root = new(nothrow) Node(key);

        if(!root)
        {
            cout<<"BST memory allocation failed"<<endl;
            exit(EXIT_FAILURE);
        }
    }
}

bool BinarySearchTree::Search(string key)
{
    Node* currentNode = root;

    while(currentNode)
    {
        if(key > currentNode->word)
            currentNode = currentNode->right;
        else if(key < currentNode->word)
            currentNode = currentNode->left;
        else
            return true;
    }

    return false;
}

bool BinarySearchTree::Search(string key, Node* &child, Node* &parent)
{
    Node* currentNode = root;
    Node* previousNode = nullptr;

    while(currentNode)
    {
        if(key > currentNode->word)
        {
            previousNode = currentNode;
            currentNode = currentNode->right;
        }
        else if(key < currentNode->word)
        {
            previousNode = currentNode;
            currentNode = currentNode->left;
        }
        else
        {
            child = currentNode;
            parent = previousNode;
            return true;
        }
     }

     return false;
}

bool BinarySearchTree::Delete(string key)
{
    Node* child = nullptr;
    Node* parent = nullptr;

    if(!(Search(key, child, parent)))
        return false;

    Delete(child, parent);
    return true;
}

void BinarySearchTree::Delete(Node* child, Node* parent)
{

    bool flag = false; //we use this flag to determine whether the node to be deleted is the right(true) or the left(false) child of its parent
    if(parent && parent->right == child) //also if we are deleting the root and parent is nullptr we don't mind that flag is false (indicating that the node to be deleted
        flag = true;                     //is the left child of its parent) as we always check parent before we use flag

    //case 1: node to be deleted is a leaf
    if(!child->right && !child->left)
    {
        if(parent)
        {
            if(flag)
                parent->right = nullptr;
            else
                parent->left = nullptr;

            delete child;
        }
        else //if there is no parent we are deleting the root
        {
            delete root;
            root = nullptr;
        }

        return;
    }

    //case 2: node to be deleted has only one subtree
    if(!child->left) //only right subtree
    {
        if(parent)
        {
            if(flag)
                parent->right = child->right;
            else
                parent->left = child->right;

            delete child;
        }
        else //root deletion
        {
            Node* temp = root->right;
            delete root;
            root = temp;
        }

        return;
    }

    if(!child->right) //only left subtree
    {
        if(parent)
        {
            if(flag)
                parent->right = child->left;
            else
                parent->left = child->left;

            delete child;
        }
        else //root deletion
        {
            Node* temp = root->left;
            delete root;
            root = temp;
        }

        return;
    }

    //case 3: node to be deleted has two subtrees
    Node* minRightNode;
    Node* parentMinRightNode;
    Node* temp;


    FindMinOfRight(child, minRightNode, parentMinRightNode);
    temp = new(nothrow) Node(minRightNode->word);

    if(!temp)
    {
        cout<<"BST memory allocation failed during node deletion"<<endl;
        exit(EXIT_FAILURE);
    }

    temp->occurrences = minRightNode->occurrences;

    Delete(minRightNode, parentMinRightNode);  //we first delete the min_right node because there is a chance the node to be deleted and the parent of the min_right are the same node
                                               // this way we make sure the every node's children will be correct
    temp->right = child->right;                //also this call of Delete() will fall one one of the first two cases as min_right will either be a leaf or have a right subtree
    temp->left = child->left;

    delete child;

    if(parent)
    {
        if(flag)
            parent->right = temp;
        else
            parent->left = temp;
    }
    else  //we have deleted the root
        root = temp;
}

void BinarySearchTree::PreorderPrint(Node* n, ofstream &output)
{
    if(!n)
        return;

    n->Print(output);
    PreorderPrint(n->left, output);
    PreorderPrint(n->right, output);
}

void BinarySearchTree::InorderPrint(Node* n, ofstream &output)
{
    if(!n)
        return;

    InorderPrint(n->left, output);
    n->Print(output);
    InorderPrint(n->right, output);
}

void BinarySearchTree::PostorderPrint(Node* n, ofstream &output)
{
    if(!n)
        return;

    PostorderPrint(n->left, output);
    PostorderPrint(n->right, output);
    n->Print(output);
}

bool BinarySearchTree::PrintSearch(string key, ofstream& output)
{
    Node* currentNode = root;

    while(currentNode)
    {
        if(key > currentNode->word)
            currentNode = currentNode->right;
        else if(key < currentNode->word)
                currentNode = currentNode->left;
        else
        {
            currentNode->Print(output);
            return true;
        }
    }

    return false;
}

void BinarySearchTree::PreorderPrint()
{
    ofstream output("BSTPreorder.txt");

    if(output.is_open())
    {
        PreorderPrint(root, output);
        output.close();
    }
    else
    {
        cout<<"Couldn't open BST Preorder output file"<<endl;
        exit(EXIT_FAILURE);
    }
}

void BinarySearchTree::InorderPrint()
{
    ofstream output("BSTInorder.txt");

    if(output.is_open())
    {
        InorderPrint(root, output);
        output.close();
    }
    else
    {
        cout<<"Couldn't open BST Inorder output file"<<endl;
        exit(EXIT_FAILURE);
    }
}

void BinarySearchTree::PostorderPrint()
{
    ofstream output("BSTPostorder.txt");

    if(output.is_open())
    {
        PostorderPrint(root, output);
        output.close();
    }
    else
    {
        cout<<"Couldn't open BST Postorder output file"<<endl;
        exit(EXIT_FAILURE);
    }
}
