//
// Created by bekor on 10/12/17.
//

#include "Obstacle.h"

Obstacle::Obstacle(const string &name, const string &description):name(name), description(description) {
}

string Obstacle::get_name() {
    return name;
}

string Obstacle::get_description() {
    return description;
}

