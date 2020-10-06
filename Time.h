#ifndef TIME_H
#define TIME_H

#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Time {
    private:
        int hour;																											
        int minutes;														
        string time_;													

    public:
        Time();
        void set_time(string t);														
        int check_time(const Time& obj);
        void add_time(const Time obj);									
        void sub_time(const Time obj);									
        void update_time_str();											
        void add_24Hours();
        void sub_from_24Hour();
        int get_hours();
        int get_minutes();
        string time_to_str();
};

#endif