cmake_minimum_required(VERSION 3.14)
project(TeamProject-COMP345)

set(CMAKE_CXX_STANDARD 17)


add_executable(Test
        Test/Tests.cpp
        Utility/Utility.cpp
        Map/Map.cpp
        Map/Continent.cpp
        Map/Country.cpp
        Cards/Cards.cpp
        Dice/Dice.cpp
        Player/PlayerStrategies.cpp
        Player/FortifyPhase.cpp
        Player/Player.cpp
        MapLoader/Adapter.cpp
        MapLoader/MapLoader.cpp
        MapLoader/ConquestMapLoader.cpp
        GameEngine/GameObservers.cpp
        GameEngine/StartupPhase.cpp
        GameEngine/GameEngine.cpp
        Cards/Hand.cpp Cards/Hand.h Cards/Deck.cpp Cards/Deck.h Player/AttackPhase.cpp Player/AttackPhase.h Player/ReinforcePhase.cpp Player/ReinforcePhase.h)
