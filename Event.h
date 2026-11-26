// Jaden Salinas
// Summary: Is the class that determines anything that can happen in a room. 
// CombatEvent and TreasureChest inherit this file
// EmptyEvent is only to start the rooms and to be the nothing in them event. 

#ifndef EVENT_H
#define EVENT_H

#include <string>
#include <vector>

class Player;

class Event {
protected:  // this had to be in protected
   std::string type; // determines if the event is combat, treasure, or empty
   std::string name; // grabs the enemy type and the item in the chest
   bool finished;
   

public:
   Event (std::string type, std::string name );
   virtual ~Event () {}
   virtual bool process ( Player& player) = 0;
   std::string getType() const { return type; }
   std::string getName() const { return name; }
   bool isFinished() const { return finished; }
};

class EmptyEvent : public Event { // Empty room
public:
EmptyEvent ();
bool process(Player& player ) override; // used to say room is empty
};

char getChoice(const std::string& prompt); // shows a prompt and reads line and get,returns first char

std::vector<std::vector<std::string>> readCsvFile(const std::string& filename); // reads csv and each line becomes a list.



#endif