#ifndef SHIP_H
#define SHIP_H

#include <string>

enum shipType { cruise, cargo };  // Declare the enum here

class Ship {
private:
    std::string shName;
    int shYear;
    shipType shType;

public:
    Ship(const std::string& name, int year, shipType type);
    virtual ~Ship() {}

    // Getter and Setter for ship name
    void setShName(const std::string& name);
    std::string getShName() const;

    // Getter and Setter for ship year
    void setShYear(int year);
    int getShYear() const;

    // Getter for ship type
    shipType getShType() const;

    // Abstract print method
    virtual void print() const = 0;
};

#endif  // SHIP_H
