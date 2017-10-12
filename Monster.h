//
// Created by eros on 12/10/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_MONSTER_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_MONSTER_H

#include "Room.h"

class Monster {
public:
    Monster();
    Monster(Room* room, string name);
    void move_to(int direction);
    Room* get_current_room();
    string get_name();
    void set_description(string description);
    string get_description();

private:
    Room* current_room = NULL;
    string name;
    string description;
};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_MONSTER_H
