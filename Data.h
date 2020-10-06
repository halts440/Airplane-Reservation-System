#ifndef DATA_H
#define DATA_H

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Data {
    private:
        string file_name;
        fstream file;
        string dt;
    public:
        Data(string fname);
        string next();
        bool isDataRemaining();
        void goToStart();
        ~Data();
};

#endif