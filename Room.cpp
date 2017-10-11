//
// Created by bekor on 10/9/17.
//

#include "Room.h"

Room::Room(Area* area) {
    this->area = area;
}

Area *Room::get_area() {
    return area;
}

void Room::set_connected_rooms(Room **conn_rooms, int conn_room_size) {
    for(int i = 0; i < conn_room_size; ++i){
//        if(*conn_rooms != nullptr){
//            std::cout << *conn_rooms << std::endl;
//        }
        connected_rooms[i] = *conn_rooms;
        ++conn_rooms;
    }
}

Room *Room::get_next_room(int room_number) {
    return connected_rooms[room_number];
}

void Room::add_items(Item* item) {
    room_items.push_back(item);
}

void Room::remove_item(Item *item) {
    int position = 0;
    for(auto &ite : room_items){
        if(ite == item){
            break;
        }
        ++position;
    }
    room_items.erase(room_items.begin()+position);
}

vector<Item *> Room::get_current_room_items() {
    return room_items;
}
