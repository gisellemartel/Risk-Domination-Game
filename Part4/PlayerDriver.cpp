//
// COMP345 Assignment #1, Fall 2019
//

#include <iostream>
using namespace std;

#include "Player.h"

int main()
{
    cout << "Executing Player Driver" << endl;
    Player* newPlayer = new Player();
    delete newPlayer;

    return 0;
}
