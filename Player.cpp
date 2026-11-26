// Name: Jaden Salinas
// The player: their class stats (loaded from cStats.csv), HP, and
// everything that changes those stats during the game.

#include "Player.h"
#include "Event.h" // for readCsvFile()
#include <iostream>
#include <cstdlib>

// Player constructor.
// Stores the player's name. All stats start at 0 until loadClass() is called.
Player::Player(std::string n)
    : name(n), className("None"), hp(0), maxHp(0), attackStrength(0), attackAccuracy(0), luck(0), evasion(0) {}

// Loads the stats for the chosen class (Fighter, Mage or Rogue) from cStats.csv.
// The player starts at full HP.
// Returns false if the class is not in the file.
bool Player::loadClass(const std::string& chosenClass) {
    // cStats.csv format: ClassName,HP,Attack,Accuracy,Luck,Evasion
    std::vector<std::vector<std::string>> rows = readCsvFile("data/cStats.csv");

    for (const std::vector<std::string>& row : rows) {
        if (row.size() >= 6 && row[0] == chosenClass) {
            className      = row[0];
            maxHp          = std::atoi(row[1].c_str());
            hp             = maxHp;
            attackStrength = std::atoi(row[2].c_str());
            attackAccuracy = std::atoi(row[3].c_str());
            luck           = std::atoi(row[4].c_str());
            evasion        = std::atoi(row[5].c_str());  // had to figure out how to change 
            return true;
        }
    }
    return false; // class not in the file
}

// Lowers the player's HP when an enemy hits them.
// HP never goes below 0 (0 HP = dead).
void Player::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

// Raises the player's HP (after a fight, from a potion, or on the stairs).
// HP never goes above maxHp.
void Player::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}

// Adds permanent stat bonuses from an item.
// Accuracy is capped at 100% and evasion at 50%.
void Player::addStats(int atk, int acc, int lck, int eva) {
    attackStrength += atk;
    attackAccuracy += acc;
    luck += lck;
    evasion += eva;

    // Keep the percentages sensible
    if (attackAccuracy > 100) attackAccuracy = 100;
    if (evasion > 50) evasion = 50; // never become impossible to hit
}

// Prints all of the player's stats (used after picking a class and for (1)info).
void Player::displayStats() const {
    std::cout << "Name: " << name << "\n";
    std::cout << "Class: " << className << "\n";
    std::cout << "HP: " << hp << "/" << maxHp << "\n";
    std::cout << "Attack Strength: " << attackStrength << "\n";
    std::cout << "Attack Accuracy: " << attackAccuracy << "%\n";
    std::cout << "Luck: " << luck << "\n";
    std::cout << "Evasion: " << evasion << "%\n";
}