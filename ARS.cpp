#include "ARS.h"

// Constructor
ARS::ARS(string flights, string hotels) {
    number = 0;

    Data flights_data( flights );   // opening data link for flights 
    Data hotels_data( hotels );     // opening data link for hostels

    string str;			// a temp string used while reading data
    bool cont = true;	// a bool variable used to control while loop
    string temp_str;	// a temp string used in reading data

    Vector<string> temp_city;		//vector for holding name of cities
    Vector<string> temp_dates;		//vector for holding the available dates
    Vector<string> temp_airlines;   //vector for holding name of airlines

    while (cont) {
        // Origin
        temp_str = flights_data.next();						//getting city of origin
        if (search_string(temp_city, temp_str) == 0)		//if city isn't present in temp city vector push it
            temp_city.push(temp_str);

        // Destination	
        temp_str = flights_data.next();						//getting city of destination
        if (search_string(temp_city, temp_str) == 0)	    //if city isn't present in temp city vector push it
            temp_city.push(temp_str);

        // Date of travel
        temp_str = flights_data.next();						//getting date of travel
        if (search_string(temp_dates, temp_str) == 0)	    //if date isn't present in temp dates vector push it
            temp_dates.push(temp_str);

        // Flying Time								//getting flying time
        str = flights_data.next();	
        // Landing Time
        str = flights_data.next();				//getting landing time
        // Ticket Price
        str = flights_data.next();			    //getting ticket price

        // Airline				
        temp_str = flights_data.next();	        //getting the name of airline

        if (search_string(temp_airlines, temp_str) == 0)		//if the airline is not present in vector then insert it
            temp_airlines.push(temp_str);

        // check if there is still data available
        if( flights_data.isDataRemaining() == false )		//if there is no data, exit from loop
            cont = false;
    }

    NoOfCities = temp_city.getSize();				//getting no of cities

    cities = new string[NoOfCities];				    //allocating memory to cities
    dates = new string[temp_dates.getSize()];		    //allocating memory to dates
    num_dates = temp_dates.getSize();				    //getting no of dates

    airlines = new string[temp_airlines.getSize()];	    //allocating memory to airlines
    num_airlines = temp_airlines.getSize();			    //getting no of airlines
    hotel_charges = new int[NoOfCities];			    //allocating memory for hotel charges
    for (int i = 0; i < NoOfCities; i++)
        hotel_charges[i] = 0;
    array = new AdjList[NoOfCities];				    //allocating memory to adjoincy list

    // making array of city names from temp_city vector
    for (int i = 0; i < NoOfCities; i++)
        cities[i] = temp_city[i];

    // making array of dates from temp_dates vector
    for (int i = 0; i < temp_dates.getSize(); i++)
        dates[i] = temp_dates[i];

    // making array of airlines names from temp_airlines vector
    for (int i = 0; i < temp_airlines.getSize(); i++)
        airlines[i] = temp_airlines[i];

    // saving hotel charges in hotel charges variable
    cont = true;
    int i = 0;
    while (cont)
    {
        // city name
        string str1;
        str1 = hotels_data.next();	

        // getting index of city
        bool c = 1;
        for (i = 0; i < NoOfCities && c; i++)
        {
            if (cities[i] == str1)
                c = 0;
        }

        // hotel charges										
        str = hotels_data.next();	//converting hotel charges from string to integer
        stringstream hc(str);
        hc >> hotel_charges[i];
        
		//if there is no hotels data remaining
        if( !hotels_data.isDataRemaining() )
            cont = false;
    }

    // creating head nodes for adjancy list
    for (int i = 0; i < NoOfCities; i++)
    {
        Node* new_node = new Node;
        new_node->Origin = cities[i];				//inserting the city of origin
        new_node->Hotel_Charg = hotel_charges[i];	//inserting hotel charges 
        array[i].insert(new_node);
    }

    // start reading flights data again from the top
    flights_data.goToStart();

    cont = true;
    while (cont)
    {
        string s_origin;
        Node* new_node = new Node;

        // origin
        s_origin = flights_data.next();		

        // Destination as Origin
        new_node->Origin = flights_data.next();	    //inserting city of origin in node

        // Date of travel
        str = flights_data.next();		
        new_node->DateOfTravel.set_Date(str);	//inserting date of travel in node

        // Flying Time
        str = flights_data.next();		
        new_node->FlyingTime.set_time(str);	    //inserting flying time in node

        // Landing Time
        str = flights_data.next();		
        new_node->LandingTime.set_time(str);	//inserting landing time in node

        // if landing time > flying time
        if (new_node->LandingTime.check_time(new_node->FlyingTime) == 3)
        {
            // travel time = landing time - flying time
            new_node->Travel_Time = new_node->LandingTime;
            new_node->Travel_Time.sub_time(new_node->FlyingTime);						//total time of flight will be landing time - flying time
        }
        // if flying time > landing time
        else
        {
            // travel time = ( landing time + 24 hours ) - flying time
            new_node->Travel_Time = new_node->LandingTime;				
            new_node->Travel_Time.add_24Hours();
            new_node->Travel_Time.sub_time(new_node->FlyingTime);
        }

        // Ticket Price
        str = flights_data.next();		
        stringstream s(str);
        s >> new_node->TicketPrice;     //inserting ticket price as integer in new node

        // Airline
        new_node->Airline = flights_data.next();

        int index = find_value(cities, s_origin, NoOfCities);	//searching the index of city in array
        if (index != -1)									    //if city is present
        {
            new_node->Hotel_Charg = hotel_charges[index];	    //inserting hotel charges of that specific city

            Node* temp = array[index].head;
            temp = temp->Destination;

            // Checking for duplicate entry
            bool dupliacte = 0;												
            while (temp)
            {
                if (temp->Origin == new_node->Origin)
                {
                    if (temp->Airline.compare(new_node->Airline) == 0 &&
                        temp->FlyingTime.check_time(new_node->FlyingTime) == 1 &&
                        temp->LandingTime.check_time(new_node->LandingTime) == 1 &&
                        temp->DateOfTravel.compare_date(new_node->DateOfTravel) == 1 &&
                        temp->TicketPrice == new_node->TicketPrice)
                        dupliacte = 1;					//if another city with all same characteristics is present means dupicate found
                }
                temp = temp->Destination;				//check next city in that list
            }
            if (dupliacte == 0)							//if no duplicate found then insert the city
                array[index].insert(new_node);
        }

        // if there is no flight data available then exit from loop
        if ( !flights_data.isDataRemaining() )		
            cont = false;
    }
    // Constructor End
}

