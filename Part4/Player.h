/**
 * Assignment #1 COMP345, FALL 2019
 * Authors: Giselle Martel (26352936), Wayne Tam, Jeffrey Li, Rania Az
 */

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
