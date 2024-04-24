#include <iostream>
using namespace std;

//Declaring the base class "Vehicle"
class Vehicle {
    //Attributes
    public:
        string make;
        string model;
        int year;

        //The virtual function "calculateRentalCost"
        double calculateRentalCost();
};

//These are the derived classes. They inherit the attributes of the "Vehicle" class.
class Car : public Vehicle {
    public:
        string numberOfDoors;
        //Add more attributes that are unique to cars
};

class SUV : public Vehicle {
    public:
        int groundClearance;
        //Add more attributes that are unique to SUVs
};

class Truck : public Vehicle {
    public:
        int numberOfWheels;
        int cargoCapacity;
        //Add more attributes that are unique to Trucks
};

int main () {
    
    return 0;
}


