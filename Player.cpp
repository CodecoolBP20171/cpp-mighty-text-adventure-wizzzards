//

#include "Player.h"

//
// Created by eros on 10/10/17.

Player::Player() {
    current_room = nullptr;
}

Player::Player(Room* room) {
    current_room = room;
}

void Player::move_to(int direction) {
    current_room = current_room->get_next_room(direction);
}

Room* Player::get_current_room() {
    return current_room;
}
