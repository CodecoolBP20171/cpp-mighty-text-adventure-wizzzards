//
// Created by bekor on 10/9/17.
//

#include "Room.h"

Room::Room(Area* area):area(area), connected_rooms(), room_obstacles() {
}

Area *Room::get_area() {
    return area;
}

void Room::set_connected_rooms(Room **conn_rooms, int conn_room_size) {
    for(int i = 0; i < conn_room_size; ++i){
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
    for(auto &room_item : room_items){
        if(room_item == item){
            break;
        }
        ++position;
    }
    room_items.erase(room_items.begin()+position);
}

vector<Item *> Room::get_current_room_items() {
    return room_items;
}

void Room::set_obstacle(Obstacle **obstacles, int conn_room_size) {
    for(int i = 0; i < conn_room_size; ++i){
        room_obstacles[i] = *obstacles;
        ++obstacles;
    }
}

Obstacle *Room::get_room_obstacles(int next_room_number) {
    return room_obstacles[next_room_number];
}

