cmake_minimum_required(VERSION 3.14)
project(TeamProject-COMP345)

set(CMAKE_CXX_STANDARD 17)


add_executable(Test
        Test/Tests.cpp
        Map/Country.cpp
        Map/Continent.cpp
        Map/Map.cpp
        Player/Phases.cpp
        Player/Player.cpp
        Player/PlayerStrategies.cpp
        Dice/Dice.cpp
        Cards/Cards.cpp
        MapLoader/MapLoader.cpp
        MapLoader/ConquestMapLoader.cpp
        MapLoader/Adapter.cpp
        GameEngine/StartupPhase.cpp
        GameEngine/GameEngine.cpp
        GameObservers/GameObservers.cpp
        Utility/Utility.cpp
        )
