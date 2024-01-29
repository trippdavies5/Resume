#ifndef CIRCULARDYNAMICARRAY_H
#define CIRCULARDYNAMICARRAY_H
#include <iostream>
using namespace std;
template <typename elmtype>
class CircularDynamicArray {
// private:
public:
    int cap;  
    int size;      
    elmtype *data; 
    int head; 
    int tail; 
    bool rev;
    // bool sort = true;
    void twice() {
        int new_cap = cap * 2;
        elmtype* new_data = new elmtype[new_cap];
        int j = 0;
        for (int i = head; i < head + size; i++) {
            new_data[j++] = data[i % cap];
        }
        delete[] data;
        data = new_data;
        head = 0;
        tail = size-1;    
        cap = new_cap;
    }
    void half() {
        int new_cap = cap/2;
        elmtype* new_data = new elmtype[new_cap];
        int j = 0;
        for (int i = head; i < head + size; i++) {
            new_data[j++] = data[i % cap];
        }
        delete[] data;
        data = new_data;
        head = 0;
        tail = size-1;    
        cap = new_cap;
    }
    void mergeSort(elmtype array[], int const begin, int const end)
    {
        
        // if (sort)   {
        //     int top = head;
        //     elmtype* data2 = new elmtype[cap];
        //     for (int i = 0; i < size; i++)
        //     {
        //         data2[i] = data[top];
        //         if (top == cap)
        //         {
        //             top = 0;
        //         }
        //         else{
        //             top++;
        //         }
                
        //     }
        //     head = 0;
        //     tail = size-1;
        //     for (int i=0; i< size;i++) cout << data2[i] << " ";  cout << endl;
        //     for (int i=0; i< size;i++) cout << data[i] << " ";  cout << endl;
        //     sort = false;
        // }
        // int begin = head;
        // int end = tail;
        
        
        if (begin >= end){
        return; 
        }
        
        int mid = begin + (end - begin) / 2;
        
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);

        
        merge(array, begin, mid, end);
        data = array;
        // sort = true;
    }
    
    void merge(elmtype array[], int const left, int const mid, int const right)
    {
        int const subArrayOne = mid - left + 1;
        int const subArrayTwo = right - mid;
    
        
        elmtype *leftArray = new elmtype[subArrayOne];
        elmtype *rightArray = new elmtype[subArrayTwo];
    
        for (int i = 0; i < subArrayOne; i++){
            leftArray[i] = array[left + i];
        }
        for (int j = 0; j < subArrayTwo; j++){
            rightArray[j] = array[mid + 1 + j];
        }
        int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0; 
        int indexOfMergedArray = left; 
    
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
        

        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
       

        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }
    void revmergeSort(elmtype array[], int const begin, int const end)
    {
        
        // if (sort)   {
        //     int top = head;
        //     elmtype* data2 = new elmtype[cap];
        //     for (int i = 0; i < size; i++)
        //     {
        //         data2[i] = data[top];
        //         if (top == cap)
        //         {
        //             top = 0;
        //         }
        //         else{
        //             top++;
        //         }
                
        //     }
        //     head = 0;
        //     tail = size-1;
        //     for (int i=0; i< size;i++) cout << data2[i] << " ";  cout << endl;
        //     for (int i=0; i< size;i++) cout << data[i] << " ";  cout << endl;
        //     sort = false;
        // }
        // int begin = head;
        // int end = tail;
        
        
        if (begin >= end){
        return; 
        }
        
        int mid = begin + (end - begin) / 2;
        
        revmergeSort(array, begin, mid);
        revmergeSort(array, mid + 1, end);

        
        revmerge(array, begin, mid, end);
        data = array;
        // sort = true;
    }
    
    void revmerge(elmtype array[], int const left, int const mid, int const right)
    {
        int const subArrayOne = mid - left + 1;
        int const subArrayTwo = right - mid;
    
        
        elmtype *leftArray = new elmtype[subArrayOne];
        elmtype *rightArray = new elmtype[subArrayTwo];
    
        for (int i = 0; i < subArrayOne; i++){
            leftArray[i] = array[left + i];
        }
        for (int j = 0; j < subArrayTwo; j++){
            rightArray[j] = array[mid + 1 + j];
        }
        int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0; 
        int indexOfMergedArray = left; 
    
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] >= rightArray[indexOfSubArrayTwo]) {
                array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
        

        while (indexOfSubArrayOne < subArrayOne) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }
       

        while (indexOfSubArrayTwo < subArrayTwo) {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
        delete[] leftArray;
        delete[] rightArray;
    }

    void swap(int i, int j)
    {
        elmtype temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
    
    int partition(int l, int r)
    {
        elmtype x = data[get(r)], i = l;
        for (int j = l; j <= r - 1; j++) {
            if (data[get(j)] <= x) {
                swap(get(i), get(j));
                i++;
            }
        }
            swap(get(i), get(r));
            return i;
    }
    int get(int l)
    {
        if (rev) {  
            return (tail - l + cap) % cap;
        }
        else{
            return (head + l + cap) % cap;
        }
    }
    elmtype kthSmallest(int l, int r, int k)
    {
    

    if (k > 0 && k <= r - l + 1) {
  
        
        int index = partition(l, r);
  
        
        if (index - l == k - 1)
        {
            // if (rev)
            // {
            //     // cout << index << endl;
            //     return data[size - index];
            // }else{
                // cout << index << endl;
            return data[get(index)];
            // }
        }
        
        if (index - l > k - 1) 
        {
            return kthSmallest(l, index - 1, k);
        }

        return kthSmallest(index + 1, r, 
                            k - index + l - 1);
    }
  
    
    return data[head];
    }

// public:
    
    CircularDynamicArray() {
        cap = 2;
        size = 0;
        head = 0;
        tail = 1;
        data = new elmtype[cap];
        rev = false;
    }

    CircularDynamicArray(int s){
        cap = s;
        size = s;
        head = 0;
        tail = s-1;
        data = new elmtype[s];
        rev = false;
    }

    CircularDynamicArray(const CircularDynamicArray<elmtype> &copy)
    {
        cap = copy.cap;
        size = copy.size;
        head = copy.head;
        tail  = copy.tail;
        data = new elmtype[cap];
        rev = copy.rev;
        for (int i = 0;i < cap;i++)
        {   
            data[i] = copy.data[i];
        }
    }

    ~CircularDynamicArray() {
        delete[] data;
    }
    

    elmtype &operator[](int i) {
        // if (capacity < i) {
        //     cout << "index is out of bounds";
        //     return data[i];
        // }
        // cout << "index is out of bounds";
        // return data[i];
        // data[(head + i) % capacity]
        if (i > size-1 || 0 > i)
        {
            cout << "Out of bounds" << endl;;
            return data[i];
        }
        else{
            if (rev) {  
                // return data[(tail) - ((head + i) % cap)];
                return data[(tail - i + cap) % cap];
            }
            else{
                return data[(head + i + cap) % cap];
            }
        }
    }
    void operator=(const CircularDynamicArray<elmtype> &copy)
    {
        delete[] data;
        cap = copy.cap;
        size = copy.size;
        head = copy.head;
        tail  = copy.tail;
        data = new elmtype[cap];
        rev = copy.rev;
        for (int i = 0;i < cap;i++)
        {   
            data[i] = copy.data[i];
        }
    }

    
    void head2(){
        head = head+1;
    }
    void delEnd() {
        if (rev){
            if (size == cap/4)
            {
                half();
            }
            if (size > 0) {
            head = (head + 1) % cap;
            size--;
            // if (size > 0) {
            //     tail = (tail - 1 + cap) % cap;
            //     size--;
            // }
            }
        }else{
            // if (size > 0) {
            // head = (head + 1) % cap;
            // size--;
            // }
            if (size == cap/4)
            {
                half();
            }
            if (size > 0) {
                tail = (tail - 1) % cap;
                size--;
            }
        }
    }

    void addEnd(elmtype v) {
        if (rev){
            if (size == cap) {
                twice();
            }
            head = (head - 1 + cap) % cap;
            data[head] = v;
            size++;
        }
        else{
            if (size == cap) {
                twice();
            }
            
            tail = (tail + 1) % cap;
            data[tail] = v;
            size++;
            // tail = (tail + 1) % cap;
            // data[tail] = v;
            
        }
    }

    void addFront(elmtype v) {
        if (rev)
        {
            if (size == cap) {
            twice();
            }
            tail = (tail + 1) % cap;
            data[tail] = v;
            size++;
        }
        else{ 
            if (size == cap) {
                twice();
            }
            head = (head - 1 + cap) % cap;
            data[head] = v;
            size++;
        }
    }

    void delFront() {
        if (rev){
            if (size == cap/4)
            {
                half();
            }
            if (size > 0) {
                tail = (tail - 1 + cap) % cap;
                size--;
            }
            // if (size > 0) {
            //     head = (head + 1) % cap;
            //     size--;
            // }
        }else{
            if (size == cap/4)
            {
                half();
            }
            if (size > 0) {
                head = (head + 1) % cap;
                size--;
            }
            // if (size > 0) {
            //     tail = (tail - 1 + cap) % cap;
            //     size--;
            // }
        }
    }

    int length() {
        return size;
    }

    int capacity() {
        return cap;
    }

    
    void hts(){
        cout << head << " " << tail << " " << size << endl;; 
    }

    void clear() {
        delete[] data;
        cap = 2;
        size = 0;
        head = 0;
        tail = 0;
        data = new elmtype[cap];
    }

    // void printArray() {
    //     int next = head;
    //     for (int i = 0; i < size; i++)
    //     {
    //         cout << data[next] << " ";
    //         if (next == cap)
    //         {
    //         next = 0;
    //         }
    //     }
        
    // }

    elmtype QuickSelect(int k){
        // elmtype* data2 = new elmtype[cap];
        // for (int i = 0;i < size;i++)
        // {
        //     data
        // }
        //data2 = data;
        // O(cap) = O(size)
        // memcpy(data2,data,cap*sizeof(elmtype));
        if (k>=size)
        {
            // delete[] data2;
            return -1;
        }else
        {
            elmtype x = kthSmallest(0, size - 1, k);
            // delete[] data2;
            
            return x;
        }
    }

    
    void stableSort(){
        elmtype* data2 = new elmtype[cap];
        int top = head;
        for (int i = 0; i < size; i++)
        {
            data2[i] = data[top];
            if (top == cap)
            {
                top = 0;
                i = i-1;
            }
            else{
                top++;
            }
            
        }
        head = 0;
        tail = size-1;
        if (rev)
        {
            revmergeSort(data2, head, tail); 
        }else{
            mergeSort(data2, head, tail);
        }
        
        data = data2;
        
    }

    int linearSearch(elmtype e){
        int top = head;
        for (int i = 0; i < size; i++)
        {
            if (e == data[top])
            {
                if (rev)
                {
                    return (size-1-i);
                }else
                {
                return i;
                }
            }
            else if (top == cap)
            {
                top = 0;
                i = i -1;
            }
            else{
                top++;
            }
        }
        return -1;
    }

    int binSearch(elmtype e) {
        // int l = 0;
        // int r = size - 1;
        // while (l <= r) {
        //     int m = l + (r - l) / 2;
        //     if (data[m] == e)
        //         return m;
        //     if (data[m] < e)
        //         l = m + 1;
        //     else
        //         r = m - 1;
        // }
        // return -1;
        
        int l = 0;
        int r = size - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (data[get(m)] == e){
                // if (rev){
                //     return get(m);
                // }else{
                    // cout << m << endl;
                    return m;
                // }
            }
            if ((rev? data[get(m)] > e : data[get(m)] < e)){
            // if (data[get(m)] < e){
                l = m + 1;
            }
            else{
                r = m - 1;
            }
        }
        return -1;
    }


    void reverse()
    {
        if (rev)
        {
            rev = false;
        }
        else{
            rev = true;
        }
    }

    
};
    
#endif
