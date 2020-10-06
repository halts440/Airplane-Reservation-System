#include "Vector.h"

// Constructor
template <typename T>
Vector<T>::Vector() {	        //default constructor
    ptr = NULL;
    size = 0;
    index = -1;
}

// Parametrized Constructor
template <typename T>
Vector<T>::Vector(int n) {				    //parametrized constructor
    ptr = new T[n];			    //allocating memory for n values
    size = n;				    //adjusting the size
    index = -1;				    //initially setting the index to -1
}


// Is Empty Function
template <typename T>
bool Vector<T>::isEmpty() {
    if (index <= -1)	// returns true if vector is empty
        return true;
    else
        return false;
}

// Clear Function
template <typename T>
void Vector<T>::clear() {		// clears the vector 
    index = -1;
}

// Push Function
template <typename T>
void Vector<T>::push(T data) {
    index++;
    if (ptr == NULL) {			//if ptr is null allocate memory to 2 cells and insert the data at the required index
        ptr = new T[2];
        ptr[index] = data;
        size = 2;
    }
    else {
        if (index >= size) {						//if the array is already filled
            T* temp = new T[size * 2];				//make a new array twice in size than the original
            for (int i = 0; i < size; i++)			//copy all elemets of previous array
                temp[i] = ptr[i];
            delete[]ptr;							//delete previous array to save memory
            size *= 2;								//adjust the size
            ptr = new T[size];						//now again allocate memory to the original pointer
            for (int i = 0; i < size; i++)			//copy all elements which were saved as a backup
                ptr[i] = temp[i];
            //	delete[]temp;
        }
        ptr[index] = data;							//insert data
    }
}

// Get Size Function
template <typename T>
int Vector<T>::getSize() {
    return index + 1;   	//returning no of elements
    //return size;
}

// Get No Of Elements Function
template <typename T>
int Vector<T>::getNoOfElements() {
    return index + 1;	    //returning no of elements
}

// Display Function
template <typename T>
void Vector<T>::display() {
    for (int i = 0; i <= index; i++)		//displaying contents of array
        cout << ptr[i] << "\t";
    cout << endl;
}

// Get At Function
template <typename T>
T Vector<T>::getAt(int ind) {
    return ptr[ind];		//getting content of specific index
}

// [ ] Operator Overloaded
template <typename T>
T& Vector<T>::operator[](int ind) {	//overloaded the []operator
    return ptr[ind];
}

// Destructor
template <typename T>
Vector<T>::~Vector() {
    for (int i = size - 1; i = 0; i--)
        delete (ptr + i);					//deallocating memory in destructor
}