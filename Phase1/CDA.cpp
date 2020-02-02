#include <iostream>
using namespace std;


template <class elmtype>
class CDA {

private:
    int front;
    int end;
    int capacity;
    int length;
    bool order;
    elmtype *array;

public:
    CDA();
    CDA(int s);
    ~CDA();
    CDA(const CDA &cda);
    CDA& operator=(const CDA &src);
    elmtype& operator[](int i);
    void Printarray();
    void AddEnd(elmtype v);
    void AddFront(elmtype v);
    void DelEnd();
    void DelFront();
    int Length();
    int Capacity();
    void Clear();
    bool Ordered();
    int SetOrdered();
    void QuickSort();
    elmtype Select(int k);
    void InsertionSort();
    void CountingSort(int m);
    int Search(elmtype e);
};

template <class elmtype>
CDA<elmtype> :: CDA(){
    capacity = 1;
    length = 0;
    array = new elmtype[capacity];
    front = 0;
    end = 0;
    order = false;
}

template <class elmtype>
CDA<elmtype> :: CDA(int s) {
    capacity = s;
    length = s;
    array = new elmtype[capacity];
    front = 0;
    end = s-1;
    order = false;
}

template <class elmtype>
CDA<elmtype> :: ~CDA() {
     delete array;
     capacity = 0;
     front = 0;
     end = 0;
     length = 0;
     order = false;
}


//Copy constructor
template <class elmtype>
CDA<elmtype> :: CDA(const CDA &src){
    cout << "In copy Constructor\n";
    capacity = src.capacity;
    end = src.end;
    front = src.front;
    length = src.length;
    order = src.order;
    array = new elmtype[capacity];
    for(int i=0;i<length;i++) {
        array[(front+i)%capacity] = src.array[(front+i)%capacity];
    }
}

//Copy assignment operator
template <class elmtype>
CDA<elmtype>& CDA<elmtype> :: operator=(const CDA<elmtype> &src) {
    cout << "In copy assignment operator\n";
    if (this != &src) {
        capacity = src.capacity;
        end = src.end;
        length = src.length;
        order = src.order;
        array = new elmtype[capacity];
        for(int i=0;i<length;i++) {
            array[(front+i)%capacity] = src.array[(front+i)%capacity];
        }
    }
    return *this;
}

template <class elmtype>
elmtype& CDA<elmtype> :: operator[](int i) {
    if(length == 0) {
        cout << "The array is empty.\n";
        exit(0);
    }
    if(i>=length) {
        exit(0);
    }
    return array[(front + i)%capacity];

    
}

template <class elmtype>
void CDA<elmtype> :: Printarray() {
    cout << "Capacity: " << capacity << endl;
    cout << "Length: " << length << endl;
    cout << "Front: " << front << endl;
    cout << "End: " << end << endl;
    cout << "Array\n";
    for (int i=0; i<length;i++){
            cout << array[(front + i)%capacity] << " ";
        }
    cout << endl << endl;
}

template <class elmtype>
void CDA<elmtype> :: AddEnd(elmtype v) {

    if (length == capacity){ // Out of space
        capacity = 2 * capacity;
        //cout << "Doubling to: " << capacity << endl;
        elmtype *temp = new elmtype[capacity];
        for (int i=0; i<length;i++){
            temp[i] = array[(front + i)%length];
        }
        delete array;
        array = new elmtype[capacity];
        for(int i=0;i<length;i++){
            array[i] = temp[i];
        }
        free(temp);
        front = 0;
        end = length-1;
    }

    if (length == 0) { //no element
        array[front] = v;
        length++;
        order = true;
    }
    else {
        if(array[end] > v){
            order = false;
        }
        else {
            order = true;
        }
        array[(end + 1)%capacity] = v;
        end = (end+1)%capacity;
        length++;
    }

    
}

template <class elmtype>
void CDA<elmtype> :: AddFront(elmtype v) {
    if (length == capacity){ // Out of space
        capacity = 2 * capacity;
        //cout << "Doubling to: " << capacity << endl;
        elmtype *temp = new elmtype[capacity];
        for (int i=0; i<length;i++){
            temp[i] = array[(front + i)%length];
        }
        free (array);
        array = new elmtype[capacity];
        for(int i=0;i<length;i++){
            array[i] = temp[i];
        }
        free(temp);
        front = 0;
        end = length-1;
    }

    if (length == 0) { //no element
        array[front] = v;
        length++;
        order = true;
    }
    else {
        if(array[front] < v) {
            order = false;
        }
        else {
            order = true;
        }

        if (front == 0) {
            front = capacity -1;
            array[front] = v;
            length++;
        }
        else {
            front--;
            array[front] = v;
            length++;
        }
    }
}

