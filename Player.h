//
// Created by eros on 10/10/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_PLAYER_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_PLAYER_H


#include "Room.h"
#include "Item.h"

class Player {
public:
    Player();
    Player(Room* room);
    void move_to(int direction);
    Room* get_current_room();
    void pick_item(Item* item);
    void throw_item(Item* item);
    vector<Item*> get_inventory();
    void set_player_helping_monster(bool b);
    bool get_player_helping_monster();

private:
    Room* current_room = NULL;
    vector<Item*> inventory;
    const static int MAX_INVENTORY_WEIGHT;
    int sum_item_weight;
    bool is_player_helping_monster = false;
};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_PLAYER_H
