//
// Created by Joe Bekor on 12/10/2017.
//

#include "UserInterface.h"

void UserInterface::player_interact(Player &player, vector<Monster> &monsters, vector<Room> &rooms) {
    string user_input;
    cout << "You are in " << player.get_current_room()->get_area()->getDesc() << "." <<endl;
    cout << "You can go to" << get_directions(player) << endl;
    print_room_items(player);
    print_room_monsters(player, monsters);

    cout << "Enter your command: " << endl;
    getline(cin, user_input);
    for(auto & c: user_input) c = tolower(c);
    check_user_input(player, monsters, rooms, user_input);
}

string UserInterface::get_directions(Player &player) {
    string result;
    for(int i=0; i<4; i++){
        if(player.get_current_room()->get_next_room(i) != nullptr){
            result += " " + possible_direction[i];
        }
    }
    return result;
}

void UserInterface::print_room_items(Player &player) {
    if(!player.get_current_room()->get_current_room_items().empty()){
        cout << "Items in this room: ";
        for(auto &rooms_item : player.get_current_room()->get_current_room_items()){
            cout << rooms_item->get_name() << " ";
        }
        cout << endl;
    }
}

void UserInterface::print_room_monsters(Player &player, vector<Monster> &monsters) {
    // Currently only one monster is handled
    if(monsters[0].get_current_room() == player.get_current_room()){
        cout << "There is a " << monsters[0].get_name() << " in the room!" << monsters[0].get_description();
        cout << endl;
    }
}

void UserInterface::check_user_input(Player &player, vector<Monster> &monsters,
                                     vector<Room> &rooms, string& user_input) {
    int selected_direction = -1;
    player_selected_direction(user_input, selected_direction);

    if(selected_direction > -1 && player.get_current_room()->get_next_room(selected_direction)) {
        if(player.get_current_room()->get_room_obstacles(selected_direction))
        {
            interact_with_obstacles(player, selected_direction);
        }
        else
        {
            player.move_to(selected_direction);
        }
        if(player.get_player_helping_monster()){
            monsters[0].move_to(selected_direction);
        }
        else
        {
            move_monster(monsters, rooms);
        }
    }
    else if(user_input == "h" || user_input == "help") {
        print_help();
    }
    else if(user_input.substr(0, actions[1].size()) == "pick up ") {
        pick_up_item(player, user_input);
    }
    else if(user_input == "inventory")
    {
        print_inventory(player);
    }
    else if(user_input.substr(0, actions[3].size()) == "throw ")
    {
        throw_item_from_inventory(player, user_input);
    }
    else if(user_input == "yes" && monster_is_in_the_room(player, monsters))
    {
        cout << "Cool, the magical monster will follow you!" << endl;
        player.set_player_helping_monster(true);
        monsters[0].set_description(" It is following you.");
    }
    else if(user_input == "no" && monster_is_in_the_room(player, monsters))
    {
        cout << "The magical monster starts to roam in the school hopelessly." << endl;
        player.set_player_helping_monster(false);
        monsters[0].set_description(" He is very sad.");
    }
    else {
        cout << "~ Your command is not understood, please try again." << endl;
    }
}

void UserInterface::player_selected_direction(string &user_input, int &selected_direction) const {
    for(int i=0; i < possible_direction.size(); i++){
        string lowercase_dir = possible_direction[i];
        for(auto & c: lowercase_dir) c = tolower(c);
        if(user_input == lowercase_dir || (user_input[0] == lowercase_dir[0] && user_input.size() == 1)){
            selected_direction = i;
        }
    }
}

void UserInterface::interact_with_obstacles(Player &player, int selected_direction) const {
    bool you_can_go = false;
    for(auto inventory_item: player.get_inventory()){
        if(inventory_item->use_item_on_obstacle() ==  current_room_obstacle(player, selected_direction)){
            cout << "// You used the " << inventory_item->get_name();
            cout << " to go through the " << inventory_item->use_item_on_obstacle()->get_name();
            cout << " //" << endl;

            player.move_to(selected_direction);
            you_can_go = true;
        }
    }
    if(!you_can_go){
        cout << current_room_obstacle(player, selected_direction)->get_name() << endl;
        cout << current_room_obstacle(player, selected_direction)->get_description() << endl;
    }
}

Obstacle *UserInterface::current_room_obstacle(Player &player, int selected_direction) const {
    return player.get_current_room()->get_room_obstacles(selected_direction);
}

void UserInterface::move_monster(vector<Monster> &monsters, vector<Room> &rooms){
    vector<int> poss_directions;
    for(int i = 0; i < 4; i++){
        if(monsters[0].get_current_room()->get_next_room(i)
           && monsters[0].get_current_room()->get_next_room(i) != &rooms.back()){
            poss_directions.push_back(i);
        }
    }
    srand (time(NULL));
    int random_index = rand() % poss_directions.size();
    monsters[0].move_to(poss_directions[random_index]);
}

void UserInterface::print_help() const {
    cout << "## HELP:" << endl;
    cout << "##  -Enter direction (North, East, South or West) or their first letter to move into";
    cout << " that direction." << endl;
    cout << "##  -With \"pick up (item-name)\" you can pick up an item from a room" << endl;
    cout << "##  -With \"throw (item-name)\" you can drop an item in a room" << endl;
    cout << "##  -If you are in the same room with the monster you can interact with it";
    cout << " by typing in: \"yes\" or \"no\". \n" << endl;
}

void UserInterface::pick_up_item(Player &player, const string &user_input) const {
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
        cout << "~ This item is not present in the room." << endl;
    }
}

void UserInterface::print_inventory(Player &player) const {
    if (!player.get_inventory().empty()){
        cout << "~ Your inventory contains the following items:" << endl;
    } else {
        cout << "~ Your inventory is empty." << endl;
    }
    for(auto inventory_item: player.get_inventory()){
        cout << " - " << inventory_item->get_name() << ": " << inventory_item->get_description() << endl;
    }
}

void UserInterface::throw_item_from_inventory(Player &player, const string &user_input) const {
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
        cout << "~ This item is not present in your inventory." << endl;
    }
}

bool UserInterface::monster_is_in_the_room(Player &player, vector<Monster> &monsters) const {
    return monsters[0].get_current_room() == player.get_current_room() && !player.get_player_helping_monster();
}
