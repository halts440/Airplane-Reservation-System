#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<string>
#include "ARS.h"
using namespace std;

class Menu {
    private:
            // variables to store details of flights specified by user
        string	Origin_,				// city of origin
                Destination_,			// destination
                DateOfTravel_,			// date of travel
                transit_location,		// transit location
                Airline_;				// airline name
        string	transit_min,
                transit_max;
        
        // some boolean variables as checks
        bool transit_location_b = 0;
        bool transit_hours_b = 0;
        bool c_t = 0;
        bool cost_travel = -1;
        bool airline_b = 0;
        bool direct_flight = 0;
        
        // selection varaibles
        int choice = 0;
        char select = 'a';

        // arrays containing city names, dates, airlines from ARS object that will be created
        int		Loc_Num;
        string* Loc_Names;
        string* dt;
        string* airl;
        int n_dt;
        int n_airl;
        

    public:
        // Start Screen Showing Functions
        void showSplashScreen();

        // Data Setting Function
        void getARSData( ARS& obj);
        
        // Menu Displaying Functions
        void selectOrigin();
        void selectDestination();
        void selectDateFlight();
        void selectTransit();
        void selectTransitLocation();
        void selectAirline();
        void selectTimeOrCost();
        void selectDirectFlight();

        // Selected Options Getting Functions
        string getOrigin() const;
        string getDestination() const;
        string getDateOfTravel() const;
        bool getTransitLocFlag() const;
        string getTransitLoc()  const;
        bool getTransitHoursFlag() const;
        string getTransitHoursMin();
        string getTransitHoursMax();
        bool getAirlineFlag();
        string getAirline();
        bool getDirectFlightFlag();
        bool getTimeOrCost();
};

#endif