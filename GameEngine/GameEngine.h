/**
 * Assignment #3 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <map>
#include <filesystem>

using namespace std;

#include "../GameObservers/GameObservers.h"
#include "../Map/Map.h"
#include "../Player/PlayerStrategies.h"
#include "../MapLoader/MapLoader.h"
#include "../Dice/Dice.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"


class GameEngine;
class MapLoader;
class Deck;

enum GamePhase {
    Startup = 0,
    Reinforce = 1,
    Attack = 2,
    Fortify = 3
};

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

class GameEngine : public Subject {

private:
    vector<Player*>* players_;
    StartupPhase* game_start_;
    MapLoader* loaded_map_;
    Deck* cards_deck_;

    GamePhase current_phase_;
    int num_of_players_;
    int num_of_human_players_;
    int num_aggressive_players_;
    int num_benevolant_players_;
    bool exit_game_;

    vector<Observer*>* observers_;

    //used to store contents of current directory so that user may reattempt file selection if another fails to load
    vector<filesystem::path>* file_paths_;

    //private helper function
    MapLoader* SelectFile();

public:
    // Function to test Player functions within game
    void TestAutoLoadMapAndCreateGame(string file_path, int num_human_players, int num_aggressive_players, int num_benevolant_players);

    //Constructors
    explicit GameEngine();
    GameEngine(const GameEngine& game_engine);
    ~GameEngine();

    //operator overloader
    GameEngine& operator=(const GameEngine& game_engine);

    //Setters
    void SetCurrentPhase(GamePhase phase);

    //Getters
    MapLoader* GetLoadedMap() const;
    Deck* GetCardsDeck() const;
    GamePhase GetCurrentPhase() const;
    vector<Player*>* GetPlayers() const;
    int GetNumPlayers() const;
    bool ExitGameSelected() const;
    StartupPhase* GetGameStart() const;

    //Methods
    bool SelectMap();
    bool LoadSelectedMap();
    bool PlayerHasWon(Player* current_player);

    void SelectNumOfHumanPlayers();
    void SelectNumOfAggressivePlayers();
    void SelectNumOfBenevolantPlayers();
    void CreatePlayers();
    void AssignDiceToPlayers();
    void AssignHandOfCardsToPlayers();
    void CreateCardsDeck();
    void DisplayCurrentGame();

    void StartGameLoop();

    void Register(Observer* observer) override;
    void Unregister(Observer* observer) override;
    void Notify() override;
};


#endif