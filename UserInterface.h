//
// Created by Joe Bekor on 12/10/2017.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_USERINTERFACE_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_USERINTERFACE_H

#include "Player.h"
#include "Monster.h"

class UserInterface {
public:
    void player_interact(Player &player, vector<Monster> &monsters, vector<Room> &rooms);

private:
    const vector<string> possible_direction = {"North", "East", "South", "West"};
    const vector<string> actions = {"Help", "Pick up ", "Inventory", "Throw "};

    string get_directions(Player &player);
    void print_room_items(Player &player);
    void print_room_monsters(Player &player, vector<Monster> &monsters);
    void check_user_input(Player &player, vector<Monster> &monsters, vector<Room> &rooms, string &user_input);
    void player_selected_direction(string &user_input, int &selected_direction) const;
    void interact_with_obstacles(Player &player, int selected_direction) const;
    Obstacle *current_room_obstacle(Player &player, int selected_direction) const;
    void move_monster(vector<Monster> &monsters, vector<Room> &rooms);
    void print_help() const;
    void pick_up_item(Player &player, const string &user_input) const;
    void print_inventory(Player &player) const;
    void throw_item_from_inventory(Player &player, const string &user_input) const;
    bool monster_is_in_the_room(Player &player, vector<Monster> &monsters) const;
};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_USERINTERFACE_H
