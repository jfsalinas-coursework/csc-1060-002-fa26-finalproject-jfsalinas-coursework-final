// Name: Jaden Salinas
// A room with an enemy in it. The player can attack or run away.

#include "Combat.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>

// CombatEvent constructor.
// Makes a "Combat" event and creates the enemy with the given stats.
CombatEvent::CombatEvent(std::string enemyName, int atk, int acc, int hp, int minDmg)
    : Event("Combat", enemyName), enemy(enemyName, atk, acc, hp, minDmg) {}

// Runs the fight, one round at a time, until someone wins or the player runs.
//   Each round:  1) the player chooses (a)ttack or (r)un away
//                2) the player attacks (uses the player's accuracy)
//                3) the enemy attacks back (enemy accuracy, then player evasion)
// Returns false if the player ran away, true otherwise (won or died).
bool CombatEvent::process(Player& player) {
    std::cout << "\n--- A " << name << " blocks your path! ---\n";

    while (player.isAlive() && enemy.isAlive()) {
        std::cout << "\nYour HP: " << player.getHp() << "/" << player.getMaxHp()
                  << "   " << name << " HP: " << enemy.getHp() << "/" << enemy.getMaxHp() << "\n";

        char choice = getChoice("(a)ttack or (r)un away? ");

        if (choice == 'r') {
            // Running away: the enemy ALWAYS gets one swing at you.
            // Your evasion is the % chance that it misses.
            std::cout << "You turn and run...\n";
            if (rand() % 100 < player.getEvasion()) {
                std::cout << "You dodge the " << name << "'s attack as you escape!\n";
            } else {
                int damage = enemy.rollDamage();
                player.takeDamage(damage);
                std::cout << "The " << name << " hits you for " << damage << " damage as you flee!\n";
                if (!player.isAlive()) {
                    std::cout << "\nYou were defeated by the " << name << "...\n";
                    return true; // main() sees the player is dead
                }
            }
            std::cout << "You run back to the room you came from!\n";
            return false; // the enemy stays here (with its current HP)
        }
        if (choice != 'a') {
            std::cout << "Please type a or r.\n";
            continue;
        }

        // ----- Player's turn -----
        if (rand() % 100 < player.getAttackAccuracy()) {
            enemy.takeDamage(player.getAttackStrength());
            std::cout << "You hit the " << name << " for " << player.getAttackStrength() << " damage!\n";
        } else {
            std::cout << "You missed!\n";
        }

        if (!enemy.isAlive()) break;

        // ----- Enemy's turn -----
        if (rand() % 100 >= enemy.getAccuracy()) {
            std::cout << "The " << name << " attacks but misses!\n";
        } else if (rand() % 100 < player.getEvasion()) {
            std::cout << "You dodge the " << name << "'s attack!\n";
        } else {
            // Damage is random from the enemy's min damage up to its attack strength
            int damage = enemy.rollDamage();
            player.takeDamage(damage);
            std::cout << "The " << name << " hits you for " << damage << " damage!\n";
        }
    }

    // ----- The fight is over -----
    if (player.isAlive()) {
        std::cout << "\nYou defeated the " << name << "!\n";
        player.heal(10); // small reward so the dungeon stays beatable
        std::cout << "You catch your breath (+10 HP). HP: " // change this late to a smaller amount
                  << player.getHp() << "/" << player.getMaxHp() << "\n";
        finished = true;
    } else {
        std::cout << "\nYou were defeated by the " << name << "...\n";
    }
    return true;
}