#ifndef CRUISE_H
#define CRUISE_H

#include "ship.h"

class Cruise : public Ship {
private:
    int maxPassengers;

public:
    Cruise() : Ship("", -1, cruise), maxPassengers(0) {}
    Cruise(std::string name, int year, int maxPass)
        : Ship(name, year, cruise), maxPassengers(maxPass) {}

    // setter & getter
    void setmaxPassengers(int maxPass) { maxPassengers = maxPass; }
    int getmaxPassengers() const { return maxPassengers; }

    // override print function
    void print() const override {
        std::cout << "Name: " << getShName() << ", Year: " << getShYear() << ", Maximum Passengers: " << maxPassengers << std::endl;
    }
};

#endif
