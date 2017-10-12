#ifndef CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
#define CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H

#include "Player.h"
#include "Monster.h"


using namespace std;

enum direction{NORTH, EAST, SOUTH, WEST};

class Game {
public:
    void init();
    void run();

private:
    const vector<string> possible_direction = {"North", "East", "South", "West"};
    const vector<string> actions = {"Help", "Pick up ", "Inventory", "Throw "};
    vector<Area> areas; // areas has only non-changeable information
    vector<Room> rooms;
    vector<Item> items;
    vector<Monster> monsters;
    vector<Obstacle> obstacles;
    Player player;


    void loadAreas();
    void loadItems();
    void loadRooms();
    void setPlayer(Player player);
    void connect_rooms(int room_number, Room* n_room, Room* e_room, Room* s_room, Room* w_room);
    void addItemsToRooms();
    void loadObstacles();
    void obstacles_to_rooms(int room_number, Obstacle* to_north, Obstacle* to_east, Obstacle* to_south, Obstacle* to_west);
    string get_directions();
    bool step();
    void check_user_input(string& user_input);
    void print_room_items();

    void setMonsters(Monster monster);

    void print_room_monsters();
};


#endif //CPP_2ND_TW_MIGHTY_TEXT_ADVENTURE_GAME_H
