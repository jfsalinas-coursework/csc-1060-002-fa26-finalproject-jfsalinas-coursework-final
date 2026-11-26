// Jaden Salinas
// Summary: loads ASCII art from art folder. Displays the art based on the event that happens in the room.

#ifndef ART_LOADER_H
#define ART_LOADER_H

#include <string>


class Room;

class ArtLoader {

public: 

    static std::string loadFromFile(const std::string& filename); // loads art fromt art folder
    static std::string getArtFileName(const std::string& eventType, const std::string& name);  // loads the type of art based on event type
    static void showRoomArt( const Room& room); // shows the art

};

#endif
