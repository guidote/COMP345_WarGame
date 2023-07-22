#include "Cards.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

/*********************************** CARD ***********************************/
Card::Card() {
//    cout << "Card Default Constructor" << endl;
    type = " ";
}

Card::Card(string theType) {
//    cout << "Card Parameterized Constructor" << endl;
    type = theType;
}

Card::Card(Card &anotherCard) {
//    cout << "Card Copy Constructor" << endl;
    type = anotherCard.type;
}

string Card::getType() const {
    return type;
}

void Card::play(OrdersList &playerOrdersList, Player* p) const {
    //Creat Order of the corresponding type
    if (type == "bomb") {
        cout << "Play Bomb card" << endl;
        Bomb* myBomb = new Bomb(p); // Create a Bomb object and play as an order
        playerOrdersList.addOrder(myBomb); // Place it in the OrdersList
    }  else if (type == "blockade") {
        cout << "Play Blockade card" << endl;
        Blockade* myBlockade = new Blockade(p);
        playerOrdersList.addOrder(myBlockade);
    } else if (type == "airlift") {
        cout << "Play Airlift card" << endl;
       Airlift* myAirlift = new Airlift(p);
       playerOrdersList.addOrder(myAirlift);
    } else if (type == "diplomacy") {
        cout << "Play Negotiate card" << endl;
        Negotiate *myNegotiate = new Negotiate(p);
        playerOrdersList.addOrder(myNegotiate);
    } else {
        cout << "Invalid card, play() can not be called!" << endl;
    }
}

ostream& operator<<(ostream& os, const Card& c) {
    os << c.getType();
    return os;
}

Card& Card::operator = (const Card &toAssign) {
    type = toAssign.type;
    return *this;
}

/*********************************** DECK ***********************************/
Deck::Deck() {
//    cout << "Deck Default Constructor" << endl;
    srand (time(NULL));
    numCardInDeck = 0;
    deck = vector<Card*>();
}

Deck::Deck(int numCard) {
//    cout << "Deck Parameterized Constructor" << endl;
    srand(time(NULL));
    numCardInDeck = numCard;
    if (numCardInDeck % 5 != 0) {
        cout << "The number of cards you entered is not divisible by 5. "
                "A default deck of 50 cards will be used instead." << endl;
        numCardInDeck = 50;
    }

    deck = vector<Card*>();

    for (int i = 0; i < numCardInDeck; i++) {
        if (i % 4 == 0) {
            deck.push_back(new Card("bomb"));
        } else if (i % 4 == 1) {
            deck.push_back(new Card("blockade"));
        } else if (i % 4 == 2) {
            deck.push_back(new Card("airlift"));
        } else {
            deck.push_back(new Card("diplomacy"));
        }
    }
}

Deck::Deck(Deck &anotherDeck) {
//    cout << "Deck Copy Constructor" << endl;
    srand(time(NULL));
    numCardInDeck = anotherDeck.numCardInDeck;

    deck = vector<Card*>();
    for (int i = 0; i < anotherDeck.numCardInDeck; i++) {
        Card* cards = new Card(*anotherDeck.deck.at(i));
        deck.push_back(cards);
    }
}

Deck::~Deck() {
    for (int i = 0; i < deck.size(); i++) {
        delete deck.at(i);
        deck.at(i) = NULL;
//        cout << "...deleting Cards in Deck" << endl;
    }
//    cout << "Deck deleted " <<  endl;
    deck.clear();
}

Card* Deck::draw() {
    // Generate a random number
    int numRandom = rand() % numCardInDeck;

    // keep a copy of the returned card in a temp var
    Card * temp = deck.at(numRandom);

    // Display the type of card that is drawn
     cout << *deck.at(numRandom) << " | ";

    // Remove the drawn card from Deck
    deck.erase(deck.begin()+numRandom);
    numCardInDeck--;
    return temp;
}

ostream& operator<<(ostream& os, const Deck& d) {
    os << "Number of card in deck: " << d.numCardInDeck << endl;
    for(int i = 0; i < d.numCardInDeck; i++) {
        os << *(d.deck.at(i)) << " | ";
    }
    return os;
}

Deck& Deck::operator = (const Deck& toAssign) {
    numCardInDeck = toAssign.numCardInDeck;
    deck = toAssign.deck;
    return *this;
}

/*********************************** HAND ***********************************/
// Default Constructor
Hand::Hand() {
    numCardInHand = 0;
    hand = vector<Card*>();
    //cout << "Hand Default Constructor" << endl;
}

// Parameterized Constructor
Hand::Hand(int numCardInHand){
    this->numCardInHand = numCardInHand;
    hand = vector<Card*>();
}

Hand::Hand(Hand &anotherHand) {
    numCardInHand = anotherHand.numCardInHand;
    hand = vector<Card*>();

    for (int i = 0; i < anotherHand.numCardInHand; i++) {
        Card* cards = new Card(*anotherHand.hand.at(i));
        hand.push_back(cards);
    }
    //cout << "Hand Copy Constructor" << endl;
}

Hand::~Hand() {
    for (int i = 0; i < hand.size(); i++) {
        delete hand.at(i);
        hand.at(i) = NULL;
//        cout << "...delete Cards on Hand" << endl;
    }
    hand.clear();
//    cout << "Hand deleted" << endl;
}

ostream& operator<<(ostream& os, const Hand& h) {
    os << "Number of cards on hand: " << h.numCardInHand << endl;

    for(int i = 0; i < h.numCardInHand; i++) {
        os << i << "-" << *(h.hand.at(i)) << " | ";
    }

    return os;
}

Hand& Hand::operator = (const Hand& toAssign) {
    numCardInHand = toAssign.numCardInHand;
    hand = toAssign.hand;
    return *this;
}

void Hand::drawCard(Deck& d) {
    Card* drawnCard = d.draw();
    // Put the drawn card into Player hand
    hand.push_back(drawnCard);
    numCardInHand++;
}

void Hand::playCard(int i, Deck &d, OrdersList &l, Player* p) {
    // Create Order and add Order to OrderList
    hand.at(i)->play(l, p);

    // Add the played Card back to deck
    Card* playedCard =hand.at(i);
    d.deck.push_back(playedCard);
    d.numCardInDeck++;

    // Remove card from Hand
    hand.erase(hand.begin()+i); // Delete the card object along with its pointer
    numCardInHand--;
}