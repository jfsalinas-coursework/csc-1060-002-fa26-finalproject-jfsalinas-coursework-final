// Name: Jaden Salinas
// An item found inside a treasure chest. Using it heals the player
// and/or gives permanent stat bonuses.

#include "Items.h"
#include "Player.h"
#include <iostream>

// Item constructor.
// Stores the item's name and how much it changes each stat.
// Same order as setEvents.csv / lootPool.csv: HP, Attack, Accuracy, Luck, Evasion
Item::Item(std::string n, int h, int a, int ac, int l, int e)
    : name(n), hpEffect(h), attackStrengthEffect(a), attackAccuracyEffect(ac),
      luckEffect(l), evasionEffect(e) {}

// Uses the item on the player.
// HP heals the player; every other stat is added on permanently.
// Prints each bonus so the player can see what they got.
void Item::applyToPlayer(Player& player) {
    std::cout << "You use the " << name << "!\n";

    // HP on an item heals the player
    if (hpEffect > 0) {
        player.heal(hpEffect);
        std::cout << "  Healed " << hpEffect << " HP\n";
    }

    // Everything else is a permanent stat bonus
    player.addStats(attackStrengthEffect, attackAccuracyEffect, luckEffect, evasionEffect);
    if (attackStrengthEffect > 0) std::cout << "  Attack +" << attackStrengthEffect << "\n";
    if (attackAccuracyEffect > 0) std::cout << "  Accuracy +" << attackAccuracyEffect << "%\n";
    if (luckEffect > 0)           std::cout << "  Luck +" << luckEffect << "\n";
    if (evasionEffect > 0)        std::cout << "  Evasion +" << evasionEffect << "%\n";
}