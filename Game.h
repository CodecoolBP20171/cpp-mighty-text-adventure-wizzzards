#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include <algorithm>
#include "Player.h"
#include "Monster.h"
#include "UserInterface.h"


using namespace std;

enum direction{NORTH, EAST, SOUTH, WEST};

class Game {
public:
    void init();
    void run();

private:
    vector<Area> areas; // areas has only non-changeable information
    vector<Obstacle> obstacles;
    vector<Item> items;
    vector<Room> rooms;
    vector<Monster> monsters;
    Player player;
    UserInterface ui;


    void loadAreas();
    void loadObstacles();
    void loadItems();
    void loadRooms();
    void connect_rooms(int room_number,
                       Room* n_room, Room* e_room, Room* s_room, Room* w_room);
    void addItemsToRooms();
    void obstacles_to_rooms(int room_number,
                            Obstacle* to_north, Obstacle* to_east, Obstacle* to_south, Obstacle* to_west);
    void setPlayer(Player player);
    void setMonsters(Monster monster);
    bool step();

};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
