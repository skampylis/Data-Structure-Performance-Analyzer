#ifndef ORDEREDARRAY_H
#define ORDEREDARRAY_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::nothrow;

class OrderedObj
{
    public:
        OrderedObj() {}
        OrderedObj(string key) //OrderedObj Constructor
        {
            word = key;
            occurances = 1;
        }
        string word;
        int occurances;
};

class OrderedArray
{
    public:
        OrderedArray();
        ~OrderedArray();
        void Insert(string);
        bool Search(string);
        bool Delete(string);
        bool PrintSearch(string,ofstream&); //prints in a text file the word passed to it, if found
        void QuickSort(); //Quicksort algorithm to sort the array. Can be called by user

    private:
        OrderedObj **OArray; //Dynamic Array
        int counter;
        int size;
        bool sorted;
        int PosSearch(string); //Works the same way as Search but returns the object's index instead
        void QuickSort(int left,int right); //2nd Definition of QuickSort called privately by the program. It recursively sorts the array
        int partition (int left, int right, int pivotIndex); //Used by Quicksort. Sorts the elements between left and right index using a pivot
        void swap(int indexA,int indexB); //Swaps object in index A with object at index B
};

#endif // ORDEREDARRAY_H
