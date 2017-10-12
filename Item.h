//
// Created by bekor on 10/11/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ITEM_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ITEM_H

#include "Obstacle.h"

using namespace std;

class Item {
public:
    Item(const string& name, const int& weight, const string& description);
    Item(const string& name, const int& weight, const string& description, Obstacle* use_on_obstacle);

    string get_name();
    int get_weight();
    string get_description();
    Obstacle* use_item_on_obstacle();

private:
    const string name;
    const int weight;
    const string description;
    Obstacle* use_on_obstacle;

};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ITEM_H