// Get Array Function
AdjList* ARS::get_array() {
    return array;				//returning Adjoincy list 
}

// Num Cities Function
// returns the total number of cities
int ARS::Num_Cities() const {
    return NoOfCities;			//returning number of cities
}

// City Names Function
// Returns the names of cities in the form of an array of strings
string* ARS::CityNames() {
    return cities;				//returning the array of cities
}

// Dates A Function
string* ARS::Dates_A() {
    return dates;				//returning the array of dates
}

// Airlines Names Function
string* ARS::Airlines_Names() {
    return airlines;			//returning array of airlines
}

// Numb Dates Function
int ARS::Numb_Dates() {
    return num_dates;			//returning no of avaiable dates
}

// numb Airline Function
int ARS::Numb_Airline() {
    return num_airlines;		//returning num of airlines
}

// Get Paths Function
// Returns the Paths as vector of vector of nodes
// a single path is avector of nodes
Vector<Vector<Node>> ARS::Get_Paths(string source_, string destination_) {
    // Get the node of the source city
    int index_s = 0;
    bool stop_s = false;
    for (int a = 0; a < NoOfCities && stop_s == false; a++)						//searching the source city
    {
        if (array[a].head->Origin == source_)
        {
            stop_s = true;		index_s = a;									//if city found exit from loop and save index in index_s
        }
    }

    // Get the node of the destination city
    int index_d = 0;
    bool stop_d = false;
    for (int a = 0; a < NoOfCities && stop_d == false; a++)						//now searching city of destination
    {
        if (array[a].head->Origin == destination_)
        {
            stop_d = true;		index_d = a;									//if city found exit from loop and save index in index_d
        }
    }

    Node* s = array[index_s].head;			// s points to source
    Node* d = array[index_d].head;			// d points to destination

    // A bool array that is of the sie number of cities and keep track of nodes visted
    bool* visited = new bool[NoOfCities];
    // Array of Nodes for saving path nodes
    Node* path = new Node[NoOfCities];
    // Number of nodes in path array
    int path_index = 0;
    // Intializing all visited nodes as zero
    for (int i = 0; i < NoOfCities; i++)
        visited[i] = false;

    // vector that will save nodes of paths
    Vector<Vector<Node>> paths;

    All_Paths(s, d, visited, path, path_index, paths);
    return paths;			// return paths
}

