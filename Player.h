//
// Created by eros on 10/10/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_PLAYER_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_PLAYER_H


#include "Room.h"

class Player {
public:
    Player();
    Player(Room* room);
    void move_to(int direction);
    Room* get_current_room();
private:
    Room* current_room = NULL;
};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_PLAYER_H
