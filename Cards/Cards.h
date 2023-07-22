#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

/// Forward Declaration to User-Defined class OrdersList
class OrdersList;
/// Forward Declaration to User-Defined class Player
class Player;

/// Class
class Card {
    public:
        /**
        Default constructor
        */
        Card();

        /**
        Parameterized Constructor - initialize type of card
        @param string that is the type of the card
        */
        Card(string type);

        /**
        Copy constructor that creates a deep copy
        @param Card reference
        @return Card created
        */
        Card(Card &anotherCard);

        /**
        Accessor for the type of the Card
        @param None
        @return string that is the type of the card
        */
        string getType() const;

        /**
        constant Method that creates an Order of the card's type
        and then adds it to the Player's Orderslist
        @param OrdersList reference and Player pointer
        @return none
        */
        void play(OrdersList &ordersList, Player* p) const;

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Card as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Card& card); // Over load << operator to print out value in Hand

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Card reference that will be copied and assigned
        @return Card reference
        */
        Card& operator = (const Card& toAssign);

    private:
        /// Card Type from the Following choices: Bomb, Airlift, Blockade, Negotiate,
        string type;
};

class Deck {
    public:
        /**
        Default Constructor
        Initializes the deck vector and the number of Cards to 0
        */
        Deck();

        /**
        Parameterized Constructor
        Will create the Corresponding number of Card Objects
        @param int that is the number of cards in the Deck
        */
        Deck(int numCard);

        /**
        Copy constructor that creates a deep copy of the Deck and its cards
        @param Card reference
        @return Card created
        */
        Deck(Deck &anotherDeck);

        /**
        Destructor
        Deck vector: will delete all Cards in Heap and set the pointers to them to NULL
        */
        ~Deck();

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Deck as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Deck& deck);

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Deck reference that will be copied and assigned
        @return Deck reference
        */
        Deck& operator = (const Deck& toAssign);

        /**
        Method that Draws a random card frm the Deck
        @param none
        @return Card pointer
        */
        Card* draw();

        /// Deck is a vector of Card object
        vector <Card*> deck;
        /// number or Cards in the Deck
        int numCardInDeck;
};

class Hand {
    public:
        /**
        Default Constructor
        Initializes all to 0 or NULL
        */
        Hand();

        /**
        Parameterized Constructor
        Will create the Corresponding number of Card Objects
        @param int that is the number of cards in the Hand
         */
        Hand(int numCardInHand);

        /**
        Copy constructor that creates a deep copy
        @param Hand reference
        @return Hand created
        */
        Hand(Hand &anotherHand);

        /**
        Destructor
        will delete all Cards in Heap and set the pointers to them to NULL
        */
        ~Hand();

        /**
        Friend method to override the stream insertion operator
        @overload
        @param output stream reference and the Hand as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream& os, const Hand& hand);  // << Overloading stream insertion outputs hand vector of Card pointers

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Hand reference that will be copied and assigned
        @return Hand reference
        */
        Hand& operator =(const Hand& toAssign);    // = assignment operator Overloading

        /**
        Method that selects a random card from the Deck and adds it to the Hand
        @param Deck reference
        @return void
        */
        void drawCard(Deck &d);

        /**
        Method that calls the play() method and then adds the card back to the Deck and removes it from the Player's hand
        @param Deck reference
        @return void
        */
        void playCard(int i, Deck &d, OrdersList &l, Player* p);

        /// vector of card pointers
        vector <Card*> hand;
        /// int that represents the cards in hand
        int numCardInHand;
};