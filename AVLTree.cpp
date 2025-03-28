#include "AVLTree.h"

AVLTree::AVLTree()
{
    root = nullptr;
}

AVLTree::~AVLTree()
{
    Clear(root);
}

void AVLTree::Clear(Node* n)
{
    if(!n)
        return;

    Clear(n->left);
    Clear(n->right);
    delete n;
}

void AVLTree::PreorderPrint(Node* n, ofstream &output)
{
    if(!n)
        return;

    n->Print(output);
    PreorderPrint(n->left, output);
    PreorderPrint(n->right, output);
}

void AVLTree::InorderPrint(Node* n, ofstream &output)
{
    if(!n)
        return;

    InorderPrint(n->left, output);
    n->Print(output);
    InorderPrint(n->right, output);
}

void AVLTree::PostorderPrint(Node* n, ofstream &output)
{
    if(!n)
        return;

    PostorderPrint(n->left, output);
    PostorderPrint(n->right, output);
    n->Print(output);
}

void AVLTree::Insert(string key)
{
    if(root)
        Insert(key, root, nullptr);
    else
    {
        root = new(nothrow) Node(key);

        if(!root)
        {
            cout<<"AVL memory allocation failed"<<endl;
            exit(EXIT_FAILURE);
        }
    }
}

void AVLTree::Insert(string key, Node* currentNode, Node* previousNode)
{
    if(!currentNode) //if a null pointer was found the new word will be inserted as a child node of the previousNode
    {
        if(key > previousNode->word)
        {
            previousNode->right = new(nothrow) Node(key);

            if(!previousNode->right)
            {
                cout<<"AVL memory allocation failed"<<endl;
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            previousNode->left = new(nothrow) Node(key);

            if(!previousNode->left)
            {
                cout<<"AVL memory allocation failed"<<endl;
                exit(EXIT_FAILURE);
            }
        }

        return;
    }

    if(key > currentNode->word)
        Insert(key, currentNode->right, currentNode);
    else if(key < currentNode->word)
        Insert(key, currentNode->left, currentNode);
    else
    {
        currentNode->occurrences++;
        return;
    }

    currentNode->UpdateHeight();
    Balance(currentNode);
}

void AVLTree::Balance(Node* currentNode)
{
    int balance = currentNode->GetBalance();

    if(balance == -2)
    {
        int balanceLeft = currentNode->left->GetBalance();

        if(balanceLeft > 0) //left-right heavy
        {
            RotateLeft(currentNode->left);
            RotateRight(currentNode);
        }
        else //left-left heavy
            RotateRight(currentNode);
    }

    if(balance == 2)
    {
        int balanceRight = currentNode->right->GetBalance();

        if(balanceRight >= 0) //right-right heavy
            RotateLeft(currentNode);
        else //right-left heavy
        {
            RotateRight(currentNode->right);
            RotateLeft(currentNode);
        }
    }
}

void AVLTree::RotateRight(Node* x)
{
    Node* y = x->left;

    Node *tempxRight = new(nothrow) Node(x->word);       //we build the node that will be the right child of the node in x's position after the rotation

    if(!tempxRight)
    {
        cout<<"AVL memory allocation failed during right rotation"<<endl;
        exit(EXIT_FAILURE);
    }

    tempxRight->occurrences = x->occurrences;
    tempxRight->right = x->right;
    tempxRight->left = y->right;

    Node *tempx = new(nothrow) Node(y->word);     //we build the node that will be in node x's position after the rotation

    if(!tempx)
    {
        cout<<"AVL memory allocation failed during right rotation"<<endl;
        exit(EXIT_FAILURE);
    }

    tempx->occurrences = y->occurrences;
    tempx->right = tempxRight;
    tempx->left = y->left;

    delete y;    //the tempx node is the y node after the rotation, so the y node is no longer needed

    *x = *tempx;       //we perform the rotation by assigning the tempx node to the current subtree's root

    delete tempx;      //we delete the extra temporary node we created

    x->right->UpdateHeight();
    x->UpdateHeight();
}

void AVLTree::RotateLeft(Node* x)
{
    Node* y = x->right;

    Node* tempxLeft = new(nothrow) Node(x->word);

    if(!tempxLeft)
    {
        cout<<"AVL memory allocation failed during left rotation"<<endl;
        exit(EXIT_FAILURE);
    }

    tempxLeft->occurrences = x->occurrences;
    tempxLeft->right = y->left;
    tempxLeft->left = x->left;

    Node* tempx = new(nothrow) Node(y->word);        //we follow the exact same logic as we did with the RotateRight method

    if(!tempx)
    {
        cout<<"AVL memory allocation failed during left rotation"<<endl;
        exit(EXIT_FAILURE);
    }

    tempx->occurrences = y->occurrences;
    tempx->right = y->right;
    tempx->left = tempxLeft;

    delete y;

    *x = *tempx;

    delete tempx;

    x->left->UpdateHeight();
    x->UpdateHeight();
}

bool AVLTree::Search(string key)
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

bool AVLTree::Delete(string key)
{
    bool found = false;
    Delete(key, root, nullptr, found);

    return found;
}

void AVLTree::Delete(string key, Node* currentNode, Node* previousNode, bool &found)
{
    if(!currentNode)
    {
        found = false;
        return;
    }

    if(key > currentNode->word)
        Delete(key, currentNode->right, currentNode, found);
    else if(key < currentNode->word)
        Delete(key, currentNode->left, currentNode, found);
    else
    {
        Delete(currentNode, previousNode);
        found = true;
        return;
    }

    currentNode->UpdateHeight();
    Balance(currentNode);
}

void AVLTree::Delete(Node* child, Node* parent)
{
    bool flag = false;  //same as BST, true indicates node is right child and false indicates that node is left child
    if(parent && parent->right == child)
        flag = true;

    //case 1: node to be deleted is a leaf (same as binary search tree)
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
        else
        {
            delete root;
            root = nullptr;
        }
        return;
    }

    //case 2: node to be deleted has only one subtree (same as binary search tree)
    if(!child->left)
    {
        if(parent)
        {
            if(flag)
                parent->right = child->right;
            else
                parent->left = child->right;

            delete child;
        }
        else
        {
            Node* temp = root->right;
            delete root;
            root = temp;
        }

        return;
    }

    if(!child->right)
    {
        if(parent)
        {
            if(flag)
                parent->right = child->left;
            else
                parent->left = child->left;

            delete child;
        }
        else
        {
            Node* temp = root->left;
            delete root;
            root = temp;
        }

        return;
    }

    //case 3: node to be deleted has two subtrees (case 3 had to be slightly altered to be able to maintain the balance of the tree)
    string minWord;
    int minOccurrences;
    Node* temp;

    FindMinOfRight(child->right, child, minWord, minOccurrences);

    temp = new(nothrow) Node(minWord);

    if(!temp)
    {
        cout<<"AVL memory allocation failed during deletion"<<endl;
        exit(EXIT_FAILURE);
    }

    temp->occurrences = minOccurrences;
    temp->right = child->right;
    temp->left = child->left;

    temp->UpdateHeight();   //we balance the subtree that had the deleted node as a root
    Balance(temp);          //and then we connect it with the rest of the tree

    delete child;

    if(parent)
    {
        if(flag)
            parent->right = temp;
        else
            parent->left = temp;
    }
    else
        root = temp;
}

