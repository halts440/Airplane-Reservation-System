#include "Data.h"

// Constructor
Data::Data(string fname) {
    file.open( fname.c_str() );
}
// next function
// gives the next string
string Data::next() {
    file >> dt;
    return dt;
}

// isDataRemaining
// find if there is still data available
bool Data::isDataRemaining() {

    //cout << "CALLED  " << file.eof() << " OK" << endl;

    bool val = false;
    if( file.eof() ) 
        val = false;
    else
        val = true;
    return val;
}

// goToStart Function
// go to start of data and read from that point
void Data::goToStart() {
    file.clear();
    file.seekg(0, ios::beg);
}

// Destructor
Data::~Data() {
    file.close();
}