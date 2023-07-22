#include "GameEngine.h"
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../CommandProcessing/CommandProcessing.h"
#include "../PlayerStrategy/PlayerStrategies.h"

//class OrdersList;
//class Player;

// Default constructor
GameEngine::GameEngine() {
    s = new State;
    *s = null;
    NumberOfPlayers = 0;
    NumberOfTerritories = 0;
    deck = new Deck(20);
    player_list = vector<Player*>();
    map = NULL;
    alliances = set<pair<Player*, Player*>>();

    // Add Neutral Player to Game
    neutralPlayer = new Player();
    neutralPlayer->setName("Neutral");

    int numberOfTurns = 0;
    endOfTournament = false;

}

// Copy constructor
GameEngine::GameEngine(const GameEngine &gm) {
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    deck = gm.deck;
    numberOfTurns = gm.numberOfTurns;

    for (Player* p : gm.player_list) {
        player_list.push_back(p);
    }

    Map *map = gm.map;

    alliances = set<pair<Player*, Player*>>();
    for(auto x : gm.alliances) {
        pair<Player*, Player*> pairCopied = make_pair(x.first, x.second);
        alliances.insert(pairCopied);
    }

    neutralPlayer = gm.neutralPlayer;
}

// Destructor
GameEngine::~GameEngine() {
    delete s;
    s = NULL;

    delete deck;
    deck = NULL;

    for (Player* p : player_list) {
        delete p;
        p = NULL;
    }

    delete map;
    map = NULL;

    for (auto x : alliances) {
        x.first = NULL;
        x.second = NULL;
    }

    delete processor;
    processor = NULL;

    delete neutralPlayer;
    neutralPlayer = NULL;

    for(int i = 0; i<tournamentResults.size()-1; i++) {
        tournamentResults.at(i).clear();
    }
    tournamentResults.clear();
}

// Assignment operator
GameEngine& GameEngine::operator = (const GameEngine& gm) {
    s = gm.s;
    NumberOfPlayers = gm.NumberOfPlayers;
    NumberOfTerritories = gm.NumberOfTerritories;
    phaseEnd = gm.phaseEnd;
    deck = gm.deck;
    neutralPlayer = gm.neutralPlayer;
    for (Player* p : gm.player_list) {
        player_list.push_back(p);
    }

    return *this;
};

// Stream insertion operator
ostream& operator<<(ostream &os, const GameEngine& gm) {
    string p = "";
    for (Player* i : gm.player_list) {
        p += (*i).getName() + " | ";
    }

    return os <<
        "GAME ENGINE: Current state: "<< gm.s <<
        "\n    Players (" << gm.NumberOfPlayers<< "): " <<endl<< p.substr(0, p.length() - 2) <<
        "\n    Number of Territories : (" << gm.NumberOfTerritories << ")" << endl;
}

// Accessors
State *GameEngine::getState() { return s; }
int GameEngine::getNumberOfPlayers() { return NumberOfPlayers; }
//bool GameEngine::endOfState() { return phaseEnd; }
vector<Player*> GameEngine::getplayer_list() { return player_list; }
CommandProcessor *GameEngine::getProcessor() { return processor; }
Map *GameEngine::getMap() { return map; }
Deck *GameEngine::getDeck() { return deck; }
set<pair<Player*, Player*>> GameEngine::getAlliances() { return alliances; }
bool GameEngine::existingAlliance(Player* p1, Player* p2) {
    for (auto x : alliances) {
        if(x.first == p1) {
            if (x.second == p2) {
                return true;
            }
        }
        else if (x.first == p2) {
            if (x.second == p1) {
                return true;
            }
        }
    }
    return false;
}
vector<int> GameEngine::getPlayerOrder() { return playerOrder; }
Player* GameEngine::getNeutralPlayer() { return neutralPlayer; }
bool GameEngine::getIsTournament() { return isTournament; }
int GameEngine::getGameNumber() { return gameNumber; }
int GameEngine::getMapNumber() { return mapNumber; }
vector<vector<string>> GameEngine::getTournamentResults() { return tournamentResults; }
int GameEngine::getNumberOfTurns() { return numberOfTurns; }

