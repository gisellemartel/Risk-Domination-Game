//
// COMP345 Assignment #1, Fall 2019
//

#ifndef TEAMPROJECT_COMP345_PLAYER_H
#define TEAMPROJECT_COMP345_PLAYER_H
#endif //TEAMPROJECT_COMP345_PLAYER_H

#include <iostream>
using namespace std;

class Player {
public:

    Player() {
        cout << "Instantiating new Player object" << endl;
    };

    ~Player() {
        cout << "Destroying Player object" << endl;
    }

    void reinforce() {};
    void attack() {};
    void fortify() {};

private:

};
