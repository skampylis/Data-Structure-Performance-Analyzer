#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::nothrow;

class HashTableObject
{
    public:
        HashTableObject(){}             //constructor of HashTableObject
        string key;
        int occurrences;
};

class HashTable
{
    public:
        HashTable();
        ~HashTable();
        int Hash_function(string);
        void Insert(string);
        bool Search(string);
        bool PrintSearch(string, ofstream&);

    private:
        HashTableObject **Array;
        int counter;
        int size;
};

#endif // HASHTABLE_H
