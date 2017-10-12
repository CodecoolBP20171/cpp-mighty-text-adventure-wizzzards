//
// Created by eros on 10/10/17.
//
#include "Player.h"

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
    sum_item_weight -= item->get_weight();
    cout << "You dropped " << item->get_name() << "." << endl;
}

void Player::pick_item(Item *item) {
    if(MAX_INVENTORY_WEIGHT >= sum_item_weight + item->get_weight()) {
        current_room->remove_item(item);
        inventory.push_back(item);
        sum_item_weight += item->get_weight();
        cout << "You picked up the " << item->get_name() << "." <<endl;
    } else {
        cout << "This is too heavy, you have to throw something to pick this up." << endl;
    }
}

vector<Item *> Player::get_inventory() {
    return inventory;
}

void Player::set_player_helping_monster(bool b) {
    is_player_helping_monster = b;
}

bool Player::get_player_helping_monster() {
    return is_player_helping_monster;
}
