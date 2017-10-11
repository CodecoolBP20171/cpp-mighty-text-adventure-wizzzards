//

#include "Player.h"

//
// Created by eros on 10/10/17.
const int Player::MAX_INVENTORY_WEIGHT = 100;

Player::Player() {
    current_room = nullptr;
    sum_item_weight = 0;
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

void Player::throw_item(Item *item) {
    int position = 0;
    for(auto &inventory_item : inventory){
        if(inventory_item == item){
            break;
        }
        ++position;
    }
    inventory.erase(inventory.begin()+position);
    current_room->add_items(item);
}

void Player::pick_item(Item *item) {
    current_room->remove_item(item);
    inventory.push_back(item);
}