// Mutators
void GameEngine::setState(const State &st) { *s = st; }
void GameEngine::setNumberOfPlayers(int x) { NumberOfPlayers = x; }
void GameEngine::setNumberOfTerritories(int x) { NumberOfTerritories = x; }
void GameEngine::setEndOfState(bool b) { phaseEnd = b; }
void GameEngine::setplayer_list(vector<Player*> pl) { player_list = pl; }
void GameEngine::setProcessor(CommandProcessor *cp) { processor = cp; }
void GameEngine::setMap(Map* m) { map = m; }
void GameEngine::setDeck(Deck* d) { deck = d; }
void GameEngine::setAlliances(const set<pair<Player *, Player *>> all) { alliances = all; }
void GameEngine::addAlliances(Player* p1, Player* p2) { alliances.insert(make_pair(p1,p2)); }
void GameEngine::resetAlliances() {
    for(auto x : alliances) {
        x.first = NULL;
        x.second = NULL;
    }
    alliances.clear();
}
void GameEngine::setPlayerOrder(vector<int> po) {
    playerOrder = vector<int>();

    for (int i : po) {
        playerOrder.push_back(i);
    }
}
void GameEngine::setNeutralPlayer(Player* np) { neutralPlayer = np; }
void GameEngine::setIsTournament(bool it) {isTournament = it; }
void GameEngine::setGameNumber(int gn) { gameNumber = gn; }
void GameEngine::setMapNumber(int mn) {mapNumber = mn; }
void GameEngine::setTournamentResults(const vector<vector<string>> tr) {tournamentResults = tr; }
void GameEngine::setNumberOfTurns(int nt) { numberOfTurns = nt; }

// Assign reinforcement phase
void GameEngine::assignReinforcementPhase() {
    transition(assignReinforcement);

    cout << "\nAssign reinforcement phase\n" << endl;
    for (int i = 0; i < NumberOfPlayers; i++) {
        Player *p = player_list.at(playerOrder.at(i));
        int num = floor(p->getNumberOfTerritories() / 3);

        if (num < 3) {
            p->addToReinforcePool(3); // Minimum number of armies per turn for any player is 3
            cout << "Adding 3 armies to reinforcement pool of player " << p->getName() <<endl;
        }
        else {
            p->addToReinforcePool(num);
            cout << "Adding " << num << " armies to reinforcement pool of player " << p->getName() <<endl;
        }

        vector<Territory*> territoriesByContinent;
        int continent_track = 0;
        for (string continent : map->getContinents()) { // Loop through all continents
            bool flag = true;
            territoriesByContinent = map->getContinentTerritories(continent);
            for (Territory *t : territoriesByContinent) { // Loop through territories in each continent to check if they belong to player
                if(!(t->getOwner()->getName() == p->getName())) {
                    flag = false; // Break and set flag false if player does not own territory
                    break;
                }
            }
            if (flag == false) { continue; }
            else {
                int bonus = map->getContinentBonuses().at(continent_track);
                p->addToReinforcePool(bonus);
                cout << "Adding continent bonus " << bonus << " armies to reinforcement pool of player " << p->getName() <<endl;
            }
            continent_track = continent_track+1;
        }
    }
    cout << "\nEnd of assign reinforcement\n" << endl;
}

