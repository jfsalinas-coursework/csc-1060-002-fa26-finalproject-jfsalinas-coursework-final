// Jaden Salinas
// Summary: Used for items that appear in the treasure chest. can heal and stats are added to player stats permantly

#ifndef ITEMS_H
#define ITEMS_H

#include <string>

class Player; 

class Item {

private: 
    std::string name;
    int hpEffect;
    int attackStrengthEffect;
    int attackAccuracyEffect;
    int luckEffect;
    int evasionEffect;

public:
    Item(std::string n, int h, int a, int ac, int l, int e);

    void applyToPlayer( Player& player );
    std::string getName() const {return name;}

};

#endif
