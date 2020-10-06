#include "Menu.h"

// showSplashScreen Function
void Menu::showSplashScreen() {
    char select;
    // Splash screen
    system("CLS");
	cout << endl << endl << endl;

	cout << "					" << " _____   _____   _____          _____           ____" << endl;
	cout << "					" << "|     |    |    |     |  |        |    |\\    | |    " << endl;
	cout << "					" << "|_____|    |    |_____|  |        |    | \\   | |____" << endl;
	cout << "					" << "|     |    |    |    \\   |        |    |   \\ | |    " << endl;
	cout << "					" << "|     |  __|__  |     \\  |_____ __|__  |    \\| |____" << endl;

	cout << "		" << " _____    ____   _____   ____    _____            _____    _______  _____   _____          " << endl;
	cout << "		" << "|     |  |      |       |       |     | \\      \/ |     |  |   |   |   |    |     |  |\\    |" << endl;
	cout << "		" << "|_____|  |____  |____   |____   |_____|  \\    \/  |_____|      |       |    |     |  | \\   |" << endl;
	cout << "		" << "|    \\   |           |  |       |    \\    \\  \/   |     |      |       |    |     |  |   \\ |" << endl;
	cout << "		" << "|     \\  |____  _____|  |____   |     \\    \\\/    |     |      |     __|__  |_____|  |    \\|" << endl;

	cout << "					" << " ____            ____   _______   _____            " << endl;
	cout << "					" << "|      \\     \/  |      |   |   | |       |\\      \/|" << endl;
	cout << "					" << "|____   \\   \/   |____      |     |____   | \\    \/ |" << endl;
	cout << "					" << "     |    |          |     |     |       |  \\  \/  |" << endl;
	cout << "					" << "_____|    |     _____|     |     |_____  |   \\\/   |" << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "					Enter any character to continue.. ";
	cin >> select;
}

// getARSData Function
void Menu::getARSData( ARS& obj) {
    Loc_Num = obj.Num_Cities();
    Loc_Names = obj.CityNames();
    dt = obj.Dates_A();
    airl = obj.Airlines_Names();
    n_dt = obj.Numb_Dates();
    n_airl = obj.Numb_Airline();
}

// selectOrigin Function
void Menu::selectOrigin() {
    choice = 0;
    while (choice < 1 || choice > Loc_Num)
	{
		system("CLS");
		cout << endl << "						Welcome To Flight Reservation System" << endl << endl;

		// Select City Of Origin
		cout << "	" << "Select your current city: " << endl << endl;
		for (int i = 0; i < Loc_Num; i++)				// displaying cities
			cout << "	" << i + 1 << ". " << Loc_Names[i] << endl;
		cout << endl << "	";

		cin >> choice;
	} 
	Origin_ = Loc_Names[choice-1];
}

// selectDestination Function
void Menu::selectDestination() {
    // Select City Of Destination
	choice = 0;
	while(choice < 1 || choice > Loc_Num || Loc_Names[choice-1] == Origin_)
	{
		system("CLS");

		cout << endl << endl << endl << "	" <<"Select your destination city: " << endl << endl;

		for (int i = 0; i < Loc_Num; i++)		// display cities
		{
			cout << "	" <<  i + 1 << ". " << Loc_Names[i];
			if ( Loc_Names[i] == Origin_)		// if city as used as origin place a X in front of it
				cout << "	X";
			cout<< endl;
		}
		cout << endl <<  "	" ;

		cin >> choice;
	}
	Destination_ = Loc_Names[choice - 1];		// save selected city in Destination_
}

// selectDateFlight Function
void Menu::selectDateFlight() {
    // Select Date For Flight
	choice = 0;
	while (choice < 1 || choice > n_dt)
	{
		system("CLS");

		cout << endl << endl << endl << "	" << "Select date of flight:" << endl << endl;
		
		for (int i = 0; i < n_dt; i++)		// display dates
			cout << "	" << i + 1 << ". " << dt[i] << endl;
		cout << endl << "	";
		
		cin >> choice;
	}
	DateOfTravel_ = dt[choice - 1];		// save select date as DateOfTravel
}

// selectTransit Function
void Menu::selectTransit() {
    // Select Transit
	system("CLS");

	// asking user if they want to specify a transit location
	cout << endl << endl << endl<<"	" << "Do You want to have a transit(Y/N): ";
	cin >> select;
	
	if (select == 'y' || select == 'Y')
		transit_location_b = 1;
}

