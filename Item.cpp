//
// Created by bekor on 10/11/17.
//

#include "Item.h"

Item::Item(const string &name, const int &weight, const string &description)
        : name(name), weight(weight), description(description)  {
    use_on_obstacle = nullptr;
}

string Item::get_name() {
    return name;
}

int Item::get_weight() {
    return weight;
}

string Item::get_description() {
    return description;
}

Item::Item(const string &name, const int &weight, const string &description, Obstacle *use_on_obstacle)
        : name(name), weight(weight), description(description), use_on_obstacle(use_on_obstacle){

}

Obstacle *Item::use_item_on_obstacle() {
    return use_on_obstacle;
}

