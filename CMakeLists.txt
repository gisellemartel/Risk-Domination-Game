cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 14)

add_executable(Map
        Part1/MapDriver.cpp
        Part1/Map.cpp)
add_executable(MapLoader
        Part2/MapLoaderDriver.cpp
        Part2/MapLoader.cpp)
add_executable(Dice
        Part3/DiceDriver.cpp
        Part3/Dice.cpp
        )
add_executable(Player
        Part4/PlayerDriver.cpp
        Part4/Player
        )
add_executable(Cards
        Part5/CardsDriver.cpp
        Part5/Cards.cpp
        )
