//
// Created by eros on 12/10/17.
//

#include "Monster.h"

Monster::Monster() {
    current_room = nullptr;
}

Monster::Monster(Room* room, string name) {
    current_room = room;
    this->name = name;
}

void Monster::move_to(int direction) {
    current_room = current_room->get_next_room(direction);
}

Room *Monster::get_current_room() {
    return current_room;
}

string Monster::get_name() {
    return name;
}

void Monster::set_description(string description) {
    this->description = description;
}

string Monster::get_description() {
    return description;
}
