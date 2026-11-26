// Name: Jaden Salinas
// The Event base class, the EmptyEvent class, and two helper functions
// (getChoice and readCsvFile) that the rest of the game uses.

#include "Event.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>

// Event constructor.
// Stores the event's type ("Combat", "Treasure" or "Empty") and name.
// Every event starts NOT finished.
Event::Event(std::string t, std::string n) : type(t), name(n), finished(false) {}


// EmptyEvent constructor.
// An empty room has the type "Empty" and no name.
EmptyEvent::EmptyEvent() : Event("Empty", "") {}

// Runs the empty room: just tells the player there is nothing here.
// Returns true because the player stays in the room.
bool EmptyEvent::process(Player&) {
    std::cout << "The room is empty.\n";
    return true; // the player stays in the room (never "finished", so this shows every visit)
}

// Shows a prompt and reads one line from the player.
// Returns the first letter they typed in lowercase (e.g. "W" -> 'w'),
// or ' ' if they just pressed Enter.
char getChoice(const std::string& prompt) {
    std::cout << prompt;
    std::string line;

    // If input is closed (e.g. Ctrl+D) end the game instead of looping forever
    if (!std::getline(std::cin, line)) {
        std::cout << "\nGoodbye!\n";
        std::exit(0);
    }

    // Return the first letter the player typed (ignoring spaces)
    for (char c : line) {
        if (!std::isspace((unsigned char)c)) {
            return (char)std::tolower((unsigned char)c);
        }
    }
    return ' '; // player just pressed Enter
}

// Reads a .csv file and returns it as a list of rows.
// Each row is a list of the fields between the commas.
//   Example line:  Goblin,10,70,30,3
//   Becomes:       {"Goblin", "10", "70", "30", "3"}
// Blank lines are skipped. Returns an empty list if the file can't be opened.
std::vector<std::vector<std::string>> readCsvFile(const std::string& filename) {
    std::vector<std::vector<std::string>> rows;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: could not open " << filename << "\n";
        return rows;
    }

    std::string line;
    while (std::getline(file, line)) {
        // Remove the '\r' that Windows puts at the end of lines
        if (!line.empty() && line[line.size() - 1] == '\r') {
            line.erase(line.size() - 1);
        }
        if (line.empty()) continue; // skip blank lines

        // Split the line on commas
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;
        while (std::getline(ss, field, ',')) {
            fields.push_back(field);
        }
        rows.push_back(fields);
    }
    return rows;
}