// Jaden Salinas
// Summary: Creates the whole dungeon, 3 floors and a 3x3 on each floor.
// Fills rooms with events from setEvents.csv, and keeps track of where the player is.

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include "Room.h"

// Creating the Dungeon based on value below
// num_floors creates the floor, rows and cols creats the grid for each floor

const int NUM_FLOORS = 3; // for this  run through floors 2, 1 and 0. The player starts on floor 2 base on a value of 3.
const int ROWS = 3;       // rooms per floor = ROWS x COLS
const int COLS = 3;

class Map {

private:
    int currentFloor;
    int currentRow;
    int currentCol;
    int previousRow;  // where the player came from (used when running away)
    int previousCol;

    std::vector<std::vector<std::string>> eventTable; // lines of setEvents.csv
    std::vector<std::string> bossRow;                 // Boss stats from setEnmies.csv

    void generateFloor ( int floor, int startRow, int startCol, int stairsRow, int stairsCol);
    Event* createEvent(const std::vector<std::string>& row);
    Event* createRandomEvent();
    bool moveTo( int newRowm int newCol);

public:
    Map();  // builds all floors
    ~Map(); // deletes all rooms

    // Movement inside a floor. Return false if there is a wall.
    bool moveUp();
    bool moveDown();
    bool moveLeft();
    bool moveRight();

    void goBack();      // return to the previous room (after running away)
    void climbStairs(); // go up one floor for this run throught it will be (floor 2 -> 1 -> 0)

    Room& getCurrentRoom();
    int getCurrentFloor() const { return currentFloor; }
    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }

};

#endif
