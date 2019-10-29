/**
 * Assignment #2 COMP345, FALL 2019
 * Project: Risk Domination Game
 * Authors: Giselle Martel (26352936), Wayne Tam (21308688), Jeffrey Li (40017627), Rania Az (40041630)
 */

#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <vector>

using namespace std;

#include "../Map/Map.h"
#include "../MapLoader/MapLoader.h"
#include "../Dice/Dice.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"

class GameEngine {

private:
    MapLoader* game_map_;
    Deck* cards_deck_;
    vector<Player*>* players_;
    int num_of_players_;

public:
    GameEngine();

    GameEngine(const GameEngine& game_engine);

    ~GameEngine();

    GameEngine& operator=(const GameEngine& game_engine);

    inline MapLoader* GetGameMap() const;

    inline Deck* GetCardsDeck() const;

    inline vector<Player*>* GetPlayers() const;

    inline int GetNumPlayers() const;

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