cmake_minimum_required(VERSION 3.21)
project(COMP345_Assignment)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(
        COMP345-Exercises
        Cards/Cards.h
        Cards/Cards.cpp
        Cards/CardsDriver.cpp
        CommandProcessing/CommandProcessing.h
        CommandProcessing/CommandProcessing.cpp
        CommandProcessing/CommandProcessingDriver.cpp
        GameEngine/GameEngine.h
        GameEngine/GameEngine.cpp
        GameEngine/GameEngineDriver.cpp
        GameEngine/GameLoopDriver.cpp
        LoggingObserver/LoggingObserver.h
        LoggingObserver/LoggingObserver.cpp
        LoggingObserver/LoggingObserverDriver.cpp
        Map/Map.h
        Map/Map.cpp
        Map/MapDriver.cpp
        Orders/Orders.h
        Orders/Orders.cpp
        Orders/OrdersDriver.cpp
        Player/Player.h
        Player/Player.cpp
        Player/PlayerDriver.cpp
        PlayerStrategy/PlayerStrategies.h
        PlayerStrategy/PlayerStrategies.cpp
        PlayerStrategy/PlayerStrategiesDriver.cpp
)

