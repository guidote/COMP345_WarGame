#pragma once

#include <vector>
#include <iostream>
#include <set>
#include <cmath>
#include <sstream>

using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

/// Forward declaration of Player
class Player;
/// Forward declaration of MapLoader
class MapLoader;
/// Forward declaration of Deck
class Deck;
/// Forward declaration of Hand
class Hand;
/// Forward declaration of CommandProcessor
class CommandProcessor;
/// Forward declaration of Map
class Map;

/**
 Free method to determine whether an int vector contains a given int
 @param vector<int> vector to be compared
 @param int to be checked if in vector
 @return Boolean, true if int is in vector else false
 */
bool doesContain(vector<int>, int);

/// Structure that represents the phases of the Game
enum State {
   null = 0, start = 1, mapLoaded = 2, mapValidated = 3, playersAdded = 4, assignReinforcement = 5, issueOrder = 6, executeOrder = 7, win = 8
};

/**
 Class that represents the GameEngine where the game is played
 Inherits from Iloggable and Subject to implement a modified Observer Pattern
 */
class GameEngine : public Iloggable, public Subject {
    public:
        /**
        Default constructor
        */
        GameEngine() ;

        /**
        Copy constructor that creates a deep copy
        @param Order reference
        @return Order created
        */
        GameEngine(const GameEngine &gm);

        /**
        Destructor
       deletes objects allocated in Heap, Iterates through Vector of pointers to delete the objects, sets pointer to null
        */
        ~GameEngine();

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Order reference that will be copied and assigned
        @return Order reference
        */
        GameEngine& operator = (const GameEngine& gm);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Order as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const GameEngine& gm);

        /**
        Accessor for the State of the game
        @param None
        @return structure State (enum)
        */
        State *getState();

        /**
        Accessor for the number of Players in the game
        @param None
        @return int that is the number of players in the game
        */
        int getNumberOfPlayers();
        //bool endOfState ();

        /**
        Accessor for the list of players in the game
        @param None
        @return vector of Player pointers
        */
        vector<Player*> getplayer_list();

        /**
        Accessor for the CommandProcessor of the game
        @param None
        @return CommandProcessor pointer
        */
        CommandProcessor *getProcessor();

        /**
        Accessor for the Map of the game
        @param None
        @return Map pointer
        */
        Map *getMap();

        /**
        Accessor for the Deck of the game
        @param None
        @return Deck pointer
        */
        Deck *getDeck();

        /**
        Accessor for the alliances in the current turn of the game
        @param None
        @return set of pairs of Player pointers
        */
        set<pair<Player*, Player*>> getAlliances();

        /**
        Accessor for the player Order (random) of the game
        @param None
        @return vector of ints
        */
        vector<int> getPlayerOrder();

//        /**
//        Accessor for the current player index in the Order
//        @param None
//        @return int index in the Order of players
//        */
//        int getCurrentPlayer();

        /**
        Accessor for the Neutral Player of the game
             Not to be confused with the Neutral PlayerStrategy
        @param None
        @return Player pointer
        */
        Player* getNeutralPlayer();

        /**
        Accessor for the boolean representing is the program is in tournament mode
        @param None
        @return bool
        */
        bool getIsTournament();

        /**
        Accessor for the game number in the tournament
        @param None
        @return int that is the game number
        */
        int getGameNumber();

        /**
        Accessor for the map number in the tournament
        @param None
        @return int that is the map number
        */
        int getMapNumber();

        /**
        Accessor for the results of the tournament mode
        @param None
        @return 2D vector with the name of the winning strategies
        */
        vector<vector<string>> getTournamentResults();

        /**
        Accessor for the number of turns in the current game
        @param None
        @return int that is the number of turns completed
        */
        int getNumberOfTurns();

        /**
        Mutator for State of the game
        @param State (enum) reference
        @return None
        */
        void setState(const State &s);

        /**
        Mutator for the number of players in the game
        @param int that is the number of players
        @return None
        */
        void setNumberOfPlayers(int x);

        /**
        Mutator for number of Territories in the game's Map
        @param int that is the number of Territories
        @return None
        */
        void setNumberOfTerritories(int x);

        /**
        Mutator for the boolean indicator of the end of the current State of the game
        @param bool
        @return None
        */
        void setEndOfState(bool b);

        /**
        Mutator for Player list of the game
        @param vector of Player pointers
        @return None
        */
        void setplayer_list(vector<Player*>);

        /**
        Mutator for CommandProcessor of the game
        @param CommandProcessor pointer
        @return None
        */
        void setProcessor(CommandProcessor*);

        /**
        Mutator for Map of the game
        @param Map pointer
        @return None
        */
        void setMap(Map*);

        /**
        Mutator for Deck of the game
        @param Deck pointer
        @return None
        */
        void setDeck(Deck*);

        /**
        Mutator for the alliances in the current turn of the game
        @param set of pairs of Player pointers
        @return None
        */
        void setAlliances (set<pair<Player*, Player*>>);

        /**
        Method to add an alliance in the current turn
             To be called by playing a Negotiate Card
        @param 2 Player pointers
        @return None
        */
        void addAlliances(Player*, Player*);

        /**
        Method to clear out the alliances created during a turn
          called at the end of every turn
        @param None
        @return None
        */
        void resetAlliances();

        /**
        Mutator for the Order of the Players
        @param vector of ints
        @return None
        */
        void setPlayerOrder(vector<int>);