template <class elmtype>
void CDA <elmtype> :: DelEnd(){
    if(length == 0) {
        //cout << "The array is empty\n";
        front = 0;
        end = 0;
    }
    else {
        if(end == 0) {
            end = capacity - 1;
            length--;
        }
        else {
            end--;
            length--;
        }
    
        if(length <= capacity * 0.25){
            capacity = capacity/2;
            //cout << "Reducing to : " << capacity << endl;
            elmtype *temp = new elmtype[capacity];
            for (int i=0; i<length;i++){
                temp[i] = array[(front + i)%(2*capacity)];
            }
            free(array);
            array = new elmtype[capacity];
            for(int i=0;i<length;i++){
                array[i] = temp[i];
            }
            front = 0;
            end = length-1;
        }
        if(length == 0) {
            end = 0;
            front =0;
        }
    }
        
}

template <class elmtype>
void CDA <elmtype> :: DelFront() {
    if (length == 0){
        cout << "The array is empty\n";
        front = 0;
        end = 0;
    }
    else {
        front = (front + 1) % capacity;
        length--;

        if(length <= capacity * 0.25){
            capacity = capacity/2;
            //cout << "Reducing to : " << capacity << endl;
            elmtype *temp = new elmtype[capacity];
            for (int i=0; i<length;i++){
                temp[i] = array[(front + i)%(2*capacity)];
            }
            free(array);
            array = new elmtype[capacity];
            for(int i=0;i<length;i++){
                array[i] = temp[i];
            }
            front = 0;
            end = length-1;
        }
        if (length == 0) {
            front = 0;
            end = 0;
        }
    }
}

template <class elmtype>
int CDA <elmtype> :: Length() {
    return length;
}

template <class elmtype>
int CDA <elmtype> :: Capacity() {
    return capacity;
}

template <class elmtype>
void CDA <elmtype> :: Clear(){
    capacity = 1;
    length = 0;
    order = false;
    front = 0;
    end = 0;
    free(array);
    array = new elmtype[1];

}

template <class elmtype> 
bool CDA <elmtype> :: Ordered(){
    return order;
}

template <class elmtype>
int CDA <elmtype> :: SetOrdered() {
    if (length == 0) {
        cout << "The array is empty\n";
        order = false;
        return -1;
    }
    order = true;
    for(int i=0;i<length-1;i++) {
        if(array[(front + i) % capacity] > array[(front + i + 1)%capacity]){
            order = false;
        }
    }

    if (order == false){
        return -1;
    }
    else {
        return 1;
    }
}

template <class elmtype>
elmtype partition(elmtype *arr, int l, int r) 
{ 
    elmtype x = arr[r];
    int i = l; 
    for (int j = l; j <= r - 1; j++) { 
        if (arr[j] <= x) { 
            swap(arr[i], arr[j]); 
            i++; 
        } 
    } 
    swap(arr[i], arr[r]); 
    return i; 
}


template <class elmtype>
elmtype kthSmallest(elmtype *arr, int l, int r, int k) 
{ 

    if (k > 0 && k <= r - l + 1) { 
        int index = partition(arr, l, r); 
        if (index - l == k - 1) 
            return arr[index]; 
  
        if (index - l > k - 1)  
            return kthSmallest(arr, l, index - 1, k); 
  
        return kthSmallest(arr, index + 1, r,  
                            k - index + l - 1); 
    } 
  
    // If k is more than number of  
    // elements in array 
    return INT_MAX; 
} 