void AVLTree::FindMinOfRight(Node* currentNode, Node* previousNode, string &minWord, int &minOccurrences)
{
    if(currentNode->left)
        FindMinOfRight(currentNode->left, currentNode, minWord, minOccurrences);
    else
    {
        minWord = currentNode->word;
        minOccurrences = currentNode->occurrences;
        Delete(currentNode, previousNode); //this call will fall one one of the first two cases of the delete method
        return;
    }

    currentNode->UpdateHeight();
    Balance(currentNode);
}

bool AVLTree::PrintSearch(string key, ofstream &output)
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

void AVLTree::PreorderPrint()
{
    ofstream output("AVLPreorder.txt");

    if(output.is_open())
    {
        PreorderPrint(root, output);
        output.close();
    }
    else
    {
        cout<<"Couldn't open AVL Preorder output file"<<endl;
        exit(EXIT_FAILURE);
    }
}

void AVLTree::InorderPrint()
{
    ofstream output("AVLInorder.txt");

    if(output.is_open())
    {
        InorderPrint(root, output);
        output.close();
    }
    else
    {
        cout<<"Couldn't open AVL Inorder output file"<<endl;
        exit(EXIT_FAILURE);
    }
}

void AVLTree::PostorderPrint()
{
    ofstream output("AVLPostorder.txt");

    if(output.is_open())
    {
        PostorderPrint(root, output);
        output.close();
    }
    else
    {
        cout<<"Couldn't open AVL Postorder output file"<<endl;
        exit(EXIT_FAILURE);
    }
}
