// Jaden Salinas
// Summary: If a room has a enemy in it, Combat will be used. 
// Inherits from Event
// Players can either attack or run away

#ifndef COMBAT_H
#define COMBAT_H

#include <string>
#include "Event.h"
#include "Enemy.h"


class CombatEvent : public Event {
private:
    Enemy enemy; 

public:

    CombatEvent(std::string enemyName, int atk, int acc, int hp, int minDmg); // same order as setevents.csv 
    bool process ( Player& player ) override; // player fights until outcome or run away

};

#endif
