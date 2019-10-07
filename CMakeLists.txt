cmake_minimum_required(VERSION 3.14)
project(TeamProject-COMP345)

set(CMAKE_CXX_STANDARD 14)

add_executable(Map
        Map/MapDriver.cpp
        Map/Map.cpp
        )
add_executable(MapLoader
        Map/Map.cpp
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
        Player/PlayerDriver.cpp
        Player/Player
        )
add_executable(Cards
        Cards/CardsDriver.cpp
        Cards/Cards.cpp
        )