//        /**
//        Mutator for the current Player index
//        @param int
//        @return None
//        */
//        void setCurrentPlayer(int);

        /**
        Mutator for the Neutral Player of the game
        @param Player pointer
        @return None
        */
        void setNeutralPlayer(Player* np);

        /**
        Mutator for the boolean indicator that it is the end of the tournament
        @param bool
        @return None
        */
        void setIsTournament(bool);

        /**
        Mutator for the game number (tournament mode only)
        @param int that is the game number
        @return None
        */
        void setGameNumber(int);

        /**
        Mutator for the map number (tournament mode only)
        @param int that is the map number
        @return None
        */
        void setMapNumber(int);

        /**
        Mutator for the results (draw or winning strategy) of each game (tournament mode only)
        @param 2D Vector of strings
        @return None
        */
        void setTournamentResults(vector<vector<string>>);

        /**
        Mutator for the number of turns in the current game (tournament mode only)
        @param int that is the number of turns
        @return None
        */
        void setNumberOfTurns(int);

        /**
         Method to determine and distribute the number of Armies to be added to each Player's reinforcement pool at the beginning of a turn
         Will consider the Player's number of territories under their ownership and any continent bonus
         @param None
         @return void
         */
        void assignReinforcementPhase();

        /**
        Method to pursue the IssueOrders Phase of the game. Will force all possible Deploys of each Players, followed by Advance Orders and finally, with Card Orders.
        @param None
        @return void
        */
        void issueOrdersPhase();

        /**
        Method to transition towards the next phase and close the IssueOrder phase
        @param None
        @return void
        */
        void endIssueOrderPhase();

        /**
        Method to iterate through the Player's OrdersList to check if there are any other Deploy Orders left
        @param Player pointer
        @return void
        */
        bool hasMoreDeploy(Player*);

        /**
        Method to execute the Player's order in a round-robin fashion
        @param None
        @return void
        */
        void executeOrdersPhase();

        /**
        Method to transition towards the next phase and close the Execute Orders phase
        @param None
        @return void
        */
        void endexecuteOrdersPhase();

            /**
        Method to transition towards the win phase
        @param None
        @return void
        */
        void winPhase(Player*);

        /**
        Method to transition towards the win phase after the maximum of turns has been reached (tournament mode only)
        @param None
        @return void
        */
        void drawPhase();

         /**
        Method to transition  out of the win phase
        @param None
        @return void
        */
        void endPhase();

        /**
        Method to transition into a start phase to restart a game
        @param None
        @return void
        */
        void playAgain();

        /**
        Supporting Method to transition from one phase to another
        calls StringToLog() to implement a modified Observer Pattern
        @param State (enum)
        @return void
        */
        void transition(State);

        /**
        Method that implements the main game. Includes the Player's turns, Issue Order adn Execute Phases until there is a win or a draw.
        @param none
        @return bool
        */
        bool mainGameLoop();

        /**
        Method to checks if a tournament command has been entered, and manages calling startupCommands
        @param none
        @return void
        */
        void startupPhase();

        /**
        Method that reads (startup) commands sequentially from the console
        @param none
        @return void
        */
        void startupCommands(bool, bool);

        /**
        Method that verifies if there is an Existing Alliance between 2 players
         Called upon by attacking Orders in their validate()
        @param 2 Player pointers
        @return bool if there is an alliance
        */
        bool existingAlliance(Player*, Player*);

        /**
        Method that verifies if there is a winner by checking if a Player owns all Territories
         Also checks if the maximum number of turns has been reached (tournament mode only)
        @param none
        @return bool if there is a winner or a draw
        */
        bool checkForWinner();

        /**
        Method that checks that players are still valid, remove players that are not
           Validity : must own at least on territory
        @param none
        @return none
        */
        void checkPlayers();


        /**
        Method that checks hat a card type is in a specific hand
        @param string that is the Card Type, Hand pointer
        @return int that is the index of the card wanted in the Hand
        */
        int checkCardInHand(string, Hand*);

        /**
        Method that changes string into lowercase to avoid conflicts of that nature, then compares them
        @param 2 strings to be transformed and compared
        @return bool if they are equal
        */
        bool equalsIgnoreCase(string, string);

        /**
         Method inherited from Iloggable to generate a output when an Order will be executed to
         notify the LogObserver and print an entry in the gamelogOutput.txt file
         */
        string stringToLog() override;

    private:
        /// State of GameEngine, what stage is game in
        State* s;
        /// Number of Players playing game
        int NumberOfPlayers;
        /// Total number of Territories
        int NumberOfTerritories;
        /// End of the current Phase of the game
        bool phaseEnd;
        /// Deck of the Game
        Deck *deck;
        /// Player list of the game
        vector<Player*> player_list;
        /// Command Processor
        CommandProcessor *processor;
        /// Map of the game
        Map *map;
        /// Alliances in the current turn
        set<pair<Player*, Player*>> alliances;
        /// Player Order (random)
        vector<int> playerOrder;
//        /// index of the current player in the Order vector
//        int currentPlayer;
        /// Neutral Player for the Blockade Card
        Player* neutralPlayer;

        /// Tournament Specific members
        bool isTournament;
        /// Tournament has completed the last game of the last Map
        bool endOfTournament;
        /// Track the game being played
        int gameNumber;
        /// Track the map being played
        int mapNumber;
        /// Store the results of each game
        vector<vector<string>> tournamentResults;
        /// Track number of turns in current game
        int numberOfTurns;
};