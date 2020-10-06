#include<iostream>
#include "Data.h"
using namespace std;

int main() {
    Data d("Flights.txt");
    int c;
    string dt;
    while(1) {
        cout << "choice: ";
        cin >> c;
        dt = d.next();
        cout << "Data: " << dt << endl;
    }
}