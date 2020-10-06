#include "Node.h"

//default constructor
Node::Node() {
    Origin = "";
    Destination = NULL;
    TicketPrice = 0;
    Airline = "";
    Hotel_Charg = 0;
    p_check = 1;
}

// Show Data Function
void Node::show_data() {
    cout << "Destination: " << Origin << endl;
    cout << "Date of Travel: " << DateOfTravel.to_str() << endl;
    cout << "Flying Time: " << FlyingTime.time_to_str() << endl;
    cout << "Landing Time: " << LandingTime.time_to_str() << endl;
    cout << "Ticket Price: " << TicketPrice << endl;
    cout << "AirLine: " << Airline << endl;
    cout << "Hotel Charges: " << Hotel_Charg << endl;
}