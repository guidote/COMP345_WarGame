#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../PlayerStrategy/PlayerStrategies.h"

int gameEngineMain() {
    // tournament -M <listofmapfiles> -P <listofplayerstrategies> -G <numberofgames> -D <maxnumberofturns>

    /*
    tournament -M canada.map europe.map -P Aggressive Aggressive -G 4 -D 10
    tournament -M canada.map europe.map -P Aggressive Benevolent -G 4 -D 10
    tournament -M canada.map europe.map -P Aggressive Neutral -G 4 -D 50
    tournament -M canada.map europe.map -P Benevolent Benevolent -G 4 -D 50
    tournament -M canada.map europe.map -P Benevolent Neutral -G 4 -D 50
    tournament -M canada.map europe.map -P Cheater Cheater -G 4 -D 50
    tournament -M canada.map europe.map -P Cheater Neutral -G 4 -D 10
    tournament -M canada.map europe.map -P Benevolent Neutral -G 4 -D 10

    tournament -M canada.map europe.map -P Aggressive Cheater Benevolent -G 4 -D 50
    tournament -M canada.map europe.map -P Benevolent Cheater -G 4 -D 50
    tournament -M canada.map europe.map -P Cheater Benevolent -G 4 -D 50
    */


    GameEngine* gameEngine = new GameEngine;
    Order::game = gameEngine;
    PlayerStrategies::game = gameEngine;

    bool isPlaying = true;

    while (isPlaying) {
        gameEngine->startupPhase();

        if (!gameEngine->getIsTournament()) {
            isPlaying = gameEngine->mainGameLoop();
        }
        else {
            isPlaying = false;
        }
    }

    Order::logObs->outputFile.close();

    return 0;
}
