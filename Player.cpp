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
    sum_item_weight = 0;
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
//    cout << "MAX: " << MAX_INVENTORY_WEIGHT <<
    if(MAX_INVENTORY_WEIGHT >= sum_item_weight + item->get_weight()) {
        current_room->remove_item(item);
        inventory.push_back(item);
        std::cout << "You picked up the" << item->get_name() << endl;
    } else {
        std::cout << "This is too heavy, you have to throw something to pick this up" << endl;
    }
}

vector<Item *> Player::get_inventory() {
    return inventory;
}
