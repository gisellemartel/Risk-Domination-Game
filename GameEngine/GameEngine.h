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

using namespace std;

#include "../Map/Map.h"
#include "../Player/PlayerStrategies.h"
#include "../MapLoader/MapLoader.h"
#include "../Dice/Dice.h"
#include "../Cards/Cards.h"
#include "../GameObservers/GameObservers.h"


class GameEngine;
class MapLoader;
class Deck;

enum PlayerType {
    Human,
    Aggressive,
    Benevolant,
    Random,
    Cheater
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
    bool exit_game_;

    vector<Observer*>* observers_;

    //used to store contents of current directory so that user may reattempt file selection if another fails to load
    vector<filesystem::path>* file_paths_;

    //private helper functions
    MapLoader* SelectFile();
    void PromptUserToSelectNumPlayers(PlayerType player_type);

public:
    // Function to test Player functions within game
    void TestAutoLoadMapAndCreateGame(string file_path, int num_human_players, int num_aggressive_players, int num_benevolant_players);

    //Constructors
    explicit GameEngine();
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