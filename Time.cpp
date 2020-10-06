#include "Time.h"


// Constructor
Time::Time() {
    hour = 0;
    minutes = 0;
    time_ = "";
}

// Set Time Function
void Time::set_time(string t) {
    if (t[1] == ':') { 					//if number of hours are less than 10
        // hour
        hour = t[0] - 48;			    //hours will be equal to ascii of 1st character minus 48
        // minutes
        minutes = t[2] - 48;		    //minutes will be calculated from the asciis of 3rd and 4th character of string
        minutes *= 10;
        minutes += t[3] - 48;
        time_ = t;						//simply equate the strings
    }
    else {                              //else hours will be doubly digit
        // hour
        hour = t[0] - 48;			    //hours will be calculated from ascii of 1st two characters of string
        hour *= 10;
        hour += t[1] - 48;
        // minutes
        minutes = t[3] - 48;			//minutes will be calculated from the asci of 4th and 5th charater of string
        minutes *= 10;
        minutes += t[4] - 48;
        time_ = t;						//simply equate the time strings
    }
}

// Check Time Function
// Compares the time returns
// 1 if same,   2 if less,  3 if greater
int Time::check_time(const Time& obj) {
    if (hour < obj.hour)				//if number of hours are smaller means time is lesser
        return 2;
    else if (hour > obj.hour)			//if number of hours is greater means time is greater
        return 3;
    else if (hour == obj.hour) {		//if hours are same than check the minutes
        if (minutes == obj.minutes)		//if minutes are also same then it means both the times are equal
            return 1;
        else if (minutes < obj.minutes)
            return 2;
        else if (minutes > obj.minutes)
            return 3;
    }
}

// Add Time Function
void Time::add_time(const Time obj)	{		//function to add time
    hour += obj.hour;					    //add the hours of both objects
    minutes += obj.minutes;				    //add the minutes of both objects
    if (minutes >= 60) {				    //if minutes are greater than 60 increment hours and retain the minutes
        minutes -= 60;
        hour++;
    }
    update_time_str();					    //function to update the string of time
}

// Sub Time Function
void Time::sub_time(const Time obj) {		//function to subtratct time
    hour -= obj.hour;					    //subtracting the hours
    minutes -= obj.minutes;				    //subtracting the minutes
    if (minutes < 0) {					    //if minutes are less than zero decrement in hours and retain the minutes		
        minutes += 60;
        hour--;
    }
    update_time_str();					    //update the string of time
}

// Update Time String Function
void Time::update_time_str() {				    //function to update the string of time
    stringstream hh, mm;
    hh << hour;
    string temp_h = hh.str();				//converting the hours from integer to string
    temp_h.append(":");						//appending : afetr hours
    string temp_m;
    if (minutes < 10) {						//if minutes are less than 10
        if (minutes == 0)					//if minutes are 0 repalce space of minutes by 00
            temp_m = "00";
        else {
            mm << minutes;
            temp_m = mm.str();
            temp_m.append("0");				//else they will be in range of 1-9 so left most bit will be 0
        }
    }
    else {
        mm << minutes;
        temp_m = mm.str();					//else convert the minutes from integre tostrings
    }
    temp_h.append(temp_m);					//now appending minutes in the time
    time_ = temp_h;
}

// Add 24 Hours Function
// add 24 hours to the time
void Time::add_24Hours() {
    hour += 24;
    update_time_str();						//adjusting the time after adding 24 hours
}

// Sub From 24 Hour Function
// subtracts time from 24 hours
void Time::sub_from_24Hour() {
    Time temp;
    temp.set_time("24:00");
    sub_time(temp);							//subtracting the time from 24:00
}

// Get Hours Function
int Time::get_hours() {
    return hour;							//returning no of hours
}

// Get Minutes Function
int Time::get_minutes() {
    return minutes;						    //returning number of minutes
}

// Time To Str Function
string Time::time_to_str() {
    return time_;						    //returning string of time
}


