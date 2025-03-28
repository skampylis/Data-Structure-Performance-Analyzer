#ifndef UNORDEREDARRAY_H
#define UNORDEREDARRAY_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::nothrow;

class ArrayObj
{
    public:
        ArrayObj(){}
        ArrayObj(string key) //ArrayObj Constructor
        {
            word = key;
            occurances = 1;
        }
        string word;
        int occurances;
};

class UnorderedArray
{
    public:
        UnorderedArray();
        ~UnorderedArray();
        void Insert(string);
        bool Search(string);
        bool Delete(string);
        bool PrintSearch(string,ofstream&); //prints in a text file the word passed to it, if found

    private:
        ArrayObj **UArray; //Dynamic Array
        int counter;
        int size;
};

#endif // UNORDEREDARRAY_H
