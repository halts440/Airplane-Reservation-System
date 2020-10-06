#include<iostream>
#include "ARS.h"
#include "Menu.h"
using namespace std;

int main()
{
	// making an object of ARS
	ARS ars_("Flights.txt", "HotelCharges_perday.txt");
	Menu m;
	// saving ars data in menu for displaying
	m.getARSData(ars_);

	// showing start screen
	m.showSplashScreen();


	m.selectOrigin();
	m.selectDestination();
	m.selectDateFlight();
	m.selectTransit();
	m.selectTransitLocation();
	m.selectAirline();
	m.selectTimeOrCost();
	m.selectDirectFlight();
	
	// display paths according to user query
	ars_.Show_Routes(  m.getOrigin(), m.getDestination(),  m.getDateOfTravel(),
					   m.getTransitLocFlag(),  m.getTransitLoc(),
					   m.getTransitHoursFlag(), m.getTransitHoursMin(), m.getTransitHoursMax(),
					   m.getAirlineFlag(),  m.getAirline(),
					   m.getDirectFlightFlag(), m.getTimeOrCost(), 1);

	// end
	cout << endl;
	cout << "Enter any character to exit...";
	int stop;
	cin >> stop;
	return 0;

}

