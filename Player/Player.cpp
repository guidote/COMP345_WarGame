#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Cards/Cards.h"
#include "PlayerStrategy/PlayerStrategies.h"
#include "Player.h"

// TODO: destructor destroys Player Strategy?

// Default constructor
Player::Player() {
    name = "empty player";
    territories = vector<Territory*>();
    hand = new Hand;
    orders = new OrdersList;
    reinforcePool = 0;
    playerStrategy = NULL;

    //cout << "[Player default constructor]" << endl;
}

// Parameterized constructor (everything)
Player::Player(string n, vector<Territory*> t, Hand* h, OrdersList* o, int r) : name(n), reinforcePool(r) {
    territories = vector<Territory*>();
    for (Territory* i : t) {
        territories.push_back(i);
    }

    hand = new Hand(*h);
    orders = new OrdersList(*o);

    playerStrategy = NULL;

    //cout << "[Player param constructor]" << endl;
}

// Parameterized constructor (name only)
Player::Player(string n) : name(n) {
    territories = vector<Territory*>();
    hand = new Hand;
    orders = new OrdersList;
    reinforcePool = 0;

    playerStrategy = NULL;

    //cout << "[Player param constructor]" << endl;
}

// Parameterized Constructor (Player Strategy only)
Player::Player(PlayerStrategies* initialPs) : playerStrategy(initialPs) {
    name = "empty";
    territories = vector<Territory*>();
    hand = new Hand;
    orders = new OrdersList;
    reinforcePool = 0;
}

// Parameterized Constructor (Player Strategy and name)
Player::Player(PlayerStrategies* initialPs, string n) : playerStrategy(initialPs), name(n) {
    territories = vector<Territory*>();
    hand = new Hand;
    orders = new OrdersList;
    reinforcePool = 0;
}

// Copy constructor
Player::Player(const Player &p) {
    name = p.name;
    territories = vector<Territory*>();
    for (Territory* i : p.territories) {
        territories.push_back(new Territory(*i));
    } // Goes through copying vector of territory pointers, creates new pointers based on value and pushes to copied vector

    hand = new Hand(*(p.hand));
    orders = new OrdersList(*(p.orders));
    reinforcePool = p.reinforcePool;

    playerStrategy = p.playerStrategy;
    //cout << "[Player copy constructor]" << endl;
}

// Destructor
Player::~Player() {
    delete hand;
    hand = NULL;
    delete orders;
    orders = NULL;

    //cout << "[Player destructor]" << endl;
}

vector<Territory*> Player::toDefend() {
    vector<Territory*> returnTeriList = playerStrategy->toDefend();
    return returnTeriList;
}

vector<Territory*> Player::toAttack() {
    vector<Territory*> returnTeriList = playerStrategy->toAttack();
    return returnTeriList;
}

void Player::issueOrder(string input) {
    playerStrategy->issueOrder(input);
}

// Return bool based on if territory is owned by player
Territory* Player::checkTerritoryOwn(string name) {
    transform(name.begin(), name.end(), name.begin(), ::tolower);
    for (Territory* t : territories) {
        string comparename = t->getName();
        transform(comparename.begin(), comparename.end(), comparename.begin(), ::tolower);t->getName();
        if (name == comparename) return t;
    }
    return NULL;
}
// Return number of armies player has
int Player::getNumberOfArmies() {
    int sum = 0;

    for (Territory* i : territories) {
        sum = sum + i->getArmies();
    }

    return sum;
}

// Return number of territories player has
int Player::getNumberOfTerritories() {
    int sum = 0;

    if (territories.empty()) {
        return 0;
    }

    for (Territory* i : territories) {
        sum = sum + 1;
    }

    return sum;
}

// Return index of Territory based on name
int Player::getTerritoryIndex(string name) {
    int index = 0;
    for (Territory* t : territories) {
        if (equalsIgnoreCase(t->getName(), name)) return index;
        index =  index + 1;
    }
    return -1;
}

// Return an origin territory adjacent to a target territory
Territory* Player::getOriginTerritory(Territory *target_territory, Map* m) {
    vector<Territory*> surround_territory = m->getConnectedTerritories(target_territory->getName());
    for (Territory* t : surround_territory) {
        if (t->getOwner()->getName() == name) return t;
    }

    return NULL;
}

void Player::addToReinforcePool(int armies) { reinforcePool += armies; }
void Player::removeFromReinforcePool(int armies) { reinforcePool = reinforcePool - armies; }
void Player::addOrderList(Order *o) { orders->addOrder(o); }

// Mutators and Accessors
void Player::setName(string n) { name = n; }
void Player::setTerritory(vector<Territory*> t) {
    for (Territory* i : t) {
        territories.push_back(i);
    }
}
void Player::assignTerritory(Territory* t) { territories.push_back(t); }
void Player::removeTerritory(int index) { territories.erase(territories.begin()+index); }

void Player::setHand(Hand* h) { hand = h; }
void Player::setOrder(OrdersList* o) { orders = o; }
void Player::setReinforcementPool(int armies) { reinforcePool = armies; }
void Player::setStrategy(PlayerStrategies* newPs) {
    playerStrategy = newPs;
}

string Player::getName() { return name; }
vector<Territory*> Player::getTerritoryList() { return territories; }
Hand* Player::getHand() { return hand; }
OrdersList* Player::getOrder() { return orders; }
int Player::getReinforcePool(){ return reinforcePool; }
PlayerStrategies* Player::getPlayerStrategy() { return playerStrategy; }

// End of Mutators and Accessors

// Assignment operator
Player& Player::operator = (const Player& p) {
    name = p.name;

    for (Territory* i : p.territories) {
        this->territories.push_back(i);
    }

    hand = p.hand;
    orders = p.orders;
    reinforcePool = p.reinforcePool;

    return *this;
}

// Stream insertion operator
std::ostream& operator<<(std::ostream &strm, const Player &p) {
    string t = "";

    for (Territory* i : p.territories) {
        t += (*i).getName() +" | ";
    }

    return strm <<
        "PLAYER: " << p.name <<
        "\n    Strategy: " << p.playerStrategy->getType() <<
        "\n    Territories: " <<endl<< t.substr(0, t.length() - 2) <<
        "\n    Players hand, " << *p.hand <<
        "\n    Players orders, " << *p.orders <<
        "\n    Players reinforcement pool has, " << p.reinforcePool << " armies"<<endl;
}