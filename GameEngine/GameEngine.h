/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <map>
#include <filesystem>

using namespace std;

#include "../Map/Map.h"
#include "../MapLoader/MapLoader.h"
#include "../Dice/Dice.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"

class StartupPhase {

private:
    map<Player*, int>* player_order_;

    static int GenerateRandomNumInRange(int lower_bound, int upper_bound);

    static bool HasValue(const vector<int>& values, const int value);

public:
    StartupPhase();

    StartupPhase(const StartupPhase& startup_phase);

    ~StartupPhase();

    StartupPhase& operator=(const StartupPhase& startup_phase);

    inline map<Player*, int>* GetPlayerOrderMap() const;

    void RandomlyDeterminePlayerOrder(vector<Player*>* players);

    void AssignCountriesToAllPlayer(vector<Player*>* players, vector<Country*>* countries_to_assign);
};

class GameEngine {

private:
    StartupPhase* game_start_;
    MapLoader* game_map_;
    Deck* cards_deck_;
    vector<Player*>* players_;
    int num_of_players_;
    bool exit_game_;

    //used to store contents of current directory so that user may reattempt file selection if another fails to load
    vector<filesystem::path>* file_paths_;

    //helper function
    MapLoader* SelectFile();

public:
    explicit GameEngine();

    GameEngine(const GameEngine& game_engine);

    ~GameEngine();

    GameEngine& operator=(const GameEngine& game_engine);

    MapLoader* GetGameMap() const;

    Deck* GetCardsDeck() const;

    vector<Player*>* GetPlayers() const;

    int GetNumPlayers() const;

    bool ExitGameSelected() const;

    bool SelectMap();

    bool LoadSelectedMap();

    void SelectNumOfPlayers();

    void CreatePlayers();

    void AssignDiceToPlayers();

    void AssignHandOfCardsToPlayers();

    void CreateCardsDeck();

    void DisplayCurrentGame();
};

#endif