/*
 * File:   PlayerClass.h
 * Author: Theopolis Armstrong
 * Created on May 29, 2019 3:10 AM
 * Purpose: Virtual Player class declaration
 */

#ifndef PLAYERCLASS_H
#define PLAYERCLASS_H

#include <cstdint>

enum Mapping {HIT = -2, MISS = -1, PATROL = 1, DESTROY, CARRIER}; //Map indications/ship size/ship health

std::ostream& operator<<(std::ostream&, const class PlayerClass*);
std::istream &operator>>(std::istream&, class PlayerClass*);

class PlayerClass{
protected:
    static const uint8_t SHIPNUM; //Number of available ship types
    static const uint8_t MAPMIN; //Minimum map size
    struct Coord{
        uint8_t x = 0;
        uint8_t y = 0;
    };
    
    std::string name; //Player name
    uint8_t size; //Map size
    int8_t **map; //Map status
    uint8_t health[3] = {PATROL, DESTROY, CARRIER}; //Ships' health
    
    void initMap();
    bool attack(PlayerClass&, const Coord&);
    bool testEnd(PlayerClass&) const;
public:
    //Constructors
    PlayerClass() : size(MAPMIN), name("Player") { initMap(); }
    PlayerClass(const std::string n) : size(MAPMIN), name(n) { initMap(); }
    PlayerClass(const uint8_t s) : size(s), name("Player") { initMap(); }
    PlayerClass(const uint8_t s, const std::string n) : size(s), name(n) { initMap(); }
    //Deconstructor
    virtual ~PlayerClass();
    
    //Mutators
    void setSize(uint8_t s) { size = s; }
    void setName(std::string n) { name = n; }
    void setHealth(const uint8_t ship, const uint8_t value) { health[ship] = value; }
    
    //Accessors
    uint8_t getSize() const { return size; }
    uint8_t getShipNum() const { return SHIPNUM; }
    std::string getName() const { return name; }
    const unsigned long int getNameLen() const { return name.length(); }
    uint8_t getHealth(const uint8_t shipType) const { return health[shipType-1]; } //Return the health of a particular ship
    
    void showMap() const; //Display the 2D map array as a map
    void debugMap() const; //Output the values of the map array
    
    //Pure virtual functions
    virtual void place(Mapping) = 0;
    virtual bool turn(PlayerClass*) = 0;
    
    //Overloaded operator
    int8_t* operator[](const int &);
    bool operator>(const PlayerClass&);
    bool operator<(const PlayerClass&);
    friend std::ostream& operator<<(std::ostream&, const class PlayerClass*);
    friend std::istream& operator>>(std::istream&, class PlayerClass*);
};

#endif /* PLAYERCLASS_H */
