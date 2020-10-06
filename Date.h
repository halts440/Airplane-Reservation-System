#ifndef DATE_H
#define DATE_H

#include<iostream>
#include<string>
using namespace std;

class Date {

private:
	int day;		    //variable to store the day
	int month;		    //variable to store current number of month
	int year;		    //variable to store current year
	string date_;	    //string to hold proper representation of the date

public:
	Date();															
	void set_Date(string dt);													
	int compare_date(const Date& obj);
	int get_Day();
	int get_Month();
	int get_Year();
	int compare_date(const Date& obj, int val);
	string to_str();
};

#endif