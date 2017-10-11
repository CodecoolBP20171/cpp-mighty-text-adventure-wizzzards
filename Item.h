//
// Created by bekor on 10/11/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ITEM_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ITEM_H

#include <string>

using namespace std;

class Item {
public:
    Item(const string& name, const int& weight, const string& description);

    string get_name();
    int get_weight();
    string get_description();

private:
    const string name;
    const int weight;
    const string description;
};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_ITEM_H
