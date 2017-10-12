//
// Created by bekor on 10/12/17.
//

#ifndef CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_OBOSTACLES_H
#define CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_OBOSTACLES_H

#include <iostream>

using namespace std;

class Obstacle {
public:
    Obstacle(const string& name, const string& description);

    string get_name();
    string get_description();
private:
    const string name;
    const string description;

};


#endif //CPP_MIGHTY_TEXT_ADVENTURE_WIZZZARDS_OBOSTACLES_H
