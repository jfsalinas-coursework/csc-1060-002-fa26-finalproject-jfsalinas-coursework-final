// Name: Jaden Salinas
// Program RNG Dungeon Crawler
// text based Dungeon Crawler with included ascii artd

#include <iostream>
#include <string>
#include <cstdlib>
#include "Map.h"
#include "Player.h"
#include "ArtLoader.h"

// The game starts here.
//   1) Character creation: the player types a name and picks a class
//   2) The player picks a dungeon number (1-100), which builds the dungeon
//   3) Main game loop: each time round, the player enters a room, the room's
//      event runs, and the player picks where to go next
// The game ends when the player wins (climbs the stairs on floor 0),
// dies, or quits.
int main() {
    // ---------------- Character creation ----------------
    std::cout << "Welcome to the Dungeon Crawler!\n";
    std::cout << "You wake up on Floor 2, deep underground.\n";
    std::cout << "Find the stairs on each floor and climb up to Floor 0.\n";
    std::cout << "Climb the final stairs on Floor 0 to escape and win!\n\n";

    std::string playerName;
    std::cout << "Enter your name: ";
    if (!std::getline(std::cin, playerName)) return 0;
    if (playerName.empty()) playerName = "Hero";

    Player player(playerName);

    // Class names must match the names in cStats.csv
    bool classChosen = false;
    while (!classChosen) {
        std::cout << "\nChoose your class:\n";
        std::cout << "  1) Fighter - lots of HP\n";
        std::cout << "  2) Mage    - hits hard, low HP\n";
        std::cout << "  3) Rogue   - lucky and hard to hit\n";
        char choice = getChoice("Enter 1, 2 or 3: ");

        std::string className;
        if (choice == '1')      className = "Fighter";
        else if (choice == '2') className = "Mage";
        else if (choice == '3') className = "Rogue";
        else {
            std::cout << "Invalid choice.\n";
            continue;
        }

        if (!player.loadClass(className)) {
            std::cout << "Could not find " << className << " in cStats.csv.\n";
            return 1;
        }
        classChosen = true;
    }

    std::cout << "\n--- Character Created ---\n";
    player.displayStats();

    // ---------------- Pick the dungeon ----------------
    // Let the player pick which dungeon to play (this number is the seed)
    int seed = 0;
    while (seed < 1 || seed > 100) {
        std::cout << "\nPick a dungeon number (1-100): ";
        std::string line;
        if (!std::getline(std::cin, line)) return 0;   // input closed
        seed = std::atoi(line.c_str());                // "42" -> 42, not a number -> 0
        if (seed < 1 || seed > 100) {
            std::cout << "Please enter a number from 1 to 100.\n";
        }
    }
    srand(seed); // seed random numbers ONCE: same number = same dungeon every time

    Map dungeon; // builds floors 2, 1 and 0 (must come AFTER srand)

    // ---------------- Main game loop ----------------
    // Each time round this loop the player has just entered a room.
    bool playing = true;
    while (playing) {
        Room& room = dungeon.getCurrentRoom();

        // Remember if we had been here BEFORE marking the room as visited
        bool alreadyVisited = room.isVisited();
        room.setVisited(true);

        // 1) Show the art for this room
        std::cout << "\n";
        ArtLoader::showRoomArt(room);
        std::cout << "\n========== Floor " << dungeon.getCurrentFloor()
                  << " - Room (" << dungeon.getCurrentRow() << "," << dungeon.getCurrentCol()
                  << ") ==========\n";
        std::cout << "HP: " << player.getHp() << "/" << player.getMaxHp() << "\n";

        if (alreadyVisited) std::cout << "This room has been explored.\n";
        else                std::cout << "This room is new.\n";

        // 2) Run the room's event (fight, chest or empty room) if it is not done yet
        Event* event = room.getEvent();
        if (!event->isFinished()) {
            bool stayed = event->process(player);

            if (!player.isAlive()) {
                std::cout << "\n*** GAME OVER - you have died. ***\n";
                break;
            }
            if (!stayed) {
                dungeon.goBack(); // player ran away
                continue;         // show the previous room again
            }
        } else {
            std::cout << "This room has already been cleared.\n";
        }

        // 3) Stairs: ask right away if the player wants to climb them
        if (room.hasStairs()) {
            if (dungeon.getCurrentFloor() == 0)
                std::cout << "Daylight shines down these stairs - this is the way OUT!\n";
            else
                std::cout << "There is a staircase here leading up to Floor "
                          << dungeon.getCurrentFloor() - 1 << ".\n";

            char climb = getChoice("Climb the stairs? (y/n): ");
            if (climb == 'y') {
                if (dungeon.getCurrentFloor() == 0) {
                    std::cout << "\nYou climb the final stairs and step out into the sunlight...\n";
                    std::cout << "*** YOU ESCAPED THE DUNGEON! YOU WIN, " << player.getName() << "! ***\n";
                    break; // game over - the player won
                }
                dungeon.climbStairs();
                player.heal(player.getMaxHp()); // rest on the stairs
                std::cout << "\nYou climb up to Floor " << dungeon.getCurrentFloor()
                          << " and rest on the way. HP fully restored!\n";
                continue; // show the room at the top of the stairs
            }
            std::cout << "You stay on this floor for now.\n";
        }

        // 4) Ask what to do until the player leaves this room
        bool leftRoom = false;
        while (!leftRoom) {
            char choice = getChoice("\nMove with w(up)/a(left)/s(down)/d(right)  (1)info, (2)quit: ");

            if (choice == 'w' || choice == 'a' || choice == 's' || choice == 'd') {
                bool moved = false;
                if (choice == 'w') moved = dungeon.moveUp();
                if (choice == 'a') moved = dungeon.moveLeft();
                if (choice == 's') moved = dungeon.moveDown();
                if (choice == 'd') moved = dungeon.moveRight();

                if (moved) leftRoom = true;
                else std::cout << "You bump into a wall.\n";
            }
            else if (choice == '1') {
                player.displayStats();
            }
            else if (choice == '2') {
                std::cout << "You gave up. Goodbye!\n";
                playing = false;
                leftRoom = true;
            }
            else {
                std::cout << "Unknown command.\n";
            }
        }
    }

    return 0;
}