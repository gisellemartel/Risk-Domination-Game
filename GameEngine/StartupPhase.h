//
// Created by Giselle Martel on 2019-11-26.
//

#ifndef TEAMPROJECT_COMP345_STARTUPPHASE_H
#define TEAMPROJECT_COMP345_STARTUPPHASE_H

#include "../Map/Map.h"
#include "../Player/Player.h"

class StartupPhase {

private:
    map<Player*, int>* player_order_;
    int number_of_armies_;

    //private helper functions
    template <class V>
    static vector<int> GenerateRandomizedIndicesForVector(const vector<V*>& vector_to_randomize);

public:
    int current_player_index_;
    //Constructors
    StartupPhase();
    StartupPhase(const StartupPhase& startup_phase);
    ~StartupPhase();

    //operator overloader
    StartupPhase& operator=(const StartupPhase& startup_phase);

    //Getters
    inline map<Player*, int>* GetPlayerOrderMap() const;

    //Setters
    void SetNumberOfArmies(int number_of_players);

    //Methods
    void RandomlyDeterminePlayerOrder(vector<Player*>* players);
    void AssignCountriesToAllPlayers(vector<Player*>* players, vector<Country*>* countries_to_assign);
    void AutoAssignArmiesToAllPlayers(vector<Player*>* players);
    void AssignArmiesToAllPlayers(vector<Player*>* players);
};


#endif //TEAMPROJECT_COMP345_STARTUPPHASE_H
