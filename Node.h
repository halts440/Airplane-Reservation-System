#ifndef NODE_H
#define NODE_H

#include<iostream>
#include<string>
#include "Time.h"
#include "Date.h"
using namespace std;

class Node {								
public:
	// Data members
	string Origin;				//ciy of origin
	Node* Destination;			//a pointer pointing to the city of destination

	int TicketPrice;			// ticket Price for flight
	string Airline;				// name of Airline
	int Hotel_Charg;			// hotel charges of that country
	Date DateOfTravel;			// date of travel of flight
	Time FlyingTime;			// flying time of flight
	Time LandingTime;			// landing time of flight
	Time Travel_Time;			//	total time of the flight
	Time Transit_Time;			//  transit time between this flight and the next flight
	bool p_check;				// if path is valid p_check is true else false

    // Methods
	Node();
	void show_data();

};

#endif