// Issue order phase
void GameEngine::issueOrdersPhase() {
    cout << "\nStart issue order phase\n" << endl;
    *s = issueOrder;
    string input;

   if (!checkForWinner())
    {

        // Rubric says: Each player's issueOrder() method is called in round-robin fashion during the issue orders phase.
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder.at(i));
            cout << p->getPlayerStrategy()->getType() << endl;
            if (p->getPlayerStrategy()->getType() != "Neutral") {
                cout << "\nIssuing the orders for player " << p->getName() << "\n" << endl;

                int num = p->getReinforcePool();
                // Only issue deploy orders while the player's reinforcement pool contains armies;
                if (num > 0) cout << "Issuing deploy orders" << endl;

                for (int j = 0; j < num; j++) {
                    if(!(p->getTerritoryList().empty())){
                    p->issueOrder("deploy");
                    cout << "Deploy of army " << j + 1 << "/" << num << " issued" << endl;
                    }
                }

                // Issue advance orders

                    cout << "\n" << p->getName() << "'s turn" << endl;
                    cout << "\nIssuing advance orders" << endl;
                if(!(p->getTerritoryList().empty())) {
                    p->issueOrder("advance");
                }
                // Issue card orders
                cout << "\nIssuing card orders" << endl;
                if(!(p->getTerritoryList().empty())) {
                    p->issueOrder("card");
                }
                // Check if Neutral Player was attacked
                if (p->getPlayerStrategy()->getNeutralAttack() != nullptr) {
                    cout << "\n Neutral player was attacked ! Now is aggressive >:( !" << endl;
                    Player *neutralplayer = p->getPlayerStrategy()->getNeutralAttack();
                    AggressivePlayerStrategy *aggressivestrat = new AggressivePlayerStrategy(neutralplayer);
                    neutralplayer->setStrategy(aggressivestrat);
                }
            }
            if(checkForWinner()) {
                cout << "Winner during IssueOrderPhase" <<endl;
                break;}
        }
    }
    endIssueOrderPhase();
}

void GameEngine::endIssueOrderPhase() {
    transition(executeOrder);
    cout << "\nEnd issue order phase\n" << endl;
}

// Checks for deploy orders in orderlist
bool GameEngine::hasMoreDeploy(Player *p) {
    for (Order * o : p->getOrder()->getOrderList()) {
        if (equalsIgnoreCase(o->getDescription(), "deploy")) {
            return true;
        }
    }
    return false;
}

// Execute order phase
void GameEngine::executeOrdersPhase() {
    // First , adding all deploy orders into a separate list and removing them from the original player's lists
    cout << "\nExecuting Deploy Order\n" << endl;

    int playersWithoutDeploy = 0;
    int playersWithoutOrders = 0;
    bool hasMoreDeployOrders = true;
    bool allOrdersDone = false;

    while (hasMoreDeployOrders) {
        // Loop will loop based on the playing order
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder.at(i));

            for(int i = 0; i < p->getOrder()->getOrderList().size(); i++) { // Loop through orders of player orderlist
                if (equalsIgnoreCase(p->getOrder()->getOrderList().at(i)->getDescription(), "deploy")) {
                    p->getOrder()->getOrderList().at(i)->validate();

                    if(!(p->getTerritoryList().empty())) {
                        p->getOrder()->getOrderList().at(i)->execute();
                    }

                    p->getOrder()->remove(i);
                    break;

            }
        }
        }
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder.at(i));
            if (!hasMoreDeploy(p))
                playersWithoutDeploy++;
        }
        if (playersWithoutDeploy == NumberOfPlayers) {
            hasMoreDeployOrders = false;
        }
        else {
            playersWithoutDeploy = 0;
        }
    }

    while (!allOrdersDone) {
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder.at(i));
            for(int i = 0 ; i < p->getOrder()->getOrderList().size(); i++) {
                p->getOrder()->getOrderList().at(i)->validate();
                p->getOrder()->getOrderList().at(i)->execute();
                p->getOrder()->remove(i);
                break;
            }
        }
        for (int i = 0; i < NumberOfPlayers; i++) {
            Player *p = player_list.at(playerOrder.at(i));
            if (p->getOrder()->getOrderList().empty()) {
                playersWithoutOrders++;
                checkPlayers();}
        }
        if (playersWithoutOrders == NumberOfPlayers) {
            allOrdersDone = true;
        }
        else {
            playersWithoutOrders = 0;
        }
    }

    endexecuteOrdersPhase();
}


void GameEngine::endexecuteOrdersPhase() {
    transition(assignReinforcement);
    cout << "\nEnd execute order phase\n" << endl;
}

void GameEngine::winPhase(Player *p) {
    // Adds the result in the correct column of the current game and Map
   tournamentResults.at(gameNumber).push_back(p->getPlayerStrategy()->getType());
    transition(win);
    cout << "Victory for player: " << p->getName() << endl;

}

