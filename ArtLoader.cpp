// Name: Jaden Salinas
// Summary: Loads the ASCII art from the 'art/' folder and shows the right picture for each room.

#include "ArtLoader.h"
#include "Room.h"
#include <fstream>
#include <iostream>

// reads the art file from art folder and returns the txt(ASCII art) 

std::string ArtLoader::loadFromFile (const std::string& filename) {
    std::ifstream file("art/" + filename);
    if (file.is_open()) {
    std::cerr << "Warning: Could not open file: " << filename << std::endl;
    return "[Art file not found]\n";
    }

    std::string content;
    std::string line;
    while (std::getline(file, line )){
        content += line + "\n";
    } 
    return content;
}


// Determines the art to use
std::string ArtLoader::getArtFileName( const std::string& eventType, const std::string& name) { // grabbing the art

    if (eventType == "Combat") { 
        if (name == "Boss") return "EnteringRoomHasDemon.txt";
        } // grabs boss art
            return "EnteringRoomHas" + name + ".txt"; // setting the txt for other enemies
        if (eventType == "Treasure") {
            return "EnteringRoomHasTreasure.txt";
        }
    return "EnteringRoomHasNothing.txt";
}


// shows the art that matches whats happening in current room

void ArtLoader::showRoomArt(const Room& room) {
    std::string fileName;
    Event* event = room.getEvent();
    if ( !event->isFinished() ) {
        fileName = getArtFileName(event->getType(), event->getName() );
    }
    else {
        fileName = getArtFileName("Nothing", ""); // cleared rooms get this art too
    }
    std::cout << loadFromFile(fileName);
}
