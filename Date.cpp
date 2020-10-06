#include "Date.h"

// Constructor
Date::Date() {
    day = 0;
    month = 0;
    year = 0;
    date_ = "";
}

// Set Date Function
void Date::set_Date(string dt) {
    date_ = dt;					//simply equate the string
    if (dt[1] == '/') {			//if days are singly digit
        day = dt[0] - 48;		//day canbe found by subtracting 48 from ascii of 1st character

        month = dt[2] - 48;		//month canbe get from ascii of 3rd and 4th charcters of string
        month *= 10;
        month += dt[3] - 48;

        year = dt[5] - 48;		//hours will be calculated from the asiis of 6-9th chaacters of string
        year *= 10;
        year += dt[6] - 48;
        year *= 10;
        year += dt[7] - 48;
        year *= 10;
        year = dt[8] - 48;
        year *= 10;
    }
    else if (dt[2] == '/') {	//else if day is doubly digit
        day = dt[0] - 48;		//calculate mon th ascii of 1st 2 characters of string
        day *= 10;
        day += dt[1] - 48;

        month = dt[3] - 48;		//month canbe get from ascii of 3rd and 4th charcters of string
        month *= 10;
        month += dt[4] - 48;

        year = dt[6] - 48; 		// hours will be calculated from the asiis of 6 - 9th chaacters of string
        year *= 10;
        year += dt[7] - 48;
        year *= 10;
        year += dt[8] - 48;
        year *= 10;
        year = dt[9] - 48;
        year *= 10;
    }
}

// Compare Date Function
int Date::compare_date(const Date& obj) {
    if (year < obj.year)
        return 2;			    			//current year is less so the date is lesser
    else if (year > obj.year)
        return 3;						    //current year is greater so the date is greater
    else if (year == obj.year) {	        //if yerars are equal check the minutes
        if (month < obj.month)	    		//if month is less means date is less
            return 2;
        else if (month > obj.month)	    	//if month is greater means the date is greater
            return 3;
        else if (month == obj.month) {	    //if months are equal then check the day
            if (day < obj.day)			    //if days are less means day is less
                return 2;
            else if (day > obj.day)		    //if days are greater than day is greater
                return 3;
            else if (day == obj.day)    	//else date will be same
                return 1;
        }
    }
}

// Get Day Function
int Date::get_Day() {
    return day;				//returning the day
}

// Get Month Function
int Date::get_Month() {
    return month;			//returning month
}

// Get Year Function
int Date::get_Year() {
    return year;			//returning year
}

// Compare Date Function
// returns 1 if equal,  2 if less,  3 if greater
int Date::compare_date(const Date& obj, int val) {	    //function to add the value in day and compare the dates
    val += day;								    //adding the value in day
    if (year < obj.year)					//current year is less so the date is lesser
        return 2;
    else if (year > obj.year)				//current year is greater so the date is greater
        return 3;
    else if (year == obj.year) {		    //if yerars are equal check the minutes
        if (month < obj.month)				//if month is less means date is less
            return 2;
        else if (month > obj.month)			//if month is greater means the date is greater
            return 3;
        else if (month == obj.month) {		//if months are equal then check the day
            if (val < obj.day)				//if days are less then date is smaller
                return 2;
            else if (val > obj.day)			//if days are greater than date is greater
                return 3;
            else if (val == obj.day)		//else date will be same
                return 1;
        }
    }
}

// To Str Function
string Date::to_str() {
    return date_;							//returning string of dat
}