void GameEngine::drawPhase() {
    // Adds the result in the correct column of the current game and Map
    tournamentResults.at(gameNumber).push_back("Draw");
    transition(win);
    cout << "Draw game." << endl;

}

void GameEngine::endPhase() {
    transition(null);
    cout << "Thank you for Playing Warzone" << endl;
}

void GameEngine::playAgain() {
    transition(null);
    cout << "The Game will restart soon" << endl;
}


void GameEngine::transition(State transitionState) {
    *s = transitionState;
    notify(this);
}

// Free method to determine whether an int vector contains a given int
bool doesContain(vector<int> arr, int in) {
    for (int i : arr) {
        if (i == in) {
            return true;
        }
    }

    return false;
}

// Checks to see if a tournament command has been entered, and manages calling startupCommands
void GameEngine::startupPhase() {
    cout << "Welcome to Warzone!" << endl;

    // Creating the (possibly unused) FileCommandProcessorAdapter
    FileCommandProcessorAdapter *fcpa;

    cout << "Read commands from console or file?" << endl;

    string word1, word2;
    cin >> word1;

    // Catching wrong inputs
    while (word1 != "console" && word1 != "file") {
        cout << "Please try again!" << endl;
        cin >> word1;
    }

    // Creating a new CommandProcessor if reading from the console
    if (word1 == "console") {
        CommandProcessor *temp = new CommandProcessor;
        processor = temp;
    }

    // Creating a new FileCommandProcessorAdapter if reading from a file
    else {
        cout << "Please provide the file name to read from:" << endl;
        cin >> word2;

        bool isValid = false;

        // Catching wrong inputs
        while (!isValid) {
            ifstream input(word2);

            if (input.is_open()) {
                isValid = true;
            } else {
                cout << "Please try again!" << endl;
                cin >> word2;
            }
        }

        fcpa = new FileCommandProcessorAdapter(word2);
        processor = fcpa;
    }

    // Connecting to and from the CommandProcessor
    processor->setEngine(this);
    setProcessor(processor);

    transition(start);

    while (true) {
        cout << "Enter a command: " << endl;

        // Getting the next Command, and accessing it for local use
        processor->getCommand();
        Command *temp = processor->getCommands()[processor->getCommands().size() - 1];

        word1 = "";

        // Splitting the input into words (if it can be split)
        for (char i : temp->getCommand()) {
            if (i == ' ') {
                break;
            }
            else {
                word1 += i;
            }
        }

        if (word1 == "tournament" && processor->validate(temp)) {
            isTournament = true;
            // Tournament Mode Effect
            // M
            string tournamentMaps = "";
            for(string i : processor->getMaps()) {
                tournamentMaps += i + ", ";
            }

            // P
            string tournamentPS = "";
            for(string i: processor->getPlayerStrategies()) {
                tournamentPS += i + ", ";
            }

            string effect ="Tournament mode: \nM: " + tournamentMaps + "\nP: " + tournamentPS + "\nG: " + to_string(processor->getNumberOfGames()) + "\nD: " + to_string(processor->getMaxTurns()) + "\n";
            temp->saveEffect(effect);

            for (int j = 0; j < processor->getNumberOfGames(); j++) {
                gameNumber = j;
                mapNumber = 0;

                // Insert a column in the Results Table
                vector<string> column;
                tournamentResults.push_back(column);

                for (string k : processor->getMaps()) {
                    mapNumber = mapNumber+1;

                    if (mapNumber > 1 || j > 0) {
                        s = new State;
                        *s = null;
                        NumberOfPlayers = 0;
                        NumberOfTerritories = 0;
                        deck = new Deck(20);
                        player_list = vector<Player*>();
                        map = NULL;
                        alliances = set<pair<Player*, Player*>>();

                        // Add Neutral Player to Game
                        neutralPlayer = new Player();
                        neutralPlayer->setName("Neutral");

                        transition(start);
                    }

                    processor->saveCommand(new Command("loadmap", k));
                    startupCommands(true, true);

                    processor->saveCommand(new Command("validatemap"));
                    startupCommands(true, true);

                    for (string ps : processor->getPlayerStrategies()) {
                        processor->saveCommand(new Command("addplayer", "Player " + to_string(player_list.size() + 1) + " (" + ps + ")"));
                        startupCommands(true, true);

                        PlayerStrategies *tempStrategy;
                        Player *tempPlayer = player_list[player_list.size() - 1];

                        if (ps == "Aggressive") {
                            tempStrategy = new AggressivePlayerStrategy(tempPlayer);
                        }
                        else if (ps == "Benevolent") {
                            tempStrategy = new BenevolentPlayerStrategy(tempPlayer);
                        }
                        else if (ps == "Neutral") {
                            tempStrategy = new NeutralPlayerStrategy(tempPlayer);
                        }
                        else if (ps == "Cheater") {
                            tempStrategy = new CheaterPlayerStrategy(tempPlayer);
                        }
                        else {
                            cout << "INVALID PLAYERSTRATEGY: " << ps << "!" << endl;
                        }

                        tempPlayer->setStrategy(tempStrategy);
                    }

                    processor->saveCommand(new Command("gamestart"));
                    startupCommands(true, true);

                    mainGameLoop();

                    if (j < processor->getMaps().size() - 1) {
                        delete deck;
                        deck = NULL;

                        for (Player* p : player_list) {
                            delete p;
                            p = NULL;
                        }

                        delete map;
                        map = NULL;

                        for (auto x : alliances) {
                            x.first = NULL;
                            x.second = NULL;
                        }

                        delete neutralPlayer;
                        neutralPlayer = NULL;

                        numberOfTurns = 0;
                    }

                    cout << "Tournament map " << k << " done!" << endl;
                }
                cout << "Tournament game " << to_string(j+1) << " done!" << endl;
            }

            endOfTournament = true;
            notify(this); //print table results
            cout << "End of the Tournament. Please consult the log file for detailed results." <<endl;

            break;
        }
        else if (word1 != "tournament" && word1 != "") {
            startupCommands(true, false);
            break;
        }
    }
}

