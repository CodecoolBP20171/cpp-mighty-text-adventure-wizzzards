//
// Created by bekor on 10/9/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ROOM_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ROOM_H

#include <vector>
#include "iostream"
#include "Area.hpp"
#include "Item.h"


class Room {
public:
    Room(Area* area);
    void set_connected_rooms(Room** conn_rooms, int conn_room_size);
    Room* get_next_room(int room_number);
    Area* get_area();
    void add_items(Item* item);
    void remove_item(Item* item);
    vector<Item*> get_current_room_items();


private:
    Room* connected_rooms[4];
    Area* area;
    vector<Item*> room_items;
};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ROOM_H
