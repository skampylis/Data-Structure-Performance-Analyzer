#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include "UnorderedArray.h"
#include "OrderedArray.h"
#include "BinarySearchTree.h"
#include "AVLTree.h"
#include "HashTable.h"

using std::string;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

#define SIZE 10000 //max number of random words
#define PROBABILITY 25 //a word has a probability of being inserted in the randWords array of 1/PROBABILITY
#define TIME_UNIT microseconds //nanoseconds / microseconds / milliseconds / seconds
#define TIME_UNITS "microseconds" //for the file print
#define INPUT_FILE "small-file.txt" //Change for different text file

void RemoveSpecialCharacters(string &word)
{
    int i = 0;

    while(word[i] != '\0')
    {
        if(!isalpha(word[i]))
            word.erase(i, 1);
        else
        {
            word[i] = tolower(word[i]);
            i++;
        }
    }
}

int main()
{
    UnorderedArray U;
    OrderedArray O;
    BinarySearchTree B;
    AVLTree A;
    HashTable H;

    srand(time(nullptr));

    string* randWords = new(std::nothrow) string[SIZE];
    int counter = 0; //counter of random words

    if(!randWords)
    {
        cout<<"Random words array memory allocation failed"<<endl;
        exit(EXIT_FAILURE);
    }

    ifstream text(INPUT_FILE);

    if(text.is_open())
    {
        string line, word;
        int pos;

        while(getline(text, line))
        {
            while(line != "")
            {
                pos = line.find(' ');
                word = line.substr(0, pos);

                if(pos < 0)               //if npos(unsigned long long) was assigned to pos, then due to the overflow pos would be -1
                    line = "";            //so we just check if pos is < 0
                else
                    line.erase(0, pos + 1);

                RemoveSpecialCharacters(word);

                if(word != "")
                {
                    U.Insert(word);
                    O.Insert(word);
                    B.Insert(word);
                    A.Insert(word);
                    H.Insert(word);

                    if(counter < SIZE && rand() % PROBABILITY == 1)
                        randWords[counter++] = word;
                }
            }
        }

        text.close();
    }
    else
    {
        cout<<"Can't open input file"<<endl;
        exit(EXIT_FAILURE);
    }


    auto start0 = std::chrono::steady_clock::now();
    for(int i = 0;i < counter;i++)
        U.Search(randWords[i]);
    auto finish0 = std::chrono::steady_clock::now();

    O.QuickSort();
    auto start1 = std::chrono::steady_clock::now();
    for(int i = 0;i < counter;i++)
        O.Search(randWords[i]);
    auto finish1 = std::chrono::steady_clock::now();

    auto start2 = std::chrono::steady_clock::now();
    for(int i = 0;i < counter;i++)
        B.Search(randWords[i]);
    auto finish2 = std::chrono::steady_clock::now();

    auto start3 = std::chrono::steady_clock::now();
    for(int i = 0;i < counter;i++)
        A.Search(randWords[i]);
    auto finish3 = std::chrono::steady_clock::now();

    auto start4 = std::chrono::steady_clock::now();
    for(int i = 0;i < counter;i++)
        H.Search(randWords[i]);
    auto finish4 = std::chrono::steady_clock::now();



    ofstream output("Results.txt");

    if(!output.is_open())
    {
        cout<<"Could't open output file"<<endl;
        exit(EXIT_FAILURE);
    }

    output<<"Unordered Array: "<<std::chrono::duration_cast<std::chrono::TIME_UNIT>(finish0 - start0).count()<<" "<<TIME_UNITS<<endl;
    output<<"Ordered Array: "<<std::chrono::duration_cast<std::chrono::TIME_UNIT>(finish1 - start1).count()<<" "<<TIME_UNITS<<endl;
    output<<"Binary Search Tree: "<<std::chrono::duration_cast<std::chrono::TIME_UNIT>(finish2 - start2).count()<<" "<<TIME_UNITS<<endl;
    output<<"AVL Tree: "<<std::chrono::duration_cast<std::chrono::TIME_UNIT>(finish3 - start3).count()<<" "<<TIME_UNITS<<endl;
    output<<"Hash Table: "<<std::chrono::duration_cast<std::chrono::TIME_UNIT>(finish4 - start4).count()<<" "<<TIME_UNITS<<endl;
    output<<"Number of words searched: "<<counter<<endl;

    output.close();

    ofstream UArrayOutput("UArray.txt");
    ofstream OArrayOutput("OArray.txt");
    ofstream BSTOutput("BST.txt");
    ofstream AVLOutput("AVL.txt");
    ofstream HashTableOutput("HashTable.txt");

    if(!UArrayOutput.is_open() || !OArrayOutput.is_open() || !BSTOutput.is_open() || !AVLOutput.is_open() || !HashTableOutput.is_open())
    {
        cout<<"Couldn't open structures output files";
        exit(EXIT_FAILURE);
    }

    for(int i = 0;i < counter;i++)
    {
        U.PrintSearch(randWords[i], UArrayOutput);
        O.PrintSearch(randWords[i], OArrayOutput);
        B.PrintSearch(randWords[i], BSTOutput);
        A.PrintSearch(randWords[i], AVLOutput);
        H.PrintSearch(randWords[i], HashTableOutput);
    }

    UArrayOutput.close();
    OArrayOutput.close();
    BSTOutput.close();
    AVLOutput.close();
    HashTableOutput.close();

    delete [] randWords;

    return 0;
}
