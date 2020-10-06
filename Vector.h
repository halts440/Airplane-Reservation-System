#ifndef VECTOR_H
#define VECTOR_H

#include<iostream>
using namespace std;

template <typename T>
class Vector {
	T* ptr;		    //array of T type
	int size;	    //variable to store size of array
	int index;	    //variable to store current index of array

public:
	Vector();																			
	Vector(int n);					
	bool isEmpty();
	void clear();										
	void push(T data);
	int getSize();
	int getNoOfElements();
	void display();
	T getAt(int ind);
	T& operator[](int ind);				
	~Vector();
};

#endif
