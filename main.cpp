#include <iostream>
#include "Game.h"

using namespace std;

int main() {
    cout << "* You woke up with a start in your bed room at the Wizzzard University!" << endl;
    cout << "* You just realised you are late from the Magical Anti Terrestrial Animals Class" << endl;
    cout << "* You get yourself together and run to the Class room.\n" << endl;

    Game game;
    game.init();
    game.run();

    cout << "Yeh, you made it, you are in the Class room, but... !" << endl;
    cout << ":: The story will or will not continue ::" << endl;
    return 0;
}
