//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_STARTUPPHASE_H
#define TEAMPROJECT_COMP345_STARTUPPHASE_H

#include "../Player/Player.h"
#include "../Utility/Utility.h"

#include <vector>
#include <map>
#include <iostream>
using namespace std;

class StartupPhase {

private:
    map<std::shared_ptr<Player>, int>* player_order_;
    int number_of_armies_;

    //private helper functions
    template <class V>
    static vector<int> GenerateRandomizedIndicesForVector(const vector<std::shared_ptr<V>>& vector_to_randomize);

public:
    int current_player_index_;
    //Constructors
    StartupPhase();
    StartupPhase(const StartupPhase& startup_phase);
    ~StartupPhase();

    //operator overloader
    StartupPhase& operator=(const StartupPhase& startup_phase);

    //Setters
    void SetNumberOfArmies(int number_of_players);

    //Methods
    void RandomlyDeterminePlayerOrder(vector<std::shared_ptr<Player>>* players);
    void AssignCountriesToAllPlayers(vector<std::shared_ptr<Player>>* players, vector<Country*>* countries_to_assign);
    void AutoAssignArmiesToAllPlayers(vector<std::shared_ptr<Player>>* players);
    void AssignArmiesToAllPlayers(vector<std::shared_ptr<Player>>* players);
};


#endif //TEAMPROJECT_COMP345_STARTUPPHASE_H
