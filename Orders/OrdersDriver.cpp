#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../LoggingObserver/LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../GameEngine/GameEngine.h"
#include "Orders.h"

int ordersMain() {
    /****************************** CREATING A GAME *******************************/

    // Create Map Loader
    MapLoader* loader;
    Map *mainmap = loader->load("../Orders/canada.map");

    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player(); player1->setReinforcementPool(10); player1->setName("Audrey");
    Player* player2 = new Player(); player2->setReinforcementPool(12); player2->setName("MJ");
    player_list.push_back(player1); player_list.push_back(player2);

    // Create & Set up Game Engine
    GameEngine* mainGE = new GameEngine();
    mainGE->setMap(mainmap);
    mainGE->setplayer_list(player_list);
    Order::game = mainGE;

    // Assign Territories to Players
    int playerIndex = 0;
    for (Territory *i : mainmap->getTerritories()) {
        Player *tempPlayer = mainGE->getplayer_list().at(playerIndex);
        i->setOwner(tempPlayer);
        tempPlayer->assignTerritory(i);

        playerIndex++;
        if (playerIndex >= mainGE->getplayer_list().size()) {
            playerIndex = 0;
        }
    }

    // Display Player list of Territories
    cout << endl;
    for (int i=0; i<mainGE->getplayer_list().size();i++){
        cout << mainGE->getplayer_list().at(i)->getName() << "'s territories: ";
        for(auto teri : mainGE->getplayer_list().at(i)->getTerritoryList()){
            cout << teri->getName() << " | ";
        }
        cout << endl;
    }

    // ******************************* Testing Orders Constructor *******************************
    // Create Territories for testing
    Territory* Yukon_Territory = Order::game->getMap()->getTerritories().at(30); Yukon_Territory->setArmies(4);
    Territory* Ontario_South = Order::game->getMap()->getTerritories().at(8); Ontario_South->setArmies(0);
    Territory* Ontario_North = Order::game->getMap()->getTerritories().at(10); Ontario_North->setArmies(0);
    Territory* Quebec_Central = Order::game->getMap()->getTerritories().at(6); Quebec_Central->setArmies(4);
    Territory* Manitoba_South = Order::game->getMap()->getTerritories().at(11); Manitoba_South->setArmies(4);

    Territory* Ontario_West = Order::game->getMap()->getTerritories().at(9); Ontario_West->setArmies(4);
    Territory* Quebec_South = Order::game->getMap()->getTerritories().at(7); Quebec_South->setArmies(0);
    Territory* Quebec_North = Order::game->getMap()->getTerritories().at(5); Quebec_North->setArmies(12);

    cout << "\n-------------------- DEPLOY --------------------" << endl;
    cout << "\n--------- Player 1" << endl;
    Deploy* deploy1 = new Deploy(player1, Ontario_South);
    cout << "Order: " << *deploy1 << endl;
    deploy1->validate();
    deploy1->execute();
    cout << deploy1->stringToLog() << endl;

    cout << "\n--------- Player 2" << endl;
    Deploy* deploy2 = new Deploy(player2, Quebec_North);
    cout << "Order: " << *deploy2 << endl;
    deploy2->validate();
    deploy2->execute();
    cout << deploy2->stringToLog() << endl;

    cout << "\n--------- Player 1 (Target belongs to another player)" << endl;
    // Target territory belongs to enemy -> failed
    Deploy* deploy3 = new Deploy(player1, Ontario_West);
    cout << "Order: " << *deploy3 << endl;
    deploy3->validate();
    deploy3->execute();
    cout << deploy3->stringToLog() << endl;


    cout << "\n-------------------- AIRLIFT --------------------" << endl;
    cout << "\n--------- Player 1" << endl;
    Airlift* airlift1 = new Airlift(player1, Ontario_South, Ontario_North);
    cout << "Order: " << *airlift1 << endl;
    airlift1->validate();
    airlift1->execute();
    cout << airlift1->stringToLog() << endl;

    // Target territory belongs to enemy -> failed
    cout << "\n--------- Player 1 (Target belongs to another player)" << endl;
    Airlift* airlift2 = new Airlift(player1, Ontario_South, Ontario_West);
    cout << "Order: " << *airlift2 << endl;
    airlift2->validate();
    airlift2->execute();
    cout << airlift2->stringToLog() << endl;

    // Origin territory is not yours -> failed
    cout << "\n--------- Player 1 (Origin belongs to another player)" << endl;
    Airlift* airlift3 = new Airlift(player1, Ontario_West, Ontario_South);
    cout << "Order: " << *airlift3 << endl;
    airlift3->validate();
    airlift3->execute();
    cout << airlift3->stringToLog() << endl;

    cout << "\n-------------------- BOMB --------------------" << endl;
    cout << "\n--------- Player 2" << endl;
    Bomb* bomb1 = new Bomb(player2, Ontario_West, Ontario_South);
    cout << "Order: " << *bomb1 << endl;
    bomb1->validate();
    bomb1->execute();
    cout << bomb1->stringToLog() << endl;

    // Target territory is your own territory -> failed
    cout << "\n--------- Player 2 (Target belongs to player issuing)" << endl;
    Bomb* bomb2 = new Bomb(player1, Ontario_South, Ontario_North);
    cout << "Order: " << *bomb2 << endl;
    bomb2->validate();
    bomb2->execute();
    cout << bomb2->stringToLog() << endl;

    // Target territory is not adjacent -> failed
    cout << "\n--------- Player 2 (Origin & Target are not adjacent)" << endl;
    Bomb* bomb6 = new Bomb(player1, Yukon_Territory, Quebec_North);
    cout << "Order: " << *bomb6 << endl;
    bomb6->validate();
    bomb6->execute();
    cout << bomb6->stringToLog() << endl;

    cout << "\n-------------------- ADVANCE --------------------" << endl;
    // Attack
    cout << "\n--------- Player 2 (Type Attack)" << endl;
    Advance* advance1 = new Advance(player2, Quebec_North, Quebec_Central);
    cout << "Order: " << *advance1 << endl;
    advance1->validate();
    advance1->execute();
    cout << advance1->stringToLog() << endl;

    // Move armies
    cout << "\n--------- Player 2 (Type Move)" << endl;
    Advance* advance2 = new Advance(player2, Ontario_West, Manitoba_South);
    cout << "Order: " << *advance2 << endl;
    advance2->validate();
    advance2->execute();
    cout << advance2->stringToLog() << endl;

    // Territories are not adjacent
    cout << "\n--------- Player 1 (Origin & Target are not adjacent)" << endl;
    Advance* advance3 = new Advance(player1, Ontario_North, Quebec_North);
    cout << "Order: " << *advance3 << endl;
    advance3->validate();
    advance3->execute();
    cout << advance3->stringToLog() << endl;

    // Origin territory doesn't belong to player  -> failed
    Advance* advance4 = new Advance(player1, Quebec_North, Ontario_South);
    cout << "Order: " << *advance4 << endl;
    advance4->validate();
    advance4->execute();
    cout << advance4->stringToLog() << endl;

    cout << "\n-------------------- BLOCKADE --------------------" << endl;
    cout << "\n--------- Player 2" << endl;
    Blockade* blockade1 = new Blockade(player2, Ontario_West);
    cout << "Order: " << *blockade1 << endl;
    blockade1->validate();
    blockade1->execute();
    cout << blockade1->stringToLog() << endl;

    cout << "\n--------- Player 1" << endl;
    Blockade* blockade2 = new Blockade(player1, Quebec_Central);
    cout << "Order: " << *blockade2 << endl;
    blockade2->validate();
    blockade2->execute();
    cout << blockade2->stringToLog() << endl;

    // The effect of Neural Player persist
    cout << "\n--------- Player 2" << endl;
    Blockade* blockade3 = new Blockade(player2, Quebec_Central);
    cout << "Order: " << *blockade3 << endl;
    blockade3->validate();
    blockade3->execute();
    cout << blockade3->stringToLog() << endl;

    // Territory is under protection of blockade -> failed
    cout << "\n--------- Player 2 (Territory under ownership of Neutral Player, cannot be attacked)" << endl;
    Bomb* bomb4 = new Bomb(player1, Ontario_South , Ontario_West);
    cout << "Order: " << *bomb4 << endl;
    bomb4->validate();
    bomb4->execute();
    cout << bomb4->stringToLog() << endl;

    // Territory is under protection of blockade -> failed
    cout << "\n--------- Player 1 (Territory under blockade protection + territory does not belong to playerIssuing)" << endl;
    Advance* advance5 = new Advance(player1,Quebec_North , Quebec_Central);
    cout << "Order: " << *advance5 << endl;
    advance5->validate();
    advance5->execute();
    cout << advance5->stringToLog() << endl;

    cout << "\n-------------------- NEGOTIATE --------------------" << endl;
    cout << "\n--------- Player 1 & Player 2" << endl;
    Negotiate* negotiate1 = new Negotiate(player1, player2);
    cout << "Order: " << *negotiate1 << endl;
    negotiate1->validate();
    negotiate1->execute();
    cout << negotiate1->stringToLog() << endl;

    // Target player is yourself -> failed
    cout << "\n--------- Player 1 & Player 1" << endl;
    Negotiate* negotiate2 = new Negotiate(player1, player1);
    cout << "Order: " << *negotiate2 << endl;
    negotiate2->validate();
    negotiate2->execute();
    cout << negotiate2->stringToLog() << endl;

    // Target territory is under negotiate, cannot be bombed -> failed
    cout << "\n--------- Player 2 attacking Player 1" << endl;
    Bomb* bomb5 = new Bomb(player2, Quebec_North, Ontario_North);
    cout << "Order: " << *bomb5 << endl;
    bomb5->validate();
    bomb5->execute();
    cout << bomb5->stringToLog() << endl;


    cout << "\n--------- Player 1" << endl;
    Advance* advance6 = new Advance(player1,Ontario_South, Quebec_South);
    cout << "Order: " << *advance6 << endl;
    advance6->validate();
    advance6->execute();

    // Testing issueOrder and executeOrder
    cout << "\n-------------------- IssueOrder phase --------------------\n" << endl;
    vector<int> tempOrder;
    for (int j = 0; j < mainGE->getplayer_list().size(); j++) {
        int randOrder = rand() % mainGE->getplayer_list().size();
        while (doesContain(tempOrder, randOrder)) {
            randOrder = rand() % mainGE->getplayer_list().size();
        }
        tempOrder.push_back(randOrder);
    }
    mainGE->setPlayerOrder(tempOrder);

    mainGE->resetAlliances();
    mainGE->setNumberOfPlayers(mainGE->getplayer_list().size());

    cout << player1->getName()<<" OrderList: " << *player1->getOrder() <<endl;
    cout << player2->getName()<< " OrderList: " << *player2->getOrder() <<endl;

    mainGE->issueOrdersPhase();

    cout << player1->getName()<<" OrderList: " << *player1->getOrder() <<endl;
    cout << player2->getName()<< " OrderList: " << *player2->getOrder() <<endl;

    cout << "\n------------------- Execution phase --------------------\n" << endl;
    mainGE->executeOrdersPhase();

    cout << player1->getName()<<" OrderList: " << *player1->getOrder() <<endl;
    cout << player2->getName()<< " OrderList: " << *player2->getOrder() <<endl;
    //
    // ******************************* Testing Orders Constructor for GameLoop *******************************
    // ToDefend() & toAttack()

    // Testing GetConnected
//    cout << "Testing GetConnected" << endl;
//    string terriName = player1->getTerritoryList().at(0)->getName();
//    vector<Territory*> territoriesConnected = mainmap->getConnectedTerritories(terriName);
//    for(auto teri : territoriesConnected){
//        cout << *teri << endl;
//    }

//     Testing ToDefend
//    cout << "Testing ToDefend" << endl;
//    vector<Territory*> territoriesToDefend = player1->toDefend(mainmap);
//    for(auto teri : territoriesToDefend){
//        cout << *teri << endl;
//    }
//
//     Testing ToAttack
//    cout << "Testing ToAttack" << endl;
//    vector<Territory*> territoriesToAttack = player1->toAttack(mainmap);
//    for(auto teri : territoriesToAttack){
//        cout << *teri << endl;
//    }

/*
    // Deploy
    cout << "\n-------------------- DEPLOY --------------------\n" << endl;
    Deploy *deploy1 = new Deploy(player1);
    cout << "Order: "<< *deploy1 << endl;
    deploy1->validate();
    deploy1->execute();
    cout << deploy1->stringToLog() << endl;

    Deploy *deploy2 = new Deploy(player1);
    cout << "Order: "<< *deploy2 << endl;
    deploy2->validate();
    deploy2->execute();
    cout << deploy2->stringToLog() << endl;

    Deploy *deploy3 = new Deploy(player2);
    cout << "Order: "<< *deploy3 << endl;
    deploy3->validate();
    deploy3->execute();
    cout << deploy3->stringToLog() << endl;

    Deploy *deploy4 = new Deploy(player2);
    cout << "Order: "<< *deploy4 << endl;
    deploy4->validate();
    deploy4->execute();
    cout << deploy4->stringToLog() << endl;

    // Airlift
    cout << "\n-------------------- AIRLIFT --------------------\n" << endl;
	  Airlift *airlift1 = new Airlift(player1);
    cout << "Order: "<< *airlift1 << endl;
    airlift1->validate();
    airlift1->execute() ;
    cout << airlift1->stringToLog() <<endl;

    Deploy *deploy5 = new Deploy(player1);
    Deploy *deploy6 = new Deploy(player1);
    Deploy *deploy7 = new Deploy(player1);
    Deploy *deploy8 = new Deploy(player1);
    Deploy *deploy9 = new Deploy(player1);
    Deploy *deploy10 = new Deploy(player1);
    Deploy *deploy11 = new Deploy(player1);

    // Advance
    cout << "\n-------------------- ADVANCE --------------------\n" << endl;
    Advance *advance1 = new Advance(player1);
    cout << "Order: "<< *advance1 << endl;
    advance1->validate();
    advance1->execute();
//    cout << advance1->stringToLog() << endl;

    Advance *advance2 = new Advance(player1);
    cout << "Order: "<< *advance2 << endl;
    advance2->validate();
    advance2->execute();
//    cout << advance2->stringToLog() << endl;

    Advance *advance3 = new Advance(player2);
    cout << "Order: "<< *advance3 << endl;
    advance3->validate();
    advance3->execute();
//    cout << advance3->stringToLog() << endl;

    Advance *advance4 = new Advance(player2);
    cout << "Order: "<< *advance4 << endl;
    advance4->validate();
    advance4->execute();
//    cout << advance4->stringToLog() << endl;
*/
    // Airlift
//    cout << "\n-------------------- AIRLIFT --------------------\n" << endl;
//	Airlift *airlift1 = new Airlift(player1);
//    cout << "Order: "<< *airlift1 << endl;
//    airlift1->validate();
//    airlift1->execute();
//    cout << airlift1->stringToLog() <<endl;
//
//    Airlift *airlift2 = new Airlift(player1);
//    cout << "Order: "<< *airlift2 << endl;
//    airlift2->validate();
//    airlift2->execute();
//    cout << airlift2->stringToLog() <<endl;
//
//    Airlift *airlift3 = new Airlift(player2);
//    cout << "Order: "<< *airlift3 << endl;
//    airlift3->validate();
//    airlift3->execute();
//    cout << airlift3->stringToLog() <<endl;
//
//    Airlift *airlift4 = new Airlift(player2);
//    cout << "Order: "<< *airlift4 << endl;
//    airlift4->validate();
//    airlift4->execute();
//    cout << airlift4->stringToLog() <<endl;


    // Bomb
//    cout << "-------------------- BOMB --------------------" << endl;
//
//    Bomb* bomb1 = new Bomb(player1);
//    cout << "Order: " << *bomb1 << endl;
//    bomb1->validate();
//    bomb1->execute();
//    cout << bomb1->stringToLog() << endl;
//
//    // Target territory is your own territory -> failed
//    Bomb* bomb2 = new Bomb(player2);
//    cout << "Order: " << *bomb2 << endl;
//    bomb2->validate();
//    bomb2->execute();
//    cout << bomb2->stringToLog() << endl;


	// Blockade
//    cout << "\n-------------------- BLOCKADE --------------------\n" << endl;
//	Blockade *blockade1 = new Blockade(player1);
//    cout << "Order: "<< *blockade1 << endl;
//    blockade1->validate();
//    blockade1->execute();
//    cout << blockade1->stringToLog() <<endl;
//
//    Blockade *blockade2 = new Blockade(player1);
//    cout << "Order: "<< *blockade2 << endl;
//    blockade2->validate();
//    blockade2->execute();
//    cout << blockade2->stringToLog() <<endl;
//
//    Blockade *blockade3 = new Blockade(player2);
//    cout << "Order: "<< *blockade3 << endl;
//    blockade3->validate();
//    blockade3->execute();
//    cout << blockade3->stringToLog() <<endl;
//
//    Blockade *blockade4 = new Blockade(player2);
//    cout << "Order: "<< *blockade4 << endl;
//    blockade4->validate();
//    blockade4->execute();
//    cout << blockade4->stringToLog() <<endl;


    // Negotiate
//    cout << "-------------------- NEGOTIATE --------------------" << endl;
//	Negotiate *negotiate1 = new Negotiate(player1);
//	cout << "Order: "<< *negotiate1 << endl;
//    negotiate1->validate();
//    negotiate1->execute();
//    cout<< negotiate1->stringToLog();
//
//    Negotiate *negotiate2 = new Negotiate(player1);
//    cout << "Order: "<< *negotiate2<< endl;
//    negotiate2->validate();
//    negotiate2->execute();
//    cout<< negotiate2->stringToLog();
//
//    Negotiate *negotiate3 = new Negotiate(player2);
//    cout << "Order: "<< *negotiate3 << endl;
//    negotiate3->validate();
//    negotiate3->execute();
//    cout<< negotiate3->stringToLog();

	return 0;
}

//    cout << "Before Assigning" <<endl;
//    cout << "mainmap directly "<< *(mainmap->getTerritories().at(0)) << endl;
//    cout << " From Order " << *(Order::game->getMap()->getTerritories()[0]) << endl;
//    cout << "From mainGE "<< *(mainGE->getMap()->getTerritories()[0]) << endl;

//    cout << "After Assigning" <<endl;
//    cout << "mainmap directly "<< *(mainmap->getTerritories()[0]) << endl;
//    cout << " From Order " << *(Order::game->getMap()->getTerritories()[0]) << endl;
//    cout << "From mainGE "<< *(mainGE->getMap()->getTerritories()[0]) << endl;