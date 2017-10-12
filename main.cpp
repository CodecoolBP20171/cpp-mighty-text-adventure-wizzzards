#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    cout << "You woke up with a start in your bed room at the Wizzzard University!" << endl;
    cout << "You just realised you are late from" << endl;

    Game game;
    game.init();
    game.run();

    cout << "Exiting from Mighty Text Adventure!" << endl;
    return 0;
}
