// Jaden Salinas
// Summary: This is for ONE room. It holds a single event inside. these can be fight(combat), treasure chest, or empty
// also knows if it has stairs in it and if it has been visited before.

#ifndef ROOM_H
#define ROOM_H

#include "Event.h"



class Room {
private:
    Event* event; // checks whats in room
    bool visited; // checks if room has been vistied by player before
    bool stairs; // checks if there is stairs in the room

public:
    Room();
    ~Room(); // deletes event from the room

    Room ( const Room& ) = delete;
    Room& operator = ( const Room&) =  delete;

    void setEvent(Event* e);
    Event* getEvent() const { return event; }

    void setStairs(bool s) {stairs = s; }
    bool hasStairs() const { return stairs; }

    void setVisited(bool v) {visited = v; }
    bool isVisited() const { return visited; }


};

#endif
