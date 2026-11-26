// Name: Jaden Salians
// One room of the dungeon. A room holds one event (a fight, a chest,
// or an EmptyEvent) and remembers if it has stairs and if it was visited.

#include "Room.h"

// Room constructor.
// A new room starts empty, unvisited and without stairs.
// The Map replaces the EmptyEvent with a fight or chest if needed.
Room::Room() : event(new EmptyEvent()), visited(false), stairs(false) {}

// Room destructor.
// The room owns its event, so it deletes it when the room is deleted.
Room::~Room() {
    delete event; // free the room's event
}

// Puts a new event in the room.
// The old event is deleted first so no memory is leaked.
void Room::setEvent(Event* e) {
    delete event; // remove any old event first
    event = e;
}