// Tota; Time And Charges Function
void ARS::Total_Time_And_Charges(Vector<Vector<Node>>& paths)
{
    // Total cost and total travel time
    for (int i = 0; i < paths.getSize(); i++)
    {
        for (int j = 0; j < paths[i].getSize(); j++)
        {
            // if node is not the first node then
            // Adding Travel Time and Ticket Price of Flight to first node
            if (j != 0)
            {
                paths[i][0].Travel_Time.add_time(paths[i][j].Travel_Time);
                paths[i][0].TicketPrice += paths[i][j].TicketPrice;
            }

            // Transit Time of Flights
            if (j != 0 && j <= (paths[i].getSize() - 2))
            {
                Time transit_time;
                // If landing time of flight 1 is greater than flying time
                if (paths[i][j].LandingTime.check_time(paths[i][j].FlyingTime) == 3)
                {
                    // if both flights are on the same day
                    if (paths[i][j].DateOfTravel.compare_date(paths[i][j + 1].DateOfTravel) == 1)
                    {
                        // transit time = flying time of flight 2 - landing time of flight 1
                        transit_time = paths[i][j + 1].FlyingTime;
                        transit_time.sub_time(paths[i][j].LandingTime);
                    }
                    else
                    {
                        // transit time = 24 hours in day - landing time of flight 1
                        transit_time.set_time("24:00");
                        transit_time.sub_time(paths[i][j].LandingTime);
                        int v = 1;
                        // add 24 hours for each day if date of flight 2 has not yet reached
                        while (paths[i][j].DateOfTravel.compare_date(paths[i][j + 1].DateOfTravel, v) != 1)
                        {
                            transit_time.add_24Hours();
                            v++;
                        }
                        // when both dates are equal then add the flying time of flight 2 to the transit time
                        if (paths[i][j].DateOfTravel.compare_date(paths[i][j + 1].DateOfTravel, v) == 1)
                            transit_time.add_time(paths[i][j + 1].FlyingTime);
                    }
                }
                // If landing time of flight 1 is less than flying time
                // means flights goes in the next day
                else
                {
                    int v = 1;
                    // check is date of flight 1 + v == date of next flight
                    while (paths[i][j].DateOfTravel.compare_date(paths[i][j + 1].DateOfTravel, v) != 1)
                    {
                        transit_time.add_24Hours();
                        v++;
                    }
                    // if date of flight 1 + v  == date of next flight
                    if (paths[i][j].DateOfTravel.compare_date(paths[i][j + 1].DateOfTravel, v) == 1)
                        transit_time.add_time(paths[i][j + 1].FlyingTime);

                    // transit = transit time - landing time of flight 1
                    transit_time.sub_time(paths[i][j].LandingTime);
                }

                // save transit time in current node
                paths[i][j].Transit_Time = transit_time;
                // add transit time to total time 
                paths[i][0].Travel_Time.add_time(transit_time);

                // if transit hours > 12 
                // add hotel charges
                if (transit_time.get_hours() > 12)
                {
                    // add hotel charges
                    int index = 0;
                    bool stop = false;
                    for (int a = 0; a < NoOfCities && stop == false; a++)
                    {
                        if (array[a].head->Origin == paths[i][j].Origin)
                        {
                            stop = true;		index = a;
                        }
                    }
                    paths[i][0].TicketPrice += hotel_charges[index];
                }

            }
        }
    }
}

