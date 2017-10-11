#include <iostream>
#include "Game.h"

void Game::init()
{
    loadAreas();
    loadItems();
    loadRooms();
    Player player(&rooms[0]);
    setPlayer(player);
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

void Game::loadItems() {
    items.emplace_back("key", 10, "This is a key");
    items.emplace_back("club", 50, "One handed weepon");
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
    connect_rooms(2, &rooms[1], &rooms[3], nullptr, nullptr);
    connect_rooms(3, nullptr, &rooms[4], nullptr, &rooms[2]);
    connect_rooms(4, &rooms[5], nullptr, nullptr, &rooms[3]);
    connect_rooms(5, &rooms[6], nullptr, &rooms[4], nullptr);
    connect_rooms(6, &rooms[7], nullptr, &rooms[5], nullptr);

    addItemsToRooms();
}

void Game::setPlayer(Player player) {
    this->player = player;
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

void Game::addItemsToRooms() {
    rooms[0].add_items(&items[0]);
    rooms[1].add_items(&items[1]);
}

void Game::run()
{
    string user_input;
    while(step()){
        std::cout << "You are in " << player.get_current_room()->get_area()->getDesc() << "." <<endl;
        std::cout << "You can go to" << get_directions() << endl;
        print_room_items();

        std::cout << "Enter your command: " << endl;
        std::getline(std::cin, user_input);
        for(auto & c: user_input) c = tolower(c);
        check_user_input(user_input);

    }
}

string Game::get_directions() {
    string result = "";
    for(int i=0; i<4; i++){
        if(player.get_current_room()->get_next_room(i) != nullptr){
            result += " " + possible_direction[i];
        }
    }
    return result;
}

bool Game::step()
{
    if(player.get_current_room() == &rooms.back()){
        std:: cout << "Congratulations, you got out of the dungeon." << endl;
        return false;
    }

    return true;
}

void Game::print_room_items() {
    if(0 < player.get_current_room()->get_current_room_items().size()){
        cout << "Items in this room: ";
        for(auto &rooms_item : player.get_current_room()->get_current_room_items()){
            cout << rooms_item->get_name();
        }
        cout << endl;
    }
}

void Game::check_user_input(string& user_input) {
    int selected_direction = -1;
    for(int i=0; i<possible_direction.size(); i++){
        string lowercase_dir = possible_direction[i];
        for(auto & c: lowercase_dir) c = tolower(c);
        if(user_input == lowercase_dir || (user_input[0] == lowercase_dir[0] && user_input.size() == 1)){
            // goto direction
            selected_direction = i;
        }
    }
    if(selected_direction > -1) {
        player.move_to(selected_direction);
    } else if(user_input == "h" || user_input == "help") {
        std::cout << "HELP: Enter direction (North, East, South or West) or their first letter to move into";
        std::cout << " that direction." << endl;
    } else if(user_input.substr(0, actions[1].size()) == "pick up ") {
        string item_name = user_input.substr(actions[1].size());
        bool is_item_found = false;
        for (auto room_item: player.get_current_room()->get_current_room_items()) {
            if (room_item->get_name() == item_name) {
                is_item_found = true;
                player.pick_item(room_item);
                break;
            }
        }
        if (!is_item_found) {
            std::cout << "This item is not present in the room" << endl;
        }
    } else if(user_input == "inventory"){
        std::cout << "Your inventory contains the following items:" << endl;
        for(auto inventory_item: player.get_inventory()){
            std::cout << " - " << inventory_item->get_name() << ": " << inventory_item->get_description() << std::endl;
        }
    } else {
        std::cout << "Your command is not understood, please try again." << endl;
    }
}