// Reads (startup) commands sequentially from the console
void GameEngine::startupCommands(bool skipFirstGetCommand, bool runOnce) {
    while (*s < 5) {
        if (!skipFirstGetCommand) {
            cout << "Enter a command: " << endl;

            // Getting the next Command
            processor->getCommand();
        }

        // Accessing it for local use
        Command *temp = processor->getCommands()[processor->getCommands().size() - 1];

        string effect = "";

        // Making sure the command is in fact valid
        if (processor->validate(temp)) {
            string word1, word2;
            bool hasReachedSpace = false;

            // Splitting the input into words (if it can be split)
            for (char i : temp->getCommand()) {
                if (!hasReachedSpace) {
                    if (i == ' ') {
                        hasReachedSpace = true;
                    }
                    else {
                        word1 += i;
                    }
                }
                else {
                    if (i != '<' && i != '>') {
                        word2 += i;
                    }
                }
            }
            // Use the loadmap <filename> command to select a map from a list of map files as stored in a directory, which results in the map being loaded in the game
            if (word1 == "loadmap") {
                if (!isTournament && map != NULL) {
                    delete map;
                    map = NULL;
                }

                MapLoader loader;
                Map *m = loader.load(word2);

                if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ' && m->isGoodMap) {
                    map = m;

                    effect = "Loaded Map: " + map->getName();
                    cout << effect << "!" << endl;

                    NumberOfTerritories = m->getTerritories().size();

                    transition(mapLoaded);
                }
                else {
                    effect = "Unable to load Map";
                    cout << effect << "!" << endl;

                    delete m;
                    m = NULL;
                }
            }
            // Use the validatemap command to validate the map (i.e. it is a connected graph, etc – see assignment 1)
            else if (word1 == "validatemap") {
                if (map->validate()) {
                    effect = "Validated Map: " + map->getName();
                    cout << effect << "!" << endl;

                    transition(mapValidated);
                }
                else {
                    effect = "Unable to validate Map";
                    cout << effect << "!" << endl;
                }
            }
            // Use the addplayer <playername> command to enter players in the game (2-6 players)
            else if (word1 == "addplayer") {
                if (player_list.size() >= 6) {
                    effect = "Unable to add Player (6 players reached)";
                    cout << effect << "!" << endl;
                }
                else {
                    if (word2.length() > 0 && word2[0] != ' ' && word2[word2.length() - 1] != ' ') {
                        Player *p = new Player(word2);

                        if (!isTournament) {
                            PlayerStrategies *tempStrategy = new HumanPlayerStrategy(p);
                            p->setStrategy(tempStrategy);
                        }

                        player_list.push_back(p);
                        NumberOfPlayers++;

                        effect = "Added Player: " + p->getName();
                        cout << effect << "!" << endl;

                        transition(playersAdded);
                    }
                    else {
                        effect = "Unable to add Player";
                        cout << effect << "!" << endl;
                    }
                }
            }
            else if (word1 == "gamestart") {
                if (player_list.size() < 2) {
                    effect = "Unable to start game (not enough players)";
                    cout << effect << "!" << endl;
                }
                else {
                    int playerIndex = 0;

                    // Fairly distribute all the territories to the players
                    for (Territory *i : map->getTerritories()) {
                        Player *tempPlayer = player_list.at(playerIndex);
                        i->setOwner(tempPlayer);
                        tempPlayer->assignTerritory(i);

                        playerIndex++;

                        if (playerIndex >= player_list.size()) {
                            playerIndex = 0;
                        }
                    }

                    effect = "Distributed Territories to Players";

                    vector<int> tempOrder = vector<int>();

                    // Determine randomly the order of play of the players in the game
                    for (int j = 0; j < player_list.size(); j++) {
                        int randOrder = rand() % player_list.size();

                        while (doesContain(tempOrder, randOrder)) {
                            randOrder = rand() % player_list.size();
                        }

                        tempOrder.push_back(randOrder);
                    }

                    setPlayerOrder(tempOrder);

                    effect += ", randomly determined the order of playing order";

                    for (Player* k : player_list) {
                        // Give 50 initial armies to the players, which are placed in their respective reinforcement pool
                        k->addToReinforcePool(50);

                        // Let each player draw 2 initial cards from the deck using the deck’s draw() method
                        k->getHand()->drawCard(*deck);
                        k->getHand()->drawCard(*deck);
                    }

                    effect += ", gave 50 armies to each Player, and drew 2 cards for each Player";

                    // Switch the game to the play phase
                    transition(assignReinforcement);
                }
            }
            else {
                effect = "Command does not exist";
                cout << effect << "!" << endl;
            }
        }
        else {
            if (temp->isPossibleCommand) {
                effect = "Command is invalid in the current state";
                cout << effect << "!" << endl;
            }
            else {
                effect = "Command does not exist";
                cout << effect << "!" << endl;
            }
        }

        temp->saveEffect(effect);

        if (runOnce) {
            break;
        }
        else {
            skipFirstGetCommand = false;
        }
    }

    notify(this); // FROM SUBJECT
}

