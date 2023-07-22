#include "Cards.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

int cardsMain() {
    Deck *mainDeck = new Deck(10);
    Player *player1 = new Player();

    cout << "\n--------------------------------Deck--------------------------------" << endl;
    cout << *mainDeck << endl;

    cout << "\n--------------------------------Drawn Card--------------------------------" << endl;
    player1->getHand()->drawCard(*mainDeck);
    player1->getHand()->drawCard(*mainDeck);
    player1->getHand()->drawCard(*mainDeck);
    player1->getHand()->drawCard(*mainDeck);
    player1->getHand()->drawCard(*mainDeck);

    cout << "\n\n--------------------------------Remaining Deck--------------------------------" << endl;
    cout << *mainDeck << endl;

    cout << "\n--------------------------------Player1 Hand--------------------------------" << endl;
    cout << *player1->getHand() << endl;

    cout << "\n******************************* Play Card *******************************" << endl;
    player1->getHand()->playCard(4, *mainDeck, *player1->getOrder(), player1);
    player1->getHand()->playCard(3, *mainDeck, *player1->getOrder(), player1);
    player1->getHand()->playCard(0, *mainDeck, *player1->getOrder(), player1);

    cout << endl;
    cout << *(player1->getOrder());

    cout << endl;
    cout << *(player1->getHand()) << endl;


    cout << "\n--------------------------------Deck (added played cards)--------------------------------" << endl;
    cout << *mainDeck << endl;

    // Assignment Operator
    cout << "\n******************************* Assignment Operator Checking *******************************" << endl;
    Deck *assignDeck = new Deck(*mainDeck);
    cout << *assignDeck << endl;

    cout << endl;

    Hand *assignHand = new Hand(*player1->getHand());
    cout << *assignHand << endl;

    cout << endl;

    cout << "> AssignHand draws 2 cards from assignDeck: ";
    assignHand->drawCard(*assignDeck);
    assignHand->drawCard(*assignDeck);

    cout << "\n" << endl;
    cout << *assignHand << endl;
    cout << endl;
    cout << *assignDeck << endl;

    cout << "\n> AssignHand plays all cards:" << endl;
    assignHand->playCard(3, *assignDeck, *player1->getOrder(), player1);
    assignHand->playCard(1, *assignDeck, *player1->getOrder(), player1);
    assignHand->playCard(0, *assignDeck, *player1->getOrder(), player1);
    assignHand->playCard(0, *assignDeck, *player1->getOrder(), player1);
    cout << endl;
    cout << *player1->getOrder() << endl
    ;
    cout << *assignHand << endl;
    cout << endl;
    cout << *assignDeck << "\n" << endl;

    // Copy constructor
    cout << "\n******************************* Copy Constructor Checking *******************************" << endl;
    Deck *copyDeck = new Deck(*mainDeck);
    cout << *copyDeck << endl;

    cout << endl;

    Hand *copyHand = new Hand(*player1->getHand());
    cout << *copyHand << endl;

    cout << endl;

    cout << "> Copyhand draws 2 cards from copyDeck: ";
    copyHand->drawCard(*copyDeck);
    copyHand->drawCard(*copyDeck);

    cout << "\n" << endl;
    cout << *copyHand << endl;
    cout << endl;
    cout << *copyDeck << endl;

    cout << "\n> CopyHand plays 2 cards:" << endl;
    copyHand->playCard(1, *copyDeck, *player1->getOrder(), player1);
    copyHand->playCard(0, *copyDeck, *player1->getOrder(), player1);
    cout << endl;
    cout << *player1->getOrder() << endl;

    cout << *copyHand << endl;
    cout << endl;
    cout << *copyDeck << "\n" << endl;

    return 0;
}