// Print Paths Function
// prints all the function
void ARS::Print_Paths(Vector<Vector<Node>>& paths) {
    for (int i = 0; i < paths.getSize(); i++)
    {
        // if path is valid
        if (paths[i][0].p_check)
        {
            // print all nodes
            for (int j = 0; j < paths[i].getSize(); j++)
            {
                // if it is first node
                if (j == 0)
                    cout << paths[i][j].Origin << " ";
                else
                {
                    cout << "| ";
                    cout << paths[i][j].DateOfTravel.to_str() << " "
                        << paths[i][j].FlyingTime.time_to_str() << " "
                        << paths[i][j].LandingTime.time_to_str() << " "
                        << paths[i][j].Transit_Time.time_to_str() << " "
                        << paths[i][j].Airline << "| "
                        << paths[i][j].Origin << " ";
                }
            }
            cout << endl;
            cout << "Total Cost: " << paths[i][0].TicketPrice << endl; // print total fare
            cout << "Total Time: " << paths[i][0].Travel_Time.time_to_str() << endl;	// print total time of flight
            cout << endl << endl;
        }
    }
}

// All Paths Function
// This function add all the possible paths from source to the specified destination
void ARS::All_Paths(Node* u, Node* d, bool visited[], Node path[], int& path_index, Vector<Vector<Node>>& paths) {
    // Getting the index of u ( source ) node in  Adjancy list
    int index1 = 0;
    bool stop1 = false;
    for (int a = 0; a < NoOfCities && stop1 == false; a++)
    {
        if (array[a].head->Origin == u->Origin)		// if found stop the for loop
        {
            stop1 = true;		index1 = a;
        }
    }

    // marking node as visited
    visited[index1] = true;
    // saving node in path
    path[path_index] = *u;
    // number of nodes in path updated
    path_index++;

    // if current node == destination node
    if (u->Origin == d->Origin)
    {

        bool time_check = true;			// if this variable is true then this path will be added into paths

        // check for each node the time and date of that node and the next node are correct
        for (int i = 0; i < path_index; i++)
        {
            // if node is not first or last node
            if (path[i].DateOfTravel.to_str() != "" && i + 1 < path_index)
            {
                // if date of flight of node 1 > date of flight of node 2
                // then path is not correct
                if (path[i].DateOfTravel.compare_date(path[i + 1].DateOfTravel) == 3)
                    time_check = false;
                else
                {
                    // check if date of flight of node 1 and date of flight of node 2 are on the same
                    if (path[i].DateOfTravel.compare_date(path[i + 1].DateOfTravel) == 1)
                    {
                        // if flying time of node 1 > landing time of node 1
                        // then path is not correct
                        if (path[i].FlyingTime.check_time(path[i].LandingTime) == 3)
                        {
                            time_check = false;
                        }
                        // flying time of node 1 < landing time of node 1
                        else
                        {
                            // if flying time of node 2 < landing time of node 1
                            // then path is not correct
                            if (path[i + 1].FlyingTime.check_time(path[i].LandingTime) == 2)
                                time_check = false;
                        }
                    }

                    // if date of flight of node 1    + 1  ==  date of flight of node 2
                    if ((path[i].DateOfTravel.compare_date(path[i + 1].DateOfTravel, 1) == 1))
                    {
                        // if flying landing time > landing time
                        if (path[i].FlyingTime.check_time(path[i].LandingTime) == 3)
                            // if flying time of node 2 < landing time of node 1
                            // then path is not correct
                            if (path[i + 1].FlyingTime.check_time(path[i].LandingTime) == 2)
                                time_check = false;
                    }
                }
            }
        }
        // if time check == 1 then add path
        if (time_check == 1)
        {
            // add nodes to vector v
            Vector<Node> v;
            for (int i = 0; i < path_index; i++)
                v.push(path[i]);
            // v vector to paths
            paths.push(v);
            number++;
        }
    }
    // if node was not the destination node
    else
    {
        // temp points to head of linked list
        Node* temp = array[index1].head;
        // now temp points to its first child
        temp = temp->Destination;
        while (temp)
        {
            // check if node is visited
            int index2 = 0;
            bool stop2 = false;
            for (int a = 0; a < NoOfCities && stop2 == false; a++)
            {
                if (array[a].head->Origin == temp->Origin)		// if city was found end the loop and save value of i as index2
                {
                    stop2 = true;		index2 = a;
                }
            }
            // if node was not visited insert it into queue
            if (visited[index2] == 0)
                All_Paths(temp, d, visited, path, path_index, paths);
            // temp points to next child of u
            temp = temp->Destination;
        }
    }
    // removing u node from path
    path_index--;
    // marking u as unvisited
    visited[index1] = false;
}