// Main game loop, includes reinforcement phase, issue order phase, execute order phase
bool GameEngine::mainGameLoop() {
    bool playing = true;
    bool continueplaying;
    string input;

    while (playing) {
        assignReinforcementPhase(); // Begin reinforcement phase for all players
        issueOrdersPhase(); // Begin issue orders phase for all players
        executeOrdersPhase(); // Begin execute orders phase for all players
        checkPlayers(); // Check if any players need to be removed
        resetAlliances(); // Reset Alliances

        // Track number of Turns in this game
        numberOfTurns++;

        // Win phase is started in check for winner
        playing = !checkForWinner(); // Check for winner
    }

    cout << "done loop" << endl;

    while (!isTournament && *s == 8) {
        cout << "Replay or quit? " << endl;

        processor->getCommand();

        Command *temp = processor->getCommands()[processor->getCommands().size() - 1];

        string command = temp->getCommand();
        string effect = "";

        if (processor->validate(temp)) {
            if (command == "replay") {
                effect = "Replaying game";
                cout << effect << "!" << endl;
                continueplaying = true;

                transition(start);
            }
            else if (command == "quit") {
                effect = "Quitting game";
                cout << effect << "!" << endl;
                continueplaying = false;

                transition(null);
            }
            else {
                if (temp->isPossibleCommand) {
                    effect = "Command is invalid in the current state";
                    cout << effect << "!" << endl;
                }
                else {
                    effect = "Command does not exist";
                    cout << effect << "!" << endl;
                }
            }
        }

        temp->saveEffect(effect);
    }

    return continueplaying;
}

