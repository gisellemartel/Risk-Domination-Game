cmake_minimum_required(VERSION 3.14)
project(TeamProject-COMP345)

set(CMAKE_CXX_STANDARD 14)

add_executable(Map
        Player/Player.cpp
        Dice/Dice.cpp
        Cards/Cards.cpp
        Map/MapDriver.cpp
        Map/Map.cpp
        )
add_executable(MapLoader
        Map/Map.cpp
        Player/Player.cpp
        Dice/Dice.cpp
        Cards/Cards.cpp
        MapLoader/MapLoaderDriver.cpp
        MapLoader/MapLoader.cpp
        )
add_executable(Dice
        Dice/DiceDriver.cpp
        Dice/Dice.cpp
        )
add_executable(Player
        Map/Map.cpp
        Dice/Dice.cpp
        Cards/Cards.cpp
        Player/PlayerDriver.cpp
        Player/Player
        )
add_executable(Cards
        Cards/CardsDriver.cpp
        Cards/Cards.cpp
        )