// Show Routes
// Get all possible routes from souce to destination
// and display them
void ARS::Show_Routes(string origin, string destination, string date,
    bool transit_loc_b, string transit_loc,
    bool transit_hours_b, string min, string max,
    bool airline_b, string airline,
    bool direct_flight, int cost_or_time, bool again)
{
    // if cost or time preference is not specified then take time as a preference
    if (cost_or_time == -1)
        cost_or_time = 2;

    // get all the paths
    Vector<Vector<Node>> paths = Get_Paths(origin, destination);
    // calculate thier total charges and time
    Total_Time_And_Charges(paths);
    // sort the paths according to time or cost
    Sort_Paths(paths, cost_or_time);
    // check if user date matched
    Check_Date(paths, date);

    // if transit location was specified
    if (transit_loc_b)
    {
        // check if transit location was found in paths
        Check_Transit_Location(paths, transit_loc);
        // if hours was specified then check paths with correct transit stay
        if (transit_hours_b)
            Check_Transit_Hours(paths, transit_loc, min, max);
    }

    // check paths for user airline preference if specified
    if (airline_b)
        Check_Airline(paths, airline);

    // check paths for direct flights if specified
    if (direct_flight)
        Check_Direct_Flights(paths);

    cout << endl;

    // displaying date
    cout << date << endl;

    // if number of paths found is 0
    if (Num_Paths(paths) == 0)
    {
        cout << "Sorry no Flights Avaliable on this date....";
        if (direct_flight != 1)
        {
            date[0] = date[0] - 1;
            // flights for previous day
            if (again && date[0] > 0)
                Show_Routes(origin, destination, date,
                    0, transit_loc,
                    0, min, max,
                    0, airline,
                    0, cost_or_time, 0);

            // flights for next day
            date[0] = date[0] + 2;
            if (again && date[0] > 0)
                Show_Routes(origin, destination, date,
                    0, transit_loc,
                    0, min, max,
                    0, airline,
                    0, cost_or_time, 0);
        }
        else
        {
            cout << endl;
            cout << "Other than direct flights...." << endl;

            Show_Routes(origin, destination, date,
                0, transit_loc,
                0, min, max,
                0, airline,
                0, 0, 1);
        }

    }
    else
        // print all the valid paths
        Print_Paths(paths);
}

// Check Transit Location
// check for paths if they contain a specified transit location
void ARS::Check_Transit_Location(Vector<Vector<Node>>& paths, string transit_loc) {
    for (int a = 0; a < paths.getSize(); a++)
    {
        bool transit_found = false;						// intially transit location found is set to 0
        for (int b = 0; b < paths[a].getSize(); b++)
        {
            if (b != 0 && b != paths[a].getSize() - 1)		// if node is not first node and not last node
            {
                if (paths[a][b].Origin == transit_loc)		// if transit location id found then set transit fount = 1
                    transit_found = 1;
            }
        }
        if (transit_found == 0)		// if transit location was not found then path is not valid
            paths[a][0].p_check = 0;
    }
}

// Check Direct Flights
// check paths for direct flights
void ARS::Check_Direct_Flights(Vector<Vector<Node>>& paths) {
    for (int a = 0; a < paths.getSize(); a++)
    {
        if (paths[a].getSize() > 2)		// if path size is > 2 then path is not valid
            paths[a][0].p_check = 0;
    }
}

