// Name: Jaden Salinas
// A room with a locked treasure chest. The player gets 3 tries to open it,
// and luck makes each try more likely to work.

#include "TreasureChest.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

// TreasureChest constructor.
// Makes a "Treasure" event named after the item inside.
// The chest starts locked with 3 tries to open it.
TreasureChest::TreasureChest(Item chestItem)
    : Event("Treasure", chestItem.getName()), item(chestItem), locked(true), attemptsToUnlock(3) {}

// One try at opening the lock.
// Chance to open = 60% + 1% for each point of the player's luck.
// Returns true if the chest opened. A failed try uses up one attempt.
bool TreasureChest::attemptUnlock(int playerLuck) {
    // 60% base chance + 1% per point of luck
    int chance = 60 + playerLuck;
    if (rand() % 100 < chance) {
        locked = false;
        return true;
    }
    attemptsToUnlock--;
    return false;
}

// Runs the chest room.
// Asks if the player wants to open the chest. If yes, keeps trying until it
// opens (the player gets the item) or the tries run out (the lock breaks).
// Saying no leaves the chest so the player can come back later.
// Always returns true (you can't run away from a chest).
bool TreasureChest::process(Player& player) {
    std::cout << "\nYou found a treasure chest!\n";
    char choice = getChoice("Try to open it? (y/n): ");

    if (choice != 'y') {
        std::cout << "You leave the chest alone for now.\n";
        return true; // you can come back later
    }

    // Keep trying until it opens or we run out of attempts
    while (locked && attemptsToUnlock > 0) {
        if (attemptUnlock(player.getLuck())) {
            std::cout << "*Click* The chest opens!\n";
        } else {
            std::cout << "The lock won't budge... (" << attemptsToUnlock << " tries left)\n";
        }
    }

    if (!locked) {
        std::cout << "Inside you find: " << item.getName() << "\n";
        item.applyToPlayer(player);
    } else {
        std::cout << "The lock breaks. This chest can never be opened.\n";
    }

    finished = true; // the chest is now empty either way
    return true;
}