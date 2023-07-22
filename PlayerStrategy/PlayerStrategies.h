#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/// Forward declaration of Player
class Player;
/// Forward declaration of Territory
class Territory;
/// Forward declaration of Order
class Order;
/// Forward declaration of Map
class Map;
/// Forward declaration of Hand
class Hand;
/// Forward declaration of GameEngine
class GameEngine;

/**
 Free method to compare strings while ignoring case
 @param string to be compared
 @param string to be compared
 @return Boolean, true if string are equal and false if they are not
 */
bool equalsIgnoreCase(string, string);
/**
 Free method to check if a specific card is in a player hand
 @param string representing the card type (bomb, negotiate, airlift ..etc)
 @param Hand pointer pointing to the hand we are checking
 @return int, index of the card in hand (or -1 if card not in hand)
 */
int checkCardInHand(string, Hand*);

/**
 Class representing the abstract class for different strategy types
 */
class PlayerStrategies {
    ///PlayerStrategies is friend of Player
    friend Player;

    ///PlayerStrategies is friend of GameEngine
    friend GameEngine;

    public:

        /// Default constructor
        PlayerStrategies();

        /**
         * Parameterized constructor that creates new player based on parameters
         * @param string type of player strategy (Human, Aggressive, Benevolent, Cheater, Neutral)
         */
        PlayerStrategies(string type);

        /**
         * Parameterized constructor that creates new player based on parameters
         * @param string type of player strategy (Human, Aggressive, Benevolent, Cheater, Neutral)
         * @param Player pointer pointing to the player the strategy object belongs too
         */
        PlayerStrategies(Player*, string);

        /**
        Copy constructor that creates a deep copy
        @param constant PlayerStrategies reference
        @return pointer to the PlayerStrategies created
        */
        PlayerStrategies(const PlayerStrategies& other);

        /**
         * Virtual Accessor method for Player
         * @return Player pointer
         */
        virtual Player* getPlayer();

        /**
         * Accessor method for strategy type
         * @return string type
         */
        string getType();

        /**
         * Accessor method for boolean flag for neutral player attack
         * @return boolean if a neutral player was attacked
         */
        Player* getNeutralAttack();

        /**
         * VirtualMutator method for setting player
         * @param Player pointer
         */
        virtual void setPlayer(Player*);

        /**
         * Virtual Mutator method for setting neutral attack boolean
         * @param boolean
         */
        virtual void setNeutralAttack(Player*);

        /**
         * Virtual Method to issue orders into the player orderlist
         * @param string input type of order (deploy, advance or a card)type
         */
        virtual void issueOrder(string type) = 0;

        /**
         * Virtual Method to determine which territories the player should attack in priority
         * @return vector of Territory pointers player should attack
         */
        virtual vector<Territory*> toAttack() = 0;

        /**
         * Virtual Method to determine which territories the player should defend in priority
         * @return vector of Territory pointers player should defend
         */
        virtual vector<Territory*> toDefend() = 0;

        /**
        * Assignment Operator overloading to assign a deep copy
        @overload
        @param PlayerStrategies reference that will be copied and assigned
        @return PlayerStrategies reference
        */
        const PlayerStrategies& operator= (const PlayerStrategies &ps);

        /**
        * Friend method to override the stream insertion operator
        * Stream insertion operator (virtual for derived class)
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        virtual ostream& write(ostream &strm) const;
        friend ostream& operator<<(ostream &strm, PlayerStrategies const &cp) { return cp.write(strm); };

        /// A static game Engine to access Map and Deck related
        static GameEngine* game;

    protected:
        /// Player to check if a neutral player has been attacked, will point to attacked neutral player
        Player* neutralAttack;

        /// Player related to strategy object
        Player* p;

        /// Strategy type (Human, Aggressive, Benevolent, Cheater, Neutral)
        string type;
};

/**
 Class representing the the Human Player Strategy implements abstract PlayerStrategies class
 */
class HumanPlayerStrategy : public PlayerStrategies{
    public:
        /// Default constructor
        HumanPlayerStrategy();

        /**
        * Parameterized constructor that creates new player based on parameters
        * @param Player pointer pointing to the player the strategy object belongs too
        */
        HumanPlayerStrategy(Player*);

        /**
        Copy constructor that creates a deep copy
        @param constant HumanPlayerStrategies reference
        @return pointer to the HumanPlayerStrategies created
        */
        HumanPlayerStrategy(const HumanPlayerStrategy& other);

        /**
        * Override Method to issue orders into the player orderlist
        * @param string input type of order (deploy, advance or a card) type
        */
        void issueOrder(string type) override;

        /**
        * Override Method to determine which territories the player should attack in priority
        * @return vector of Territory pointers player should attack
        */
        vector<Territory*> toAttack() override;

        /**
        * Override Method to determine which territories the player should defend in priority
        * @return vector of Territory pointers player should defend
        */
        vector<Territory*> toDefend() override;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param HumanPlayerStrategies reference that will be copied and assigned
        @return HumanPlayerStrategies reference
        */
        const HumanPlayerStrategy& operator= (const HumanPlayerStrategy& humanPs);

        /**
        Method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        ostream& write(ostream &strm) const override;
};

/**
 Class representing the the Aggressive Player Strategy implements abstract PlayerStrategies class
 */
class AggressivePlayerStrategy : public PlayerStrategies{
    public:
        /// Default constructor
        AggressivePlayerStrategy();

