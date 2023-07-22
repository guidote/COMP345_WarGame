#include "LoggingObserver.h"
#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Map/Map.h"
#include "../Player/Player.h"
#include "../GameEngine/GameEngine.h"
#include "../CommandProcessing/CommandProcessing.h"

LogObserver* logger = new LogObserver("gamelog.txt");
LogObserver* Subject::logObs = logger;

int LoggingObservermain() {

    /****************************** CLASSES INHERITING FROM SUBJECT & ILOGGABLE *******************************/

    bool subjectGameEngine = is_base_of<Subject, GameEngine>::value;
    bool subjectCommand = is_base_of<Subject, Command>::value;
    bool subjectCommandProcessor = is_base_of<Subject, CommandProcessor>::value;
    bool subjectOrdersList = is_base_of<Subject, OrdersList>::value;
    bool subjectOrder = is_base_of<Subject, Order>::value;

    cout << "\n--------- Inheritance of Class Subject\n" << endl;
    if (subjectGameEngine) { cout << "GameEngine inherits from Subject" << endl;}
    if (subjectCommand) { cout << "Command inherits from Subject"  << endl;}
    if (subjectCommandProcessor) { cout << "CommandProcessor inherits from Subject"  << endl;}
    if (subjectOrdersList) { cout << "OrdersList inherits from Subject" << endl;}
    if (subjectOrder) { cout << "Order inherits from Subject" << endl;}

    bool iloggableGameEngine = is_base_of<Iloggable, GameEngine>::value;
    bool iloggableCommand = is_base_of<Iloggable, Command>::value;
    bool iloggableCommandProcessor = is_base_of<Iloggable, CommandProcessor>::value;
    bool iloggableOrdersList = is_base_of<Iloggable, OrdersList>::value;
    bool iloggableOrder = is_base_of<Iloggable, Order>::value;

    cout << "\n--------- Inheritance of Class Iloggable\n" << endl;
    if (iloggableGameEngine) { cout << "GameEngine inherits from Iloggable\n";}
    if (iloggableCommand) { cout << "Command inherits from Iloggable\n";}
    if (iloggableCommandProcessor) { cout << "CommandProcessor inherits from Iloggable\n";}
    if (iloggableOrdersList) { cout << "OrdersList inherits from Iloggable\n";}
    if (iloggableOrder) { cout << "Order inherits from Iloggable\n";}


    /****************************** Methods using the Observer Pattern *******************************/

    cout << "\n-------------------- GameEngine::transition() --------------------" << endl;
    logger->outputFile  << "\n-------------------- GameEngine::transition() --------------------" << endl;

    GameEngine *mainGE = new GameEngine;

    cout << "In output file: The Game Engine has transitioned to the startstate. " << endl;
    mainGE->transition(start); // contains notify()

    cout << "In output file: The Game Engine has transitioned to the mapLoadedstate. \n" << endl;
    mainGE->transition(mapLoaded); // contains notify()
    MapLoader* loader;
    Map* mainmap = loader->load("../Orders/canada.map");

    cout << "\nIn output file: The Game Engine has transitioned to the mapValidatedstate." << endl;
    mainGE->transition(mapValidated); // contains notify()


    cout << "\n-------------------- CommandProcessor::saveCommand() (File) --------------------" << endl;
    logger->outputFile << "\n-------------------- CommandProcessor::saveCommand() (File) --------------------" << endl;

    cout << "In output file: Saved the following command to the CommandProcessor: addplayer <Audrey>" << endl;
    cout << "In output file: The Game Engine has transitioned to the playersAddedstate.\n" << endl;

    CommandProcessor *cp;
    FileCommandProcessorAdapter *fcpa;
    string fileName = "../LoggingObserver/commandLogObs.txt";
    ifstream input(fileName);
    fcpa = new FileCommandProcessorAdapter(fileName);
    cp = fcpa;
    cp->setEngine(mainGE);
    mainGE->setProcessor(cp);

    cp->getCommand(); // contains SaveCommand()
    Command *command1 = cp->getCommands()[cp->getCommands().size() - 1];

    // Splitting the input into words (if it can be split)
    string effect1 = "";
    string word1 = "";
    string word2 = "";
    bool hasReachedSpace = false;

    for (char i : command1->getCommand()) {
        if (!hasReachedSpace) {
            if (i == ' ') {hasReachedSpace = true;}
            else {word1 += i;}}
        else {if (i != '<' && i != '>') {word2 += i;}}}

    if (word1 == "addplayer") {
        if (mainGE->getplayer_list().size() >= 6) {
            effect1 = "Unable to add Player (6 players reached)";
            cout << effect1 << "!" << endl;}
        else {
            if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                Player *p = new Player(word2);
                mainGE->getplayer_list().push_back(p);
                mainGE->setNumberOfPlayers(mainGE->getNumberOfPlayers()+1);

                effect1 = "Added Player: " + p->getName();
                cout << effect1 << "!" << endl;
                mainGE->transition(playersAdded);}
            else { effect1 = "Unable to add Player";
                    cout << effect1 << "!" << endl;}
        }
    }

    cout << "\n-------------------- CommandProcessor::saveCommand() (Console) --------------------" << endl;
    logger->outputFile << "\n-------------------- CommandProcessor::saveCommand() (Console) --------------------" << endl;

    cout << "In output file: Saved the following command to the CommandProcessor: addplayer <MJ>" << endl;
    cout << "In output file: The Game Engine has transitioned to the playersAddedstate.\n" << endl;
    CommandProcessor *cp2 = new CommandProcessor;
    cp2->setEngine(mainGE);
    mainGE->setProcessor(cp2);

    cout << "Please give a command: " << endl;

    cp2->getCommand(); // Contains SaveCommand()
    Command *command2 = cp2->getCommands()[cp2->getCommands().size() - 1];

    // Splitting the input into words (if it can be split)
    string effect2 = "";
    word1 = "";
    word2 = "";
    hasReachedSpace = false;

    for (char j : command2->getCommand()) {
        if (!hasReachedSpace) {
            if (j == ' ') {hasReachedSpace = true;}
            else {word1 += j;}}
        else {if (j != '<' && j != '>') {word2 += j;}}}

    if (word1 == "addplayer") {
        if (mainGE->getplayer_list().size() >= 6) {
            effect2 = "Unable to add Player (6 players reached)";
            cout << effect2 << "!" << endl;}
        else { if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                Player *p = new Player(word2);
                mainGE->getplayer_list().push_back(p);
                mainGE->setNumberOfPlayers(mainGE->getNumberOfPlayers()+1);
                effect2 = "Added Player: " + p->getName();
                cout << effect2 << "!" << endl;
                mainGE->transition(playersAdded);}
            else {
                effect2 = "Unable to add Player";
                cout << effect2 << "!" << endl;}}}


    cout << "\n-------------------- Command::SaveEffect() --------------------" << endl;
    logger->outputFile << "\n-------------------- Command::SaveEffect() --------------------" << endl;

    cout << "In output file: Command entered: \"addplayer <Audrey>\" changing the Game Engine State to playersadded and having the effect of \"Added Player: MJ\"\n" << endl;
    command1->saveEffect(effect1);

    cout << "In output file: Command entered: \"addplayer <MJ>\" changing the Game Engine State to playersadded and having the effect of \"Added Player: MJ\"" << endl;
    command2->saveEffect(effect2);


    // Create Players List
    vector<Player*> player_list;
    Player* player1 = new Player();
    player1->setReinforcementPool(10); player1->setName("Audrey");
    Player* player2 = new Player();
    player2->setReinforcementPool(12); player2->setName("MJ");
    player_list.push_back(player1); player_list.push_back(player2);

    // Create & Set up Game Engine
    mainGE->setMap(mainmap);
    mainGE->setplayer_list(player_list);
    mainGE->setDeck(new Deck(20));
    Order::game = mainGE;

    // Assign Territories to Players
    int playerIndex = 0;
    for (Territory *i : mainmap->getTerritories()) {
        Player *tempPlayer = player_list.at(playerIndex);
        i->setOwner(tempPlayer);
        tempPlayer->assignTerritory(i);
        playerIndex++;
        if (playerIndex >= player_list.size()) {playerIndex = 0;}}

    Territory* Yukon_Territory = Order::game->getMap()->getTerritories().at(30); Yukon_Territory->setArmies(4);
    Territory* Ontario_South = Order::game->getMap()->getTerritories().at(8); Ontario_South->setArmies(0);
    Territory* Ontario_North = Order::game->getMap()->getTerritories().at(10); Ontario_North->setArmies(0);
    Territory* Quebec_Central = Order::game->getMap()->getTerritories().at(6); Quebec_Central->setArmies(4);
    Territory* Manitoba_South = Order::game->getMap()->getTerritories().at(11); Manitoba_South->setArmies(4);
    Territory* Ontario_West = Order::game->getMap()->getTerritories().at(9); Ontario_West->setArmies(4);
    Territory* Quebec_South = Order::game->getMap()->getTerritories().at(7); Quebec_South->setArmies(0);
    Territory* Quebec_North = Order::game->getMap()->getTerritories().at(5); Quebec_North->setArmies(0);


    cout << "\n-------------------- OrderList::addOrder() --------------------" << endl;
    logger->outputFile << "\n-------------------- OrderList::addOrder() --------------------" << endl;

    Deploy* deploy1 = new Deploy(player1, Ontario_South);
    Deploy* deploy2 = new Deploy(player2, Quebec_North);
    Deploy* deploy3 = new Deploy(player1, Ontario_West);

    cout << "In output file : Added the Order deploy to Audrey's OrderList." << endl;
    cout << "In output file : Added the Order deploy to MJ's OrderList." << endl;
    cout << "In output file : Added the Order deploy to Audrey's OrderList." << endl;
    player1->getOrder()->addOrder(deploy1);
    player1->getOrder()->addOrder(deploy2);
    player1->getOrder()->addOrder(deploy3);

    cout << "\n-------------------- Order::execute() --------------------" << endl;
    logger->outputFile << "\n-------------------- Order::execute() --------------------" << endl;

    cout << "In output file, Deploy execution information for Audrey." << endl;
    cout << "In output file, Deploy execution information for MJ. " << endl;
    cout << "In output file, Deploy execution information for Audrey. " << endl;

    cout << "\n--------- Player 1 Deploy" << endl;
    cout << "Order: " << *deploy1 << endl;
    deploy1->validate();
    deploy1->execute();

    cout << "\n--------- Player 2 Deploy" << endl;
    cout << "Order: " << *deploy2 << endl;
    deploy2->validate();
    cout << "writing stringToLog to output file: " << endl;
    deploy2->execute();

    cout << "\n--------- Player 1 Deploy (Target belongs to another player)" << endl;
    cout << "Order: " << *deploy3 << endl;
    deploy3->validate();
    cout << "writing stringToLog to output file: " << endl;
    deploy3->execute();

    logger->outputFile << "\n-------------------- Closing the gamelog file --------------------" << endl;
    // TESTING FOR ASSIGNMENT 3
