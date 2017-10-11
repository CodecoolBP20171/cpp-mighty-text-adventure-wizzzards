#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include <vector>
#include "Area.hpp"
#include "Room.h"
#include "Player.h"
#include "Item.h"

using namespace std;

enum direction{NORTH, EAST, SOUTH, WEST};

class Game {
public:
    void init();
    void run();

private:
    const vector<string> possible_direction = {"North", "East", "South", "West"};
    const vector<string> actions = {"Help", "Pick up ", "Inventory"};
    vector<Area> areas; // areas has only non-changeable information
    vector<Room> rooms;
    vector<Item> items;
    Player player;

    void loadAreas();
    void loadRooms();
    void setPlayer(Player player);
    void loadItems();
    void addItemsToRooms();
    string get_directions();
    void connect_rooms(int room_number, Room* n_room, Room* e_room, Room* s_room, Room* w_room);
    bool step();
    void check_user_input(string& user_input);
    void print_room_items();
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
