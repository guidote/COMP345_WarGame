#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/// Forward declaration of Hand
class Hand;
/// Forward declaration of Orderslist
class OrdersList;
/// Forward declaration of Territory
class Territory;
/// Forward declaration of Map
class Map;
/// Forward declaration of Order
class Order;
/// Forward declaration of PlayerStrategies
class PlayerStrategies;

/**
 Class representing the player
 */
class Player {
    public:
        /// Default constructor
        Player();

        /**
        Parameterized constructor that creates a new player based on parameters
        @param string player name
        @param vector of Territory pointers to represent players territory list
        @param hand pointer to represent players hand
        @param orderslist pointer to represent the players order list
        @param int number in players reinforcement pool
        @return pointer to the Player created
        */
        Player(string, vector<Territory*>, Hand*, OrdersList*, int);

        /**
        Parameterized constructor that creates a new player based on parameters
        @param string player name
        @return pointer to the Player created
        */
        Player(string name);

        /**
        Parameterized constructor that creates a new player based on parameters
        @param PlayerStrategy pointer to represent players playing type
        @return pointer to the Player created
        */
        Player(PlayerStrategies* ps);

        /**
        Parameterized constructor that creates a new player based on parameters
        @param PlayerStrategy pointer to represent players playing type
        @param string player name
        @return pointer to the Player created
        */
        Player(PlayerStrategies* ps, string name);

        /**
        Copy constructor that creates a deep copy
        @param constant Players reference
        @return pointer to the Player created
        */
        Player(const Player &p);

        /// Destructor
        ~Player();

        /**
        Method for adding to player reinforcement pool
        @param int number of armies to add to reinforcement pool
        */
        void addToReinforcePool(int armies);

        /**
        Method for removing from player reinforcement pool
        @param int number of armies to remove from reinforcement pool
        */
        void removeFromReinforcePool(int armies);

        /**
        Method for checking if a territory is owned by the player
        @param string name of territory
        @return pointer to Territory of name string parameter name
        */
        Territory* checkTerritoryOwn(string name);

        /**
         * Method for finding a territory owned by player that is adjacent to the territory the player wants to attack
         * @param Territory pointer target_territory territory we are checking for
         * @param Map m map of game
         * @return pointer to Territory of origin
         */
        Territory* getOriginTerritory(Territory* target_territory, Map* m);

        /**
         * Method for adding a single territory to the players territory list
         * @param Territory pointer t
         */
        void assignTerritory(Territory* t);

        /**
         * Method for removing a territory from player territory list by index
         * @param int index
         */
        void removeTerritory(int index);

        /**
         * Method for adding an order to the players orderlist
         * @param Order o
         */
        void addOrderList(Order* o);

        /**
         * Mutator method for player name
         * @param string player name
         */
        void setName(string n);

        /**
         * Mutator method for player hand
         * @param Hand h
         */
        void setHand(Hand* h);

        /**
         * Mutator method for player reinforcement pool
         * @param int armies
         */
        void setReinforcementPool(int armies);

        /**
         * Mutator for player territory list
         * @param vector of Territory pointers t
         */
        void setTerritory(vector<Territory*> t);

        /**
         * Mutator for player orderlist
         * @param OrdersList o
         */
        void setOrder(OrdersList* o);

        /**
         * Mutator for player strategy
         * @param PlayerStrategies ps
         */
        void setStrategy(PlayerStrategies* ps);

        /**
         * Accessor for player name
         * @return string player name
         */
        string getName();

        /**
         * Accessor for player hand
         * @return Hand player hand
         */
        Hand* getHand();

        /**
         * Accessor for player reinforcement pool
         * @return int reinforcement pool
         */
        int getReinforcePool();

        /**
         * Accessor for number of armies player has
         * @return int number of armies
         */
        int getNumberOfArmies();

        /**
         * Accessor for number of Territories player has
         * @return int number of Territories
         */
        int getNumberOfTerritories();

        /**
         * Returns the index of a territory passed on paramater territory name
         * @param string territory name
         * @return int index
         */
        int getTerritoryIndex(string);

        /**
         * Accessor for player orderlist
         * @return OrdersList player order list
         */
        OrdersList* getOrder();

        /**
         * Accessor for player strategy
         * @return PlayerStrategy of player
         */
        PlayerStrategies* getPlayerStrategy();

        /**
         * Accessor for player territory list
         * @return vector of Territory pointers player territory list
         */
        vector<Territory*> getTerritoryList();

        /**
         * Method to determine which territories the player should defend in priority
         * @return vector of Territory pointers player should defend
         */
        vector<Territory*> toDefend();

        /**
         * Method to determine which territories the player should attack in priority
         * @return vector of Territory pointers player should attack
         */
        vector<Territory*> toAttack();

        /**
         * Method to issue orders into the player orderlist
         * Creates an order and adds it to player orderlist
         * @param string input type of order (deploy, advance or a card)
         */
        void issueOrder(string input);

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Player reference that will be copied and assigned
        @return Player reference
        */
        Player& operator = (const Player& player);

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Player& player);

    private:
        /// Name of Player
        string name;

        /// Player hand
        Hand* hand;

        /// Number of reinforcements player has
        int reinforcePool;

        /// List of players territories
        vector<Territory*> territories;

        /// Player list of orders
        OrdersList* orders;

        /// Strategy pattern implementation
        PlayerStrategies* playerStrategy;
};