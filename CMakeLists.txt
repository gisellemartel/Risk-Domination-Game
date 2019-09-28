cmake_minimum_required(VERSION 3.14)
project(RiskDomination)

set(CMAKE_CXX_STANDARD 14)

add_executable(Map
        Map/MapDriver.cpp
        Map/Map.cpp)
add_executable(MapLoader
        MapLoader/MapLoaderDriver.cpp
        MapLoader/MapLoader.cpp)
add_executable(Dice
        Dice/DiceDriver.cpp
        Dice/Dice.cpp
        )
add_executable(Player
        Player/PlayerDriver.cpp
        Player/Player
        )
add_executable(Cards
        Cards/CardsDriver.cpp
        Cards/Cards.cpp
        )