        /**
        Parameterized constructor that creates new player based on parameters
        * @param Player pointer pointing to the player the strategy object belongs too
        */
        AggressivePlayerStrategy(Player*);

        /**
        Copy constructor that creates a deep copy
        @param constant AggressivePlayerStrategies reference
        @return pointer to the AggressivePlayerStrategies created
        */
        AggressivePlayerStrategy(const AggressivePlayerStrategy& other);

        /**
        Override Method to issue orders into the player orderlist
        * @param string input type of order (deploy, advance or a card) type
        */
        void issueOrder(string type) override;

        /**
        Override Method to determine which territories the player should attack in priority
        * @return vector of Territory pointers player should attack
        */
        vector<Territory*> toAttack() override;

        /**
        Override Method to determine which territories the player should defend in priority
        * @return vector of Territory pointers player should defend
        */
        vector<Territory*> toDefend() override;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param AggressivePlayerStrategies reference that will be copied and assigned
        @return AggressivePlayerStrategies reference
        */
        const AggressivePlayerStrategy& operator= (const AggressivePlayerStrategy& aggressivePs);

        /**
        Method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        ostream& write(ostream &strm) const override;
};

/**
 Class representing the the Benevolent Player Strategy implements abstract PlayerStrategies class
 */
class BenevolentPlayerStrategy : public PlayerStrategies{
    public:
        /// Default constructor
        BenevolentPlayerStrategy();

        /**
        Parameterized constructor that creates new player based on parameters
        * @param Player pointer pointing to the player the strategy object belongs too
        */
        BenevolentPlayerStrategy(Player*);

        /**
        Copy constructor that creates a deep copy
        @param constant BenevolentPlayerStrategies reference
        @return pointer to the BenevolentPlayerStrategies created
        */
        BenevolentPlayerStrategy(const BenevolentPlayerStrategy& other);

        /**
        Override Method to issue orders into the player orderlist
        * @param string input type of order (deploy, advance or a card) type
        */
        void issueOrder(string type) override;

        /**
        Override Method to determine which territories the player should attack in priority
        * @return vector of Territory pointers player should attack
        */
        vector<Territory*> toAttack() override;

        /**
        Override Method to determine which territories the player should defend in priority
        * @return vector of Territory pointers player should defend
        */
        vector<Territory*> toDefend() override;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param BenevolentPlayerStrategies reference that will be copied and assigned
        @return BenevolentPlayerStrategies reference
        */
        const BenevolentPlayerStrategy& operator= (const BenevolentPlayerStrategy& benevolentPs);

        /**
        Method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        ostream& write(ostream &strm) const override;
};

class NeutralPlayerStrategy  : public PlayerStrategies{
    public:
        /// Default constructor
        NeutralPlayerStrategy();

        /**
        Parameterized constructor that creates new player based on parameters
        * @param Player pointer pointing to the player the strategy object belongs too
        */
        NeutralPlayerStrategy(Player*);

        /**
        Copy constructor that creates a deep copy
        @param constant NeutralPlayerStrategies reference
        @return pointer to the NeutralPlayerStrategies created
        */
        NeutralPlayerStrategy(const NeutralPlayerStrategy& other);

        /**
        Override Method to issue orders into the player orderlist
        * @param string input type of order (deploy, advance or a card) type
        */
        void issueOrder(string type) override;

        /**
        Override Method to determine which territories the player should attack in priority
        * @return vector of Territory pointers player should attack
        */
        vector<Territory*> toAttack() override;

        /**
        Override Method to determine which territories the player should defend in priority
        * @return vector of Territory pointers player should defend
        */
        vector<Territory*> toDefend() override;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param NeutralPlayerStrategies reference that will be copied and assigned
        @return NeutralPlayerStrategies reference
        */
        const NeutralPlayerStrategy& operator= (const NeutralPlayerStrategy& neutralPs);

        /**
        Method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        ostream& write(ostream &strm) const override;
};

class CheaterPlayerStrategy : public PlayerStrategies{
    public:
        /// Default constructor
        CheaterPlayerStrategy();

        /**
        * Parameterized constructor that creates new player based on parameters
        * @param Player pointer pointing to the player the strategy object belongs too
        */
        CheaterPlayerStrategy(Player*);

        /**
        Copy constructor that creates a deep copy
        @param constant CheaterPlayerStrategies reference
        @return pointer to the CheaterPlayerStrategies created
        */
        CheaterPlayerStrategy(const CheaterPlayerStrategy& other);

        /**
        * Override Method to issue orders into the player orderlist
        * @param string input type of order (deploy, advance or a card) type
        */
        void issueOrder(string type) override;

        /**
        * Override Method to determine which territories the player should attack in priority
        * @return vector of Territory pointers player should attack
        */
        vector<Territory*> toAttack() override;

        /**
        * Override Method to determine which territories the player should defend in priority
        * @return vector of Territory pointers player should defend
        */
        vector<Territory*> toDefend() override;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param CheaterPlayerStrategies reference that will be copied and assigned
        @return CheaterPlayerStrategies reference
        */
        const CheaterPlayerStrategy& operator= (const CheaterPlayerStrategy& cheaterPs);

        /**
        Method to override the stream insertion operator
        @overload
        @param output stream reference and the player as a constant reference
        @return output stream reference
        */
        ostream& write(ostream &strm) const override;
};