template <class elmtype>
void  insertionsort(elmtype *array, int left, int right){
    if(right <= left) {
        return;
    }

    for(int i=left; i <= right; i++)
    {
        elmtype key = array[i];
        int j = i - 1;
        while(j >= 0 && key < array[j])
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

template <class elmtype>
void quicksort(elmtype array[], int left, int right){
    if(right <= left) {
        return;
    }
    int l = left;
    int r = right;
    int median = (left+right)/2;

    elmtype x = array[left];
    elmtype y = array[median];
    elmtype z = array[right];
    elmtype pivot = (x+y+z) - (max(max(x,y),z)+min(min(x,y),z));

    while(l < r) {
        while(array[l] < pivot) {
            l++;
            if(l == r) {
                break;
            }
        }

        while(array[r] > pivot) {
            r--;
            if(r == l) {
                break;
            }
        }

        swap(array[l],array[r]);
    }

    if(((r-1) - left) >= 10) {
        quicksort(array,left,r-1);
    }
    else {
        insertionsort(array,left,r-1);
    }
    if((right-(l+1)) >= 10) {
        quicksort(array,l+1,right);
    }
    else {
        insertionsort(array,l+1,right);
    }

}

template  <class elmtype>
void CDA <elmtype> :: QuickSort() {
    elmtype *temp = new elmtype[length];
    for(int i=0;i<length;i++) {
        temp[i] = array[(front+i)%capacity];
    }
    quicksort(temp,0,length-1);
    for(int i=0;i<length;i++) {
        array[(front+i)%capacity] = temp[i];
    }
    free(temp);
    order = true;

}

template <class elmtype>
elmtype CDA <elmtype> :: Select(int k){
    if(order){
        return array[(front + k-1)%capacity];
    }
    else {
        elmtype *temp = new elmtype[length];
        for(int i=0;i<length;i++) {
            temp[i] = array[(front+i)%capacity];
        }
        elmtype index = kthSmallest(temp,0,length-1,k);
        free(temp);
        return index;
    }
}

template <class elmtype>
void CDA <elmtype> :: InsertionSort() {
    for(int i=1;i<length;i++) {
        for(int j=i-1;j>=0 && array[(front+j+1)%capacity] < array[(front+j)%capacity];j--){
            elmtype temp = array[(front+j)%capacity];
            array[(front+j)%capacity] = array[(front+j+1)%capacity];
            array[(front+j+1)%capacity] = temp;
        }
    }
    order = true;
}

template <class elmtype> 
elmtype getMax(elmtype *array, int size) {
   elmtype max = array[1];
   for(int i = 2; i<=size; i++) {
      if(array[i] > max)
         max = array[i];
   }
   return max; //the max element from the array
}

template <class elmtype>
void countSort(elmtype *array, int size){
    int output[size+1];
   elmtype max = getMax(array, size);
   int count[max+1];     //create count array (max+1 number of elements)
   for(int i = 0; i<=max; i++)
      count[i] = 0;     //initialize count array to all zero
   for(int i = 1; i <=size; i++)
      count[array[i]]++;     //increase number count in count array.
   for(int i = 1; i<=max; i++)
      count[i] += count[i-1];     //find cumulative frequency
   for(int i = size; i>=1; i--) {
      output[count[array[i]]] = array[i];
      count[array[i]] -= 1; //decrease count for same numbers
   }
   for(int i = 1; i<=size; i++) {
      array[i] = output[i]; //store output array to main array
   }
}

template <class elmtype>
void CDA <elmtype> :: CountingSort(int m){
    elmtype *temp = new elmtype[length];
    for(int i=0;i<length;i++) {
        temp[i] = array[(front+i)%capacity];
    }
    countSort(array,m);
    for(int i=0;i<length;i++) {
        array[(front+i)%capacity] = temp[i];
    }
    free(temp);
    order = true;

}

template <class elmtype>
int binarySearch(elmtype *array, elmtype key, int length) {
    int mid = 0;
    int front = 0;
    int back = length - 1;
    while(front <= back) {
        mid = (front + back)/2;
        if(array[mid] == key) {
            return mid;
        }
        else if (array[mid]< key) {
            front = mid + 1;
        }
        else {
            back = mid - 1;
        }

    }
    return -1;
}

template <class elmtype> 
int CDA <elmtype> :: Search (elmtype e){
    if(order) {
        elmtype *temp = new elmtype[length];
        for(int i=0;i<length;i++) {
            temp[i] = array[(front+i)%capacity];
        }
        int index = binarySearch(temp, e, length);
        free(temp);
        return index+1;
    }
    else {
        for(int i=0;i<length;i++) {
            if(array[(front+i)%capacity] == e) {
                return i;
            }
        }
        return -1;
    }
}