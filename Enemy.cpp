// Name: Jaden Salians
// An enemy the player fights. Its stats come from setEvents.csv
// (or setEnemies.csv for the Boss).

#include "Enemy.h"
#include <cstdlib>

// Enemy constructor.
// Sets up the enemy's stats. The enemy starts at full HP.
Enemy::Enemy(std::string n, int atk, int acc, int hp, int minDmg)
    : name(n), hp(hp), maxHp(hp), attackStrength(atk), minDamage(minDmg), accuracy(acc) {
    // Keep minDamage sensible: at least 1 and never more than the max
    if (minDamage < 1) minDamage = 1;
    if (minDamage > attackStrength) minDamage = attackStrength;
}

// Lowers the enemy's HP when the player hits it.
// HP never goes below 0.
void Enemy::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

// Picks how much damage this enemy's hit does.
// Returns a random number from minDamage up to attackStrength.
int Enemy::rollDamage() const {
    // e.g. min 3, max 10 -> 3 + (0 to 7) -> 3 to 10
    return minDamage + rand() % (attackStrength - minDamage + 1);
}