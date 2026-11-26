// Name: Jaden Salinas
// Summary: generate the 3 floors and the 3x3 grid
// keeps track of player

#include "Map.h"
#include "Combat.h"
#include "TreasureChest.h"
#include "Items.h"
#include <iostream>
#include <cstdlib>

// creating the Map
// first loads possible event for room


Map::Map()
    : currentFloor(NUM_FLOORS - 1), currentRow(0), currentCol(0), previousRow(0), previousCol(0) {

    // 1) Load every possible room event from setEvents.csv
    std::vector<std::vector<std::string>> rows = readCsvFile("data/setEvents.csv");
    for (const std::vector<std::string>& row : rows) {
        bool badCombat   = (row[0] == "Combat"   && row.size() < 6);
        bool badTreasure = (row[0] == "Treasure" && row.size() < 7);
        if (badCombat || badTreasure) {
            std::cerr << "Warning: skipping bad line in setEvents.csv for " << row[0] << "\n"; 
        }
        else {
            eventTable.push_back(row):
        }
    }

    bossRow = {"Combat", "Boss", "50", "90", "100", "10"}; // used if the file is missing
    std::vector<std::vector<std::string>> enemies = readCsvFile("data/setEnemies.csv");
    for (const std::vector<std::string>& row : enemies) {
        if (row.size() >= 5 && row[0] == "Boss") {
            bossRow = {"Combat", "Boss", row[1], row[2], row[3], row[4]};
        }
    }

    // 3) Make an empty grid: NUM_FLOORS floors of ROWS x COLS rooms
    grid.resize(NUM_FLOORS, std::vector<std::vector<Room*>>(ROWS, std::vector<Room*>(COLS)));

    // 4) Build each floor from the bottom (floor 2) to the top (floor 0).
    //    The stairs on one floor lead to the same spot on the floor above.
    int startRow = 0;
    int startCol = 0;
    for (int floor = NUM_FLOORS - 1; floor >= 0; floor--) {
        // Put the stairs somewhere at least 3 steps away from the start
        int stairsRow, stairsCol;
        do {
            stairsRow = rand() % ROWS;
            stairsCol = rand() % COLS;
        } while (abs(stairsRow - startRow) + abs(stairsCol - startCol) < 3);

        generateFloor(floor, startRow, startCol, stairsRow, stairsCol);

        startRow = stairsRow;
        startCol = stairsCol;
    }
}

// Map destructor.
// Deletes every room in the dungeon (each room then deletes its own event).
Map::~Map() {
    for (int f = 0; f < NUM_FLOORS; f++)
        for (int r = 0; r < ROWS; r++)
            for (int c = 0; c < COLS; c++)
                delete grid[f][r][c];
}

// Builds one floor of rooms.
//   - the start room is always empty (safe)
//   - the stairs room gets the stairs (and the Boss on floor 0)
//   - every other room gets a random event from setEvents.csv
void Map::generateFloor(int floor, int startRow, int startCol, int stairsRow, int stairsCol) {
    for (int r = 0; r < ROWS; r++) {
        for (int c = 0; c < COLS; c++) {
            Room* room = new Room();

            if (r == startRow && c == startCol) {
                // The room you arrive in is always safe and empty
            } else if (r == stairsRow && c == stairsCol) {
                room->setStairs(true);
                // On the last floor the Boss guards the exit
                if (floor == 0) {
                    room->setEvent(createEvent(bossRow));
                }
            } else {
                room->setEvent(createRandomEvent());
            }

            grid[floor][r][c] = room;
        }
    }
}

// Turns one line of setEvents.csv into an event.
//   "Combat"   line -> a CombatEvent (a fight)
//   "Treasure" line -> a TreasureChest holding that item
//   "Nothing"  line -> an EmptyEvent (empty room)
Event* Map::createEvent(const std::vector<std::string>& row) {
    // Combat line:   Combat,Name,Attack,Accuracy,HP,MinDamage
    if (row[0] == "Combat") {
        return new CombatEvent(row[1],
                               std::atoi(row[2].c_str()),
                               std::atoi(row[3].c_str()),
                               std::atoi(row[4].c_str()),
                               std::atoi(row[5].c_str()));
    }

    // Treasure line: Treasure,Name,HP,Attack,Accuracy,Luck,Evasion  (same stats as lootPool.csv)
    if (row[0] == "Treasure") {
        Item item(row[1],
                  std::atoi(row[2].c_str()),
                  std::atoi(row[3].c_str()),
                  std::atoi(row[4].c_str()),
                  std::atoi(row[5].c_str()),
                  std::atoi(row[6].c_str()));
        return new TreasureChest(item);
    }

    // "Nothing" line = empty room
    return new EmptyEvent();
}

// Picks a random event for a room.
// First picks the kind of room (40% Combat, 35% Treasure, 25% Nothing),
// then picks a random line of that kind from setEvents.csv.
Event* Map::createRandomEvent() {
    // Pick what kind of room this is: 40% Combat, 35% Treasure, 25% Nothing
    int roll = rand() % 100;
    std::string type;
    if (roll < 40)      type = "Combat";
    else if (roll < 75) type = "Treasure";
    else                type = "Nothing";

    // Find every line in setEvents.csv with that type...
    std::vector<int> matches;
    for (int i = 0; i < (int)eventTable.size(); i++) {
        if (eventTable[i][0] == type) {
            matches.push_back(i);
        }
    }
    if (matches.empty()) return new EmptyEvent();

    // ...and pick one of them at random
    int pick = matches[rand() % matches.size()];
    return createEvent(eventTable[pick]);
}

// Moves the player to (newRow, newCol) on the current floor.
// Remembers the old room so goBack() can return to it.
// Returns false (and does not move) if that spot is outside the floor (a wall).
bool Map::moveTo(int newRow, int newCol) {
    if (newRow < 0 || newRow >= ROWS || newCol < 0 || newCol >= COLS) {
        return false; // wall
    }
    previousRow = currentRow;
    previousCol = currentCol;
    currentRow = newRow;
    currentCol = newCol;
    return true;
}

// The four movement directions (w/a/s/d). Each returns false if there is a wall.
bool Map::moveUp()    { return moveTo(currentRow - 1, currentCol); }
bool Map::moveDown()  { return moveTo(currentRow + 1, currentCol); }
bool Map::moveLeft()  { return moveTo(currentRow, currentCol - 1); }
bool Map::moveRight() { return moveTo(currentRow, currentCol + 1); }

// Sends the player back to the room they just came from (used when running away).
void Map::goBack() {
    currentRow = previousRow;
    currentCol = previousCol;
}

// Moves the player up one floor (2 -> 1 -> 0).
// The player arrives in the same row/col on the floor above.
void Map::climbStairs() {
    if (currentFloor > 0) {
        currentFloor--;
        // You arrive at the same row/col on the floor above
        previousRow = currentRow;
        previousCol = currentCol;
    }
}

// Returns the room the player is standing in right now.
Room& Map::getCurrentRoom() {
    return *grid[currentFloor][currentRow][currentCol];
}
