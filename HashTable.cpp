#include "HashTable.h"

HashTable::HashTable()
{
    size = 100003;
    counter=0;
    Array=new HashTableObject*[size];  //array of pointers that point to HashTableObject
    for (int i=0;i<size;i++)
    {
        Array[i]=nullptr;              //initialize every pointer with null pointer
    }
}

HashTable::~HashTable()
{
    for (int i=0;i<size;i++)
    {
        if (Array[i]!=nullptr)
        {
            delete Array[i];
        }
    }

    delete [] Array;
}

int HashTable::Hash_function(string key)
{
    unsigned long long sum=0;
    for (int i=0;key[i] != '\0';i++)
    {
        sum=37*sum+(int)key[i];
    }
    return sum%size;
}

void HashTable::Insert(string key)
{
    if (counter==size)
    {
        cout<<"HashTable is full!"<<endl;
        return;
    }
    int i = 0;
    int h = Hash_function(key);
    int index=h;
    while (Array[index]!=nullptr)
    {
        if(Array[index]->key == key)
        {
            Array[index]->occurrences++;
            return;
        }
        index = (++i * h) % size;
    }
    Array[index]=new HashTableObject;
    Array[index]->key=key;
    Array[index]->occurrences = 1;
    counter++;
}

bool HashTable::Search(string key)
{
    if (counter==0)
    {
        cout<<"HashTable is Empty!"<<endl;
        return false;
    }
    int i = 0;
    int h = Hash_function(key);
    int index = h;
    while (Array[index]!=nullptr)
    {
        if(Array[index]->key == key)
            return true;

        index = (++i * h) % size;
    }
    return false;
}

bool HashTable::PrintSearch(string key, ofstream &output)
{
    if (counter==0)
    {
        cout<<"HashTable is Empty!"<<endl;
        return false;
    }
    int i;
    int h = Hash_function(key);
    int index = h;
    while (Array[index]!=nullptr)
    {
        if(Array[index]->key == key)
        {
            output<<Array[index]->key<<"["<<Array[index]->occurrences<<"]"<<endl;
            return true;
        }

        index = (++i * h) % size;
    }
    return false;
}
