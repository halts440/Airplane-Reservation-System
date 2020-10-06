#ifndef ADJLIST_H
#define ADJLIST_H

#include<iostream>
#include "Node.h"
using namespace std;

class AdjList {
public:
    // Member Variables
	Node* head;			

    // Member Functions						
	AdjList();													
	void insert(Node* newDataItem);
	void display();
	bool search(string value);													
};

#endif