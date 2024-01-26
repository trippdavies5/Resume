#ifndef HEAP_H
#define HEAP_H
#include <iostream>
using namespace std;
#include "CircularDynamicArray.cpp"
template <typename keytype>

class Heap
{
private:
    CircularDynamicArray<keytype>* array;
    int size;
    //Makes an array into an array heap
    void heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < array->size && array->data[l] < array->data[i])
        {
            smallest = l;
        }
        if (r < array->size && array->data[r] < array->data[smallest])
        {
            smallest = r;
        }
        if (smallest != i)
        {
            swap(array->data[i], array->data[smallest]);
            heapify(smallest);
        }
    }

    void swap(keytype& one, keytype& two)
    {
        keytype temp = one;
        one = two;
        two = temp;
    }

    int parent(int i)
    {
        return (i - 1) / 2;
    }

    int left(int i)
    {
        return (2 * i + 1);
    }

    int right(int i)
    {
        return (2 * i + 2);
    }

public:
    //default constuctor
    Heap()
    {
        array = new CircularDynamicArray<keytype>();
        array->data = new keytype[2];
        size = 0;
    }
    //Array constructor 
    Heap(keytype k[], int s)
    {
        array = new CircularDynamicArray<keytype>(s);
        array->data = new keytype[s];
        size = s;

        for (int i = 0; i < s; i++) {
            array->data[i] = k[i];
        }

        for (int i = (s - 2) / 2; i >= 0; i--) {
            heapify(i);
        }

    }
    //delete heap
    ~Heap()
    {
        while (size > 0)
        {
            extractMin();
        }
    }
    //copy constructor
    Heap(const Heap<keytype>& copy)
    {
        size = copy.size;
        array = new CircularDynamicArray<keytype>(*(copy.array));
    }
    //Equal operator
    Heap& operator=(const Heap<keytype>& copy)
    {
        delete array;

        Heap<keytype> temp(copy);
        array = temp.array;
        temp.array = NULL;
        this->size = temp.size;
        temp.size = 0;
        return *this;
    }


    keytype peekKey()
    {
        return array->data[0];
    }
    
    keytype extractMin()
    {
        keytype minKey = array->data[0];
        array->data[0] = array->data[size - 1];
        array->delEnd();
        size--;
        heapify(0);
        
        return minKey;
    }

    void insert(keytype key) {
        array->rev = false;
        array->addEnd(key);
        size++;
        int i = size-1;

        while (i > 0 && array->data[(i - 1) / 2] > array->data[i]) {
            swap(array->data[i], array->data[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void printKey() {

        for (int i = 0; i < size; i++) {
            cout << array->data[i] << " ";
        }
        cout << endl;
    }
};



#endif