#ifndef ARS_H
#define ARS_H

#include<iostream>
#include<string>
#include<sstream>
#include "Data.h"
#include "Vector.h"
#include "Vector.cpp"
#include "Node.h"
#include "AdjList.h"
using namespace std;

class ARS {					//main calss of air reservation system
private:
	AdjList* array;			//array of adjoincy list
	int num_vertex;		    //variable to store num of vertices
	int NoOfCities;		    //variable to store no of cities
	int number;

	string* cities;			    //array of city names
	string* dates;			    //array of dates
	string* airlines;		    //array of airlines
	int* hotel_charges;		    //array of hotel charges

	int num_dates;			    //total no of dates available
	int num_airlines;		    //total no of airlines

    Vector<Vector<Node>> Get_Paths(string source_, string destination_);
	void Total_Time_And_Charges(Vector<Vector<Node>>& paths);
	void Print_Paths(Vector<Vector<Node>>& paths);
	void All_Paths(Node* u, Node* d, bool visited[], Node path[], int& path_index, Vector<Vector<Node>>& paths);
    void Check_Transit_Location(Vector<Vector<Node>>& paths, string transit_loc);
	void Check_Direct_Flights(Vector<Vector<Node>>& paths);
	void Check_Airline(Vector<Vector<Node>>& paths, string airline);
	int Num_Paths(Vector<Vector<Node>>& paths);
	void Check_Transit_Hours(Vector<Vector<Node>>& paths, string transit_loc, string min, string max);
	void Check_Date(Vector<Vector<Node>>& paths, string date);
	void Sort_Paths(Vector<Vector<Node>>& paths, int cost_or_travel);
	bool search_string(Vector<string>& t, string str);
	int find_value(string arr[], string value, int size);		


public:
	ARS(string flights, string hotels);
	AdjList* get_array();
	int Num_Cities() const;
	string* CityNames();
	string* Dates_A();
	string* Airlines_Names();
	int Numb_Dates();
	int Numb_Airline();
	void Show_Routes(string origin, string destination, string date,
		bool transit_loc_b, string transit_loc,
		bool transit_hours_b, string min, string max,
		bool airline_b, string airline,
		bool direct_flight, int cost_or_time, bool again);
};

#endif