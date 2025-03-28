#include "OrderedArray.h"

OrderedArray::OrderedArray()
{
    size = 100000000;
    counter = 0;
    sorted = false;
    OArray = new(std::nothrow) OrderedObj*[size]; //array of pointers that point to OrderedObj
    for (int i=0; i<size; i++)
    {
        OArray[i]=nullptr;      //initialize every pointer with null pointer
    }
    //ctor
}

OrderedArray::~OrderedArray()
{
    for (int i=0; i<counter; i++)
    {
        if(OArray[i]!= nullptr) //Delete the contents of every pointer that is not NULL
            delete OArray[i];
    }
    delete[] OArray;
    //dtor
}

void OrderedArray::Insert(string key) //Follows the same practice as Unordered Array
{
    bool exists=false;
    int i = 0;
    while(i<counter && !exists)
    {
        if(key == OArray[i]->word)
        {
            OArray[i]->occurances++;
            exists = true;
        }
        i++;
    }
    if(!exists)
    {
        if(counter < size)
        {
            OArray[counter] = new OrderedObj(key);
            counter++;
        }
        else
        {
            return; //no room in array
        }

    }
    //The above code is used if you are going to use the QuickSort after completing inserting.
}

bool OrderedArray::Search(string key) //Uses binary search.
{
    if(sorted) //Checks if array is sorted. Otherwise binary search is useless
    {
        int left = 0;
        int right = counter-1;
        while (right >= left)
        {
            int middle = (left+right)/2;
            if(key == OArray[middle]->word)
            {
                return true;
            }
            if(key > OArray[middle]->word )  //Objects that start with A are at the top
            {
                right = middle-1;
            }
            else                            //Objects that start with Z are at the bottom
            {
                left = middle+1;
            }
        }
        return false;
    }
    else
    {
        QuickSort(0,counter-1);
        sorted = true;
        return Search(key);
    }
}

bool OrderedArray::Delete(string key)
{
    if(sorted)
    {
        int pos = PosSearch(key);
        if(pos == -1)
        {
            return false;
        }
        else
        {
            int i = pos;
            while (i<counter-1)
            {
                *OArray[i] = *OArray[i+1]; //Pushes every element under the one being deleted one index above.
                i++;
            }
            delete OArray[i]; //then deletes the last one because it is an extra copy of OArray[i-1]
            counter--;
            return true;
        }
    }
    else
    {
        QuickSort(0,counter-1);
        sorted = true;
        return Delete(key);
    }
}

bool OrderedArray::PrintSearch(string key, ofstream &output) //Same practice as UnorderedArray
{
    if (counter==0)
    {
        cout<<"Ordered Array is Empty!"<<endl;
        return false;
    }
    if(sorted)
    {
        int pos = PosSearch(key); //Binary search to find index
        if(pos == -1)
        {
            return false;
        }
        else
        {
            output<<OArray[pos]->word<<"["<<OArray[pos]->occurances<<"]"<<endl;
            return true;
        }

    }
    else
    {
        QuickSort(0,counter-1);
        sorted = true;
        return PrintSearch(key, output);
    }
}

//QuickSort
void OrderedArray::QuickSort()
{
    if(!sorted)
    {
        QuickSort(0,counter-1); //Calls the private definition of Quicksort and gives the start and end of the array as parameters
        sorted = true;
    }
    else
    {
        cout<<"Already sorted"<<endl;
    }
}

int OrderedArray::PosSearch(string key) //Same as Search but returns the object's index instead of boolean
{
    if(sorted)
    {
        int left = 0;
        int right = counter-1;
        while (right >= left)
        {
            int middle = (left+right)/2;
            if(key == OArray[middle]->word)
            {
                return middle;
            }
            if(key > OArray[middle]->word )
            {
                right = middle-1;
            }
            else
            {
                left = middle+1;
            }
        }
        return -1; //returns -1 if not found
    }
    else
    {
        QuickSort(0,counter-1);
        sorted = true;
        return PosSearch(key);
    }
}

void OrderedArray::swap(int indexA,int indexB)
{
    OrderedObj temp = *OArray[indexA];
    *OArray[indexA] = *OArray[indexB];
    *OArray[indexB] = temp;
}

int OrderedArray::partition(int left, int right, int pivotIndex)
{
    OrderedObj pivot = *OArray[pivotIndex];
    swap(pivotIndex,right);
    int storeIndex = left;
    for (int i=left;i<right;i++)
    {
        if (OArray[i]->word >= pivot.word)
        {
            swap(i,storeIndex);
            storeIndex++;
        }
    }
    swap(storeIndex,right);
    return storeIndex;
}

void OrderedArray::QuickSort(int left,int right) //Quicksorts the objects between left and right index by calling upon partition and recursively itself again
{
    if(left<right)
    {
        int pivotIndex = left + (right - left)/2;
        pivotIndex = partition(left,right,pivotIndex); //pivotInxdex is used to divide the array for the next calls of Quicksort
        QuickSort(left,pivotIndex-1);
        QuickSort(pivotIndex+1,right);
    }
}
