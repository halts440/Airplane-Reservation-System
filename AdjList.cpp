#include "AdjList.h"

// default constructor
AdjList::AdjList() {
    head = NULL;
}

// Insert Function
void AdjList::insert(Node* newDataItem) {				//prametrized constructor
    if (head == NULL) {						    //if head is null insert data at head
        head = newDataItem;
    }
    else {
        Node* temp = head;
        while (temp->Destination != NULL) {		//else keep on going till we reach to null
            temp = temp->Destination;
        }
        temp->Destination = newDataItem;		//now insert data at null
    }
}

// Display Function
void AdjList::display()  {							    //displaying contents of adjancy list
    Node* temp = head;
    while (temp != NULL) {
        cout << temp->Origin << "|" << temp->Travel_Time.time_to_str() << " ";
        temp = temp->Destination;
    }
    cout << endl;
}

// Search
bool AdjList::search(string value) {					//verify whether the value exits in list or not
    bool found = false;
    Node* temp = head;
    while (temp) {
        if (temp->Origin == value)
            found = true;
        temp = temp->Destination;
    }
    return found;
}