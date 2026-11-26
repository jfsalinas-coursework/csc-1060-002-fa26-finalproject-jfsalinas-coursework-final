// Jaden Salinas
// Summary: Holds one enemy name stats, like HP, accuracy, and minimum,max Damage.
// stats come from setEvents.csv and setEnemies 

#ifndef ENEMY_H
#define ENEMY_H

#include <string>



class Enemy {
private:
    std::string name;
    int hp;
    int maxHp;
    int attackStrength;
    int minDamage; // Determines the min. amount of dmg enemy can do
    int accuracy; // % chance to hit player


public:
    Enemy( std::string n, int atk, int acc, int hp, int minDmg);  // listed in the same order as in csv file

    void takeDamage( int damage);
    bool isAlive() const { return hp > 0; }

    int rollDamage() const; // used to chose random dmg from min to attackstrength
    int getHp() const {return hp; }
    int getMaxHp() const {return maxHp; }
    int getAccuracy() const {return accuracy; }

};

#endif