/*
    int gameNumber = 2;
    int mapNumber = 2;
    vector<string> processor;
    processor.push_back("Map A");
    processor.push_back("Map B");
    processor.push_back("Map C");

    vector<vector<string>> tournamentResults;
    for (int i = 0; i <= gameNumber+1; i++){
        vector<string> row;
        tournamentResults.push_back(row);
    }
    tournamentResults.at(0).push_back("draw1");
    tournamentResults.at(0).push_back("Neutral");
    tournamentResults.at(0).push_back("Cheater");

    tournamentResults.at(1).push_back("Draw2");
    tournamentResults.at(1).push_back("Neutral");
    tournamentResults.at(1).push_back("Cheater");

    tournamentResults.at(2).push_back("Draw3");
    tournamentResults.at(2).push_back("Neutral");
    tournamentResults.at(2).push_back("Cheater");

    int ws = 15;
    ostringstream resultsTable;
    resultsTable << "Results:\n";
    resultsTable.width(ws);
    resultsTable << " |";

    for (int i = 0; i <= gameNumber; i++){
        resultsTable.width(ws);
        resultsTable << "Game "+ to_string(i+1) + " |";
        }
        resultsTable <<"\n";

    for(int j = 0; j <= mapNumber; j++){
        resultsTable.width(ws);
        resultsTable << processor.at(j) + " |";

        for(int k = 0; k <= gameNumber; k++){
            resultsTable.width(ws);
            resultsTable <<  " " + tournamentResults.at(j).at(k) + " |";
        }

        resultsTable << "\n";
    }

    cout << resultsTable.str();
    */
    Order::logObs->outputFile.close();

    return 0;
}
