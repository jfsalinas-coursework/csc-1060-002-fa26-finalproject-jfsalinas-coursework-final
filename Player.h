// Player.h File
// Jaden Salinas
// Holds player class, it will be from 3 choices. It will also hold stats like HP, Attack Strength, Attack Accuracy, luck, and evasion.
// Stats will be loaded from the data-Cstats.csv file. Player can heal, take damamge and get more stats from Items.

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    std::string name;
    std::string className;
    int hp;
    int maxHp;
    int attackStrength;
    int attackAccuracy; // is a % chance to hit
    int luck; // Used when trying to open chest
    int evasion; // % chance to dodge attacks

public:
    Player (std::string n);

    
    bool loadClass(const std::string& chosenClass);

    // getters
    std::string getName() const { return name; }
    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    int getAttackStrength() const { return attackStrength; }
    int getAttackAccuracy() const { return attackAccuracy; }
    int getLuck() const { return luck; }
    int getEvasion() const { return evasion; }

    // Actions applied to player

    void takeDamage (int damage);
    void heal (int heal);
    void addStats ( int atk, int acc, int lck, int eva );
    void displayStats () const;
    bool isAlive () const { return hp > 0; }

};

#endif 