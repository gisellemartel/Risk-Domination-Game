/**
 * Assignment #4 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */
#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>
#include <map>
#include <filesystem>
#include <iostream>
#include <string>
#include <utility>
#include <iterator>
#include <random>
using namespace std;

#include "GameObservers.h"

enum PlayerType {
    Human,
    Aggressive,
    Benevolant,
    Random,
    Cheater
};

enum GameResult {
    AggressiveWin,
    RandomWin,
    CheaterWin,
    Draw
};

class GameEngine : public PhaseSubject, public StatisticsSubject {

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
    int num_random_players_;
    int num_cheater_players_;
    int num_unqiue_maps_;
    int num_strategies_;
    int max_num_turns_per_game_;
    bool exit_game_;

    map<int, MapLoader*>* game_maps_;  //key is # game per map
    map<Map*, vector<GameResult>>* game_results_; //data structure that will store the results of all games for each map

    vector<Observer*>* observers_;

    //used to store contents of current directory so that user may reattempt file selection if another fails to load
    vector<filesystem::path>* file_paths_;

    //private helper functions
    MapLoader* SelectFile();
    void PromptUserToSelectNumPlayers(PlayerType player_type);

    void StartTournament();

public:
    // Function to test Player functions within game
    void TestAutoLoadMapAndCreateGame(string file_path, int num_human_players, int num_aggressive_players, int num_benevolant_players, int num_random_players, int num_cheater_players);

    //Constructors
    GameEngine();
    GameEngine(const GameEngine& game_engine);
    ~GameEngine();

    //operator overloader
    GameEngine& operator=(const GameEngine& game_engine);

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
    bool AutoSelectMap(string dir);
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


    //TODO: code added for A4
    void CreateNewGame();
    //

    void Register(Observer* observer) override;
    void Unregister(Observer* observer) override;
    void Notify(Player* current_player, int current_phase, string current_phase_action_description, bool phase_start, bool phase_over) override;
    void Notify(string msg) override;

    void RemovePlayer(Player* player);
};

#endif