#include <iostream>
#include "Game.h"

void Game::init()
{
    loadAreas();
    loadRooms();
}

void Game::loadAreas()
{
    areas.emplace_back("start room");
    areas.emplace_back("room 1");
    areas.emplace_back("room 2");
    areas.emplace_back("room 3");
    areas.emplace_back("room 4");
    areas.emplace_back("room 5");
    areas.emplace_back("room 6");
}

void Game::loadRooms() {
    // First init the rooms
    rooms.emplace_back(&areas[0]);
    rooms.emplace_back(&areas[1]);
    rooms.emplace_back(&areas[2]);
    rooms.emplace_back(&areas[3]);
    rooms.emplace_back(&areas[4]);
    rooms.emplace_back(&areas[5]);
    rooms.emplace_back(&areas[6]);
    rooms.emplace_back(&areas[7]);

    // Call connections to every room. args: (room_number, North, East, South, West)
    // Maybe we should not set connection details to the last room.
    connect_rooms(0, nullptr, nullptr, nullptr, &rooms[1]);
    connect_rooms(1, nullptr, &rooms[0], &rooms[2], nullptr);
    connect_rooms(2, &rooms[1], &rooms[2], nullptr, nullptr);
    connect_rooms(3, nullptr, &rooms[4], nullptr, &rooms[2]);
    connect_rooms(4, &rooms[5], nullptr, nullptr, &rooms[3]);
    connect_rooms(5, &rooms[6], nullptr, &rooms[4], nullptr);
    connect_rooms(6, &rooms[7], nullptr, &rooms[5], nullptr);
}

void Game::run()
{
    std::cout << "this is the next room N: "<< rooms[0].get_next_room(direction::NORTH) << std::endl;

    while(!step()){}
}

bool Game::step()
{
    return true;
}

void Game::connect_rooms(int room_number, Room* n_room, Room* e_room, Room* s_room, Room* w_room) {
    Room* direc[4];
    direc[direction::NORTH] = n_room;
    direc[direction::EAST] = e_room;
    direc[direction::SOUTH] = s_room;
    direc[direction::WEST] = w_room;

    Room** p_dir = &direc[0];

    rooms[room_number].set_connected_rooms(p_dir, sizeof(direc)/sizeof(direc[0]));
}
