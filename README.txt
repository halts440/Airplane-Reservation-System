To run the project run the following command on cmd. G++ must be installed on PC. 
g++ -o prog main.cpp Node.cpp AdjList.cpp Vector.cpp ARS.cpp Data.cpp Date.cpp  Time.cpp Menu.cpp

then run
prog



On Ubuntu it will work too.
Programme has been tested and is running properly.



-----Layers-----
Layer 1:
Menu.h is the View Layer and has functions to display menu for different options and to save user choice

Layer 2:
Ars.h is the main file that do the calculations related to flight finding
All the other files (AdjList, Date, Node, Time, Vector) are used in ARS class

Layer 3:
Data.h is the data layer and provides data to the Programme



main.cpp is where programme will start it will create Menu and ARS objects and call the rquired functions.