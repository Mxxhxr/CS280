#ifndef CRUISE_H
#define CRUISE_H

#include "ship.h"

class Cruise : public Ship {
private:
    int maxPassengers;

public:
    Cruise();
    Cruise(const std::string& name, int year, int maxPassengers);
    ~Cruise() {}

    // Getter and Setter for maxPassengers
    void setmaxPassengers(int passengers);
    int getmaxPassengers() const;

    // Implementation of the inherited abstract print method
    void print() const override;
};

#endif  // CRUISE_H
