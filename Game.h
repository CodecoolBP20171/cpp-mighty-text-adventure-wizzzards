#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include <vector>
#include "Area.hpp"
#include "Room.h"
#include "Player.h"

using namespace std;

enum direction{NORTH, EAST, SOUTH, WEST};

class Game {
public:
    void init();
    void run();

private:
    vector<Area> areas; // areas has only non-changeable information
    vector<Room> rooms;
    vector<string> dirs = {"North", "East", "South", "West"};
    Player player;

    void loadAreas();
    void loadRooms();
    void setPlayer(Player player);
    string get_directions();
    void connect_rooms(int room_number, Room* n_room, Room* e_room, Room* s_room, Room* w_room);
    bool step();
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
