#ifndef CARGO_H
#define CARGO_H

#include "ship.h"

class Cargo : public Ship {
private:
    int cargoCapacity;

public:
    Cargo() : Ship("", -1, cargo), cargoCapacity(0) {}
    Cargo(std::string name, int year) : Ship(name, year, cargo), cargoCapacity(0) {} // Added this constructor
    Cargo(std::string name, int year, int capacity)
        : Ship(name, year, cargo), cargoCapacity(capacity) {}

    // setter & getter
    void setCapacity(int capacity) { cargoCapacity = capacity; }
    int getcargoCapacity() const { return cargoCapacity; }

    // override print function
    void print() const override {
        std::cout << "Name: " << getShName() << ", Year: " << getShYear() << ", Capacity (in tons): " << cargoCapacity << std::endl;
    }
};

#endif