// Check Airline Function
// check paths if they contain the spcified airline or not
void ARS::Check_Airline(Vector<Vector<Node>>& paths, string airline) {
    for (int a = 0; a < paths.getSize(); a++)
    {
        bool airline_found = false;			// initally airline found set to 0
        for (int b = 0; b < paths[a].getSize(); b++)
        {
            if (b != 0)		// if node is not the first node
            {
                if (paths[a][b].Airline == airline)		// if airline found set airline found to 1
                    airline_found = 1;
            }
        }
        // if airline found is zero path is not valid
        if (airline_found == 0)
            paths[a][0].p_check = 0;
    }
}

// Num Paths Function
// turns the number of valid paths
int ARS::Num_Paths(Vector<Vector<Node>>& paths) {
    int count = 0;
    for (int a = 0; a < paths.getSize(); a++)
    {
        if (paths[a][0].p_check)		// if path is valid, count = count + 1
            count++;
    }
    return count;
}

// Check Transit Hours Function
// checks paths for correct transit stay
void ARS::Check_Transit_Hours(Vector<Vector<Node>>& paths, string transit_loc, string min, string max) {
    for (int a = 0; a < paths.getSize(); a++)
    {
        bool transit_t = false;		// intiallially transit stay time is set to false
        for (int b = 0; b < paths[a].getSize(); b++)
        {
            // if node is not first and last nodes
            if (b != 0 && b != paths[a].getSize() - 1)
            {
                // if transit location was found
                if (paths[a][b].Origin == transit_loc)
                {
                    Time temp1, temp2;
                    temp1.set_time(min);	// minimun transit time
                    temp2.set_time(max);	// maximum transit time
                    // transit time >= min transit stay
                    if (paths[a][b].Transit_Time.check_time(temp1) == 1 || paths[a][b].Transit_Time.check_time(temp1) == 3)
                    {
                        // max transit stay >= transit time
                        if (temp2.check_time(paths[a][b].Transit_Time) == 1 || temp2.check_time(paths[a][b].Transit_Time) == 3)
                            transit_t = 1;
                    }
                }
            }
        }
        // if transit t == 0 not a valid path
        if (transit_t == 0)
            paths[a][0].p_check = 0;
    }
}

// Check Date
// check paths for correct date
void ARS::Check_Date(Vector<Vector<Node>>& paths, string date) {
    for (int a = 0; a < paths.getSize(); a++)
    {
        if (paths[a][1].DateOfTravel.to_str().compare(date) != 0)	// if dates were not equal not a valid path
            paths[a][0].p_check = 0;
    }
}

// Sort Path Function
// sort paths according to travel time or price
void ARS::Sort_Paths(Vector<Vector<Node>>& paths, int cost_or_travel) {
    for (int pass = 1; pass < paths.getSize(); pass++)
    {
        for (int i = 0; i < paths.getSize() - pass; i++)
        {
            // cost or travel == 1 , sort according to price
            if (cost_or_travel == 1)
            {
                // if cost of path 1 > cost of path 2
                if (paths[i][0].TicketPrice > paths[i + 1][0].TicketPrice)
                {
                    // swap
                    Vector<Node> temp;
                    temp = paths[i];
                    paths[i] = paths[i + 1];
                    paths[i + 1] = temp;
                }
            }
            // cost or travel == 1 , sort according to travel time
            if (cost_or_travel == 2)
            {
                // if travel time of path 1 > travel time of path 2
                if (paths[i][0].Travel_Time.check_time(paths[i + 1][0].Travel_Time) == 3)
                {
                    // swap
                    Vector<Node> temp;
                    temp = paths[i];
                    paths[i] = paths[i + 1];
                    paths[i + 1] = temp;
                }
            }
        }
    }
}

// Search String Function
// searches a string in a string vector and returns true or false
bool ARS::search_string(Vector<string>& t, string str) {		//function to verify presence of string in a vector
	bool found = 0;
	for (int a = 0; a < t.getSize(); a++)
		if (t[a] == str)
			found = 1;
	return found;
}

// Find Value Function
// Finds a string in the array of strings and returns its index
int ARS::find_value(string arr[], string value, int size) {	    //function to return the index of string in string array
	int index = -1;							// intial index set to -1
	bool go = true;
	for (int a = 0; go && a < size; a++) {
		if (arr[a] == value)			// if value was found then stop the loop and save the index
		{
			index = a;
			go = false;
		}
	}
	return index;
}