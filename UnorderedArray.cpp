#include "UnorderedArray.h"


UnorderedArray::UnorderedArray()
{
    size = 100000000;
    counter = 0;
    UArray = new(std::nothrow) ArrayObj*[size];  //array of pointers that point to ArrayObj
    for (int i=0; i<size; i++)
    {
        UArray[i]=nullptr;      //initialize every pointer with null pointer
    }
    //ctor
}

UnorderedArray::~UnorderedArray()
{
    for (int i=0; i<counter; i++)
    {
        if(UArray[i]!= nullptr)  //Delete the contents of every pointer that is not NULL
            delete UArray[i];
    }
    delete[] UArray;
    //dtor
}

void UnorderedArray::Insert(string key)
{

    bool exists=false;
    int i = 0;

    //Serial Search to find if the word already exists
    while(i<counter && !exists)
    {
        if(key == UArray[i]->word)
        {
            UArray[i]->occurances++;
            exists = true;
        }
        i++;
    }
    if(!exists)
    {
        if(counter<size)
        {
            UArray[counter] = new ArrayObj(key); // Add new object at the last position
            counter++;
        }
        else
        {
            return;
        }
    }
}

bool UnorderedArray::Search(string key)
{
    //Serial Search
    int i = 0;
    while(i<counter)
    {
        if(key == UArray[i]->word)
        {
            return true;
        }
        i++;
    }
    return false;
}

bool UnorderedArray::Delete(string key)
{
    int i = 0;
    //Serial Search
    while(i<counter)
    {
        if(key == UArray[i]->word)
        {
            if(i == (counter-1))
            {
                delete UArray[i];
            }
            else
            {
                *UArray[i] = *UArray[counter-1]; //Replace the to be deleted object with the last object in the array and then delete the original copy
                delete UArray[counter-1];
                counter--;
            }
            return true;
        }
        i++;
    }
    return false;
}

bool UnorderedArray::PrintSearch(string key, ofstream &output)
{
    if (counter==0)
    {
        cout<<"Unordered Array is Empty!"<<endl;
        return false;
    }
    int i = 0;
    //Serial Search
    while(i<counter)
    {
        if(key == UArray[i]->word)
        {
            output<<UArray[i]->word<<"["<<UArray[i]->occurances<<"]"<<endl;
            return true;
        }
        i++;
    }
    return false;
}
