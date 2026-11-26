// Jaden Salinas
// Summary: Happens when a room is a Treasure Event. Chest holds one item
// Player gets 3 attempts to unlock
// Includes event and items.

#ifndef TREASURE_CHEST_H
#define TREASURE_CHEST_H

#include <string>
#include "Event.h"
#include "Items.h"



class TreasureChest : public Event {
private:
    Item item;
    bool locked;
    int attemptsToUnlock; // how many tries before the lock breaks


public:
    TreasureChest (Item chestItem );
    bool process( Player& player) override; // ask if player wants to open chest
    bool attemptUnlock ( int playerLuck);  // the attempt to open chest

};

#endif