// Check if a player has won by looping through territories and checking owner
bool GameEngine::checkForWinner() {
    // Check to verify that the number of turns is not maxed out
    if (numberOfTurns >= processor->getMaxTurns()) {
        drawPhase();
        return true;
    }

    int lost = 0;
    for (Player* p : player_list) {
        string player = p->getName();
        for (Territory *i : map->getTerritories()) {
            string owner = i->getOwner()->getName();
            if (owner != player) {
                lost = lost + 1;
                break;
            }
        }
        if (lost == 0) {
            winPhase(p);
            return true;
        }
    }

    cout << "\nNo winner, therefore continue\n" << endl;

    return false;
}

// Check that players are still valid, remove players that are not
// Validity : must own at least on territory
void GameEngine::checkPlayers() {
    for (int i = 0; i <player_list.size(); i++) {
        int ordervalue = playerOrder[i];
        Player *p = player_list.at(ordervalue);

        if (p->getNumberOfTerritories() == 0) {
            cout << "\nPlayer " << p->getName() << " has been eliminated\n" <<endl;
            NumberOfPlayers = NumberOfPlayers - 1; // Lowers player count
            player_list.erase(player_list.begin() + playerOrder[i]); // Removes player from player_list

            for (int j = i; j <= player_list.size()-1; j++) { // Removes from playing order
                playerOrder[j] = (playerOrder[j+1]);
            }

            for (int k = 0; k < player_list.size(); k++) { // Accommodates playerOrder for change in playerlist size
                if (playerOrder[k] > ordervalue) {
                    playerOrder[k] = playerOrder[k] - 1;
                }
            }
        }
    }
}

// Check that a card type is in a specific hand
int GameEngine::checkCardInHand(string type, Hand* h) {
    int index = 0; // Returns index of card in hand, -1 if card is not in hand

    for (Card* c : h->hand) {
        if (equalsIgnoreCase(c->getType(), type)) return index;
        index = index + 1;
    }

    return -1;
}

// Checks for returns true for strings that are equal ignoring case
bool GameEngine::equalsIgnoreCase(string s1, string s2) {
   // Change to lower case
   transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
   transform(s2.begin(), s2.end(), s2.begin(), ::tolower);

   if (s1 == s2) {
       return true;
   }
   else {
       return false;
   }
}

// From Iloggable
string GameEngine::stringToLog() {
    string enumStates[] = {"null", "start", "mapLoaded", "mapValidated", "playersAdded", "assignReinforcement",
                           "issueOrder", "executeOrder", "win"};
    string logString = "";
    if (endOfTournament) {
        logString = "The Game Engine has transitioned to the " + enumStates[*s] + "state. The tournament has ended. \n";

        // Following lines help format the Table
        int ws = 15;
        ostringstream resultsTable;
        resultsTable << "Results:\n";
        resultsTable.width(ws);
        resultsTable << " |";

        for (int i = 0; i <= gameNumber; i++) {
            resultsTable.width(ws);
            resultsTable << "Game "+ to_string(i+1) + " |";
        }
        resultsTable <<"\n";

        for(int j = 0; j < mapNumber; j++) {
            resultsTable.width(ws);
            resultsTable << processor->getMaps().at(j) + " |";

            for(int k = 0; k <= gameNumber; k++) {
                resultsTable.width(ws);
                resultsTable <<  " " + tournamentResults.at(k).at(j) + " |";
            }
            resultsTable << "\n";
        }
        logString += resultsTable.str();
    }

    else if     (enumStates[*s] == "win" && numberOfTurns == processor->getMaxTurns()) {
        logString = "The Game Engine has transitioned to the " + enumStates[*s] + "state despite a Draw since the maximum number of turns has been reached for this game. \n";
    }
    else{
        logString = "The Game Engine has transitioned to the " + enumStates[*s] + "state. \n";
    }

    return logString;
}