// Question2

#include <iostream>

// Abstract class
class TransportVehicle
{
public:
    virtual void loadCargo() = 0;
    virtual void startJourney() = 0;
};

// concrete class
class Truck : public TransportVehicle
{
public:
    void loadCargo()
    {
        std::cout << "Loading cargo onto a truck." << std::endl;
    }
    void startJourney()
    {
        std::cout << "Starting the truck journey." << std::endl;
    }
};

// concrete class
class Ship : public TransportVehicle
{
public:
    void loadCargo()
    {
        std::cout << "Loading cargo onto a ship." << std::endl;
    }
    void startJourney()
    {
        std::cout << "Starting the ship journey." << std::endl;
    }
};

// concrete class
class Airplane : public TransportVehicle
{
public:
    void loadCargo()
    {
        std::cout << "Loading cargo onto a airplane." << std::endl;
    }
    void startJourney()
    {
        std::cout << "Starting the airplane journey." << std::endl;
    }
};

// Abstract Factory class
class TransportVehicleFactory
{
public:
    virtual TransportVehicle *createTransportVehicle(std::string vehicleType) = 0;
};

class TransportVehicleTypeFactory : public TransportVehicleFactory
{
public:
    TransportVehicle *createTransportVehicle(std::string vehicleType)
    {
        if (vehicleType == "Truck")
        {
            return new Truck();
        }
        else if (vehicleType == "Ship")
        {
            return new Ship();
        }
        else if (vehicleType == "Airplane")
        {
            return new Airplane();
        }
        std::cerr << "Unsupported transport vehicle type: " << vehicleType << std::endl;
        return nullptr;
    }
};

int main()
{
    TransportVehicleFactory *vehicleTypeObj = new TransportVehicleTypeFactory();
    std::string continueOption;
    do
    {

        std::string vehicleType;
        std::cout << "enter the mode of transportation (Truck or Ship or Airplane)" << std::endl;
        std::cin >> vehicleType;
        TransportVehicle *transportVehicle = vehicleTypeObj->createTransportVehicle(vehicleType);
        if (transportVehicle)
        {
            transportVehicle->loadCargo();
            transportVehicle->startJourney();
        }
        else
        {
            std::cout << "Please Enter (Truck or Ship or Airplane)" << std::endl;
        }

        std::cout << "do you want to continue: (y/n)" << std::endl;
        std::cin >> continueOption;

    } while (continueOption == "y" || continueOption == "Y");

    return 0;
}