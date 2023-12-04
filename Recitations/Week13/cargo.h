#ifndef CARGO_H
#define CARGO_H

#include "ship.h"

class Cargo : public Ship {
private:
    int cargoCapacity;

public:
    Cargo();
    Cargo(const std::string& name, int year, int cargoCapacity);
    ~Cargo() {}

    // Getter and Setter for cargoCapacity
    void setCargoCapacity(int capacity);
    int getCargoCapacity() const;

    // Implementation of the inherited abstract print method
    void print() const override;
};

#endif  // CARGO_H
