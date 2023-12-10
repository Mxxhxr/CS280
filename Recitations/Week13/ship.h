#ifndef SHIP_H
#define SHIP_H

#include <string>

// shipType defined globally

class Ship {
private:
    std::string shName;
    int shYear;
    shipType shType;

public:
    Ship(std::string name, int year, shipType type)
        : shName(name), shYear(year), shType(type) {}

    virtual ~Ship() {}

    // setters & getters
    void setShName(const std::string &name) { shName = name; }
    void setShYear(int year) { shYear = year; }
    void setShType(shipType type) { shType = type; }

    std::string getShName() const { return shName; }
    int getShYear() const { return shYear; }
    shipType getShType() const { return shType; }

    virtual void print() const = 0;
};

#endif