// selectTransitLocation Function
void Menu::selectTransitLocation() {


	// if user wants to specify a transit location
	if (transit_location_b)
	{
		choice = 0;
		while (choice < 1 || choice > Loc_Num || Loc_Names[choice - 1] == Origin_ || Loc_Names[choice - 1] == Destination_)
		{
			system("CLS");

			// Getting a Transit Location
			choice = 0;

			cout << endl << endl;
			cout << endl << "	" << "Select a transit location: " << endl << endl;
			
			for (int i = 0; i < Loc_Num; i++)		// display a transit location
			{
				cout << "	" << i + 1 << ". " << Loc_Names[i];
				if (Loc_Names[i] == Origin_ || Loc_Names[i] == Destination_)	// put a X if location was used as origin and destination
					cout << "	X";
				cout << endl;
			}
			cout << endl << "	";
			
			cin >> choice;
		}
		transit_location = Loc_Names[choice - 1];	// saving selected city as transit location


		// Getting transit hours
		cout << endl << "	" << "Do You want to specify transit hours(Y/N): ";

		cin >> select;
		
		if (select == 'y' || select == 'Y')
		{
			transit_hours_b = 1;
			cout << endl;
			
			// get minimum transit hours
			cout << "	" << "Enter hours minimum transit duration (00:00):	";
			cin >> transit_min;
			
			// get maximum transit hours
			cout << "	" << "Enter hours maximum transit duration (00:00):	";
			cin >> transit_max;
		}
	}

}

// selectAirline Function
void Menu::selectAirline() {
    // Select Airline
	system("CLS");

	cout << endl << endl << endl <<  "	" << "Do You want to specify Airline(Y/N): ";
	cin >> select;
	
	if (select == 'y' || select == 'Y')
	{
		airline_b = 1;
		cout << endl << "	" << "Select An Airline For Flight:" << endl << endl;
		
		for (int i = 0; i < n_airl; i++)		// displaying all the airlines
			cout << "	" << i + 1 << ". " << airl[i] << endl;
		cout << endl << "	";
		
		cin >> choice;
		Airline_ = airl[choice - 1];		// Saving selected Airline as Airline_
	}
}

// selectTimeOrCost Function
void Menu::selectTimeOrCost() {
    // Select Cost or Travel Time
	system("CLS");
	cout << endl << endl << endl << "	" << "Do You want to mention cost or travel time(Y/N): ";
	cin >> select;
	
	if (select == 'y' || select == 'Y')
	{
		cout << endl;
		cout << "	1. Cost\n	2. Travel Time" << endl;
		cout << endl << "	";
		cin >> cost_travel;
	}
}

// selectDirectFlight Function
void Menu::selectDirectFlight() {
    
	// if transit location is not specified ask if used wants a direct flight
	if (transit_location_b == 0)
	{
		system("CLS");
		cout << endl << endl << endl << "	" << "Do you want to have a direct flight(Y/N): ";
		cin >> select;
		
		if (select == 'y' || select == 'Y')
			direct_flight = 1;
		else
			direct_flight = 0;
	}
}

// getOrigin Function
string Menu::getOrigin() const {
	return Origin_;
}

// getDestination Function
string Menu::getDestination() const {
	return Destination_;
}

// getDateOfTravel Function
string Menu::getDateOfTravel() const {
	return DateOfTravel_;
}

// getTransitLocFlag Function
bool Menu::getTransitLocFlag() const {
	return transit_location_b;
}

// getTransitLoc Function
string Menu::getTransitLoc()  const {
	return transit_location;
}

// getTransitHoursFlag Function
bool Menu::getTransitHoursFlag() const {
	return transit_hours_b;
}

// getTransitHoursMin Function
string Menu::getTransitHoursMin() {
	return transit_min;
}

// getTransitHoursMax Function
string Menu::getTransitHoursMax() {
	return transit_max;
}

// getAirlineFlag Function
bool Menu::getAirlineFlag() {
	return airline_b;
}

// getAirline Function
string Menu::getAirline() {
	return Airline_;
}

// getDirectFlightFlag Function
bool Menu::getDirectFlightFlag() {
	return direct_flight;
}

// getTimeOrCost Function
bool Menu::getTimeOrCost() {
	return cost_travel;
}












