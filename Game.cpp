
#include <iostream>
#include <algorithm>

#include "Game.h"
#include "Monster.h"

void Game::init()
{
    loadAreas();
    loadObstacles();
    loadItems();
    loadRooms();
    Player player(&rooms[0]);
    setPlayer(player);
    Monster monster(&rooms[2], "friendly monster");
    monster.set_description(" It does not hurt you, but begs you to lead it to the wizzard lecture. Will you help?");
    setMonsters(monster);
}

void Game::run()
{
    string user_input;
    while(step()){
        std::cout << "You are in " << player.get_current_room()->get_area()->getDesc() << "." <<endl;
        std::cout << "You can go to" << get_directions() << endl;
        print_room_items();
        print_room_monsters();
      
        std::cout << "Enter your command: " << endl;
        std::getline(std::cin, user_input);
        for(auto & c: user_input) c = tolower(c);
        check_user_input(user_input);

    }
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
    items.emplace_back("key", 10, "This is a key", &obstacles[0]);
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
    connect_rooms(7, nullptr , nullptr, &rooms[6], nullptr);

    addItemsToRooms();
    obstacles_to_rooms(3, nullptr, &obstacles[0], nullptr, nullptr);
}

void Game::setMonsters(Monster monster) {
    monsters.push_back(monster);
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
    rooms[2].add_items(&items[1]);
}

void Game::setPlayer(Player player) {
    this->player = player;
}


void Game::loadObstacles() {
    obstacles.emplace_back("Locked Door", "You need a key to unlock it");
}

void Game::obstacles_to_rooms(int room_number, Obstacle* to_north, Obstacle* to_east, Obstacle* to_south, Obstacle* to_west) {
    Obstacle* obs_direct[4];
    obs_direct[direction::NORTH] = to_north;
    obs_direct[direction::EAST] = to_east;
    obs_direct[direction::SOUTH] = to_south;
    obs_direct[direction::WEST] = to_west;

    Obstacle** p_dir = &obs_direct[0];
    rooms[room_number].set_obstacle(p_dir, sizeof(obs_direct)/sizeof(obs_direct[0]));
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
        std:: cout << "Congratulations, you found your way to the classroom." << endl;
        return false;
    }

    return true;
}

void Game::print_room_items() {
    if(0 < player.get_current_room()->get_current_room_items().size()){
        cout << "Items in this room: ";
        for(auto &rooms_item : player.get_current_room()->get_current_room_items()){
            cout << rooms_item->get_name() << " ";
        }
        cout << endl;
    }
}

void Game::print_room_monsters() {
    // Currently only one monster is handled
    if(monsters[0].get_current_room() == player.get_current_room()){
        cout << "There is a " << monsters[0].get_name() << " in the room!" << monsters[0].get_description();
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

    if(selected_direction > -1 && player.get_current_room()->get_next_room(selected_direction)) {
        if(player.get_current_room()->get_room_obstacles(selected_direction)){
            bool you_can_go = false;
            for(auto inventory_item: player.get_inventory()){
                if(inventory_item->use_item_on_obstacle() ==  player.get_current_room()->get_room_obstacles(selected_direction)){
                    cout << " You can go past " << endl;
                    player.move_to(selected_direction);
                    you_can_go = true;
                }
            }
            if(!you_can_go){
                cout<< player.get_current_room()->get_room_obstacles(selected_direction)->get_description() << endl;
            }

        } else {
            player.move_to(selected_direction);
        }
        if(player.get_player_helping_monster()){
            monsters[0].move_to(selected_direction);
        } else {
            vector<int> possible_directions;
            for(int i = 0; i < 4; i++){
                if(monsters[0].get_current_room()->get_next_room(i) != nullptr){
                    possible_directions.push_back(i);
                }
            }
            srand (time(NULL));
            int random_index = rand() % possible_directions.size();
            if(monsters[0].get_current_room() == &rooms.back()-1){
                possible_directions.erase(std::remove(possible_directions.begin(), possible_directions.end(), 1), possible_directions.end());
            }
            monsters[0].move_to(possible_directions[random_index]);
        }
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
            std::cout << "This item is not present in the room." << endl;
        }
    } else if(user_input == "inventory") {
        if (player.get_inventory().size() > 0){
            std::cout << "Your inventory contains the following items:" << endl;
        } else {
            std::cout << "Your inventory is empty." << endl;
        }
        for(auto inventory_item: player.get_inventory()){
            std::cout << " - " << inventory_item->get_name() << ": " << inventory_item->get_description() << std::endl;
        }
    } else if(user_input.substr(0, actions[3].size()) == "throw ") {
        string item_name = user_input.substr(actions[3].size());
        bool is_item_found = false;
        for (auto inventory_item: player.get_inventory()) {
            if (inventory_item->get_name() == item_name) {
                is_item_found = true;
                player.throw_item(inventory_item);
                break;
            }
        }
        if (!is_item_found) {
            std::cout << "This item is not present in your inventory." << endl;
        }
    } else if(user_input == "yes" && monsters[0].get_current_room() == player.get_current_room() && !player.get_player_helping_monster()){
        std::cout << "Cool, the monster will follow you!" << endl;
        player.set_player_helping_monster(true);
        monsters[0].set_description(" It is following you.");
    } else if(user_input == "no" && monsters[0].get_current_room() == player.get_current_room() && !player.get_player_helping_monster()){
        std::cout << "The monster starts to roam in the school hopelessly." << endl;
        player.set_player_helping_monster(false);
        monsters[0].set_description(" He is very sad.");
    } else {
        std::cout << "Your command is not understood, please try again." << endl;
    }
}
