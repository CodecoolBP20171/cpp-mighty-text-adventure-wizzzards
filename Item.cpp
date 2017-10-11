//
// Created by bekor on 10/11/17.
//

#include "Item.h"

Item::Item(const string &name, const int &weight, const string &description)
        : name(name), weight(weight), description(description)  {

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

