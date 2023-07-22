#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "Map.h"

// Free method to determine whether a string vector contains a given string
bool doesContain(vector<string> arr, string s) {
    for (string i : arr) {
        if (i == s) {
            return true;
        }
    }

    return false;
}

// Free method to determine whether an Edge vector contains an Edge between the given Territories
bool doesContain(vector<Edge*> arr, Territory *t1, Territory *t2) {
    for (Edge *i : arr) {
        string n1 = i->a->getName();
        string n2 = i->b->getName();
        string n3 = t1->getName();
        string n4 = t2->getName();

        if ((n1 == n3 && n2 == n4) || (n1 == n4 && n2 == n3)) {
            return true;
        }
    }

    return false;
}

// Free method to split a given string into a string vector based on a given delimiter
vector<string> stringSplit(string s, char delim) {
    vector<string> result = vector<string>();
    int indexChecker = 0;
    string temp = "";

    // Looping through all the characters in the string
    for (char i : s) {
        // Adding to the current word if a delimiter has not been reached
        if (i != delim) {
            temp += i;
        }

        // Adding the new word to the pointer array if a delimiter or the end has been reached
        if (i == delim || indexChecker == s.length() - 1) {
            result.push_back(temp);
            temp = "";
        }

        indexChecker++;
    }

    return result;
}

// Territory default constructor
Territory::Territory() {
    name = "";
    continent = "";
    owner = NULL;
    armies = 0;
    
    //cout << "[Territory default constructor]" << endl;
}

// Territory parameterized constructor
Territory::Territory(string n, string c, Player *o, int a) : name(n), continent(c), armies(a) {
    owner = o;

    //cout << "[" << n << " Territory param constructor]" << endl;
}

// Territory copy constructor
Territory::Territory(const Territory &t) {
    name = t.name;
    continent = t.continent;
    owner = t.owner;
    armies = t.armies;
    
    //cout << "[" << t.name << " Territory copy constructor]" << endl;
}

// Territory destructor
Territory::~Territory() {
    owner = NULL;
    //cout << "[" << name << " Territory destructor]" << endl;
}

// Territory stream insertion operator
ostream& operator<<(ostream &strm, const Territory &t) {
    string temp;

    if (t.owner == NULL) {
        temp = "null";
    }
    else {
        temp = t.owner->getName();
    }

    return strm <<
        "[TERRITORY PRINT: " << t.name << "]" <<
        endl << "[--- Continent: " << t.continent << " ---]" <<
        endl << "[--- Owner: " << temp << " ---]" <<
        endl << "[--- Armies: " << t.armies << " ---]";
}

// Territory assignment operator
Territory& Territory::operator = (const Territory& toAssign){
    name = toAssign.name;
    continent = toAssign.continent;
    owner = toAssign.owner;
    armies = toAssign.armies;
    return *this;
}

// Territory accessors
string Territory::getName() { return name; }
string Territory::getContinent() { return continent; }
Player *Territory::getOwner() { return owner; }
string Territory::getOwnerName() { return owner->getName(); }
int Territory::getArmies() { return armies; }

// Territory mutators
void Territory::setName(string n) { name = n; }
void Territory::setContinent(string c) { continent = c; }
void Territory::setOwner(Player *o) { owner = o;}
void Territory::setArmies(int a) { armies = a; }

// Map default constructor
Map::Map() {
    name = "";
    continents = vector<string>();
    continentBonuses = vector<int>();
    territories = vector<Territory*>();
    edges = vector<Edge*>();

    //cout << "[Map default constructor]" << endl;
}

// Map parameterized constructor
Map::Map(string n) : name(n) {
    continents = vector<string>();
    continentBonuses = vector<int>();
    territories = vector<Territory*>();
    edges = vector<Edge*>();
    
    //cout << "[" << n << " Map param constructor]" << endl;
}

// Map copy constructor
Map::Map(const Map &m) {
    name = m.name;
    setContinents(m.continents);
    setContinentBonuses(m.continentBonuses);
    setTerritories(m.territories);
    setEdges(m.edges);

    //cout << "[" << m.name << " Map copy constructor]" << endl;
}

// Map destructor
Map::~Map() {
    for (Territory *i : territories) {
        delete i;
        i = NULL;
    }

    for (Edge *j : edges) {
        delete j;
        j = NULL;
    }

    //cout << "[" << name << " Map destructor]" << endl;
}

// Map stream insertion operator
ostream& operator<<(ostream &strm, const Map &m) {
    string c = "";
    string t = "";
    string e = "";

    // Creating a long deliminated string of all the continents
    for (string i : m.continents) {
        c += i + " | ";
    }

    // Creating a long deliminated string of all the territories
    for (Territory *j : m.territories) {
        t += j->getName() + " | ";
    }

    // Creating a long deliminated string of all the Edges
    for (Edge *k : m.edges) {
        e += k->a->getName() + " and " + k->b->getName() + " | ";
    }

    return strm <<
        "[MAP PRINT: " << m.name << "]" << endl <<
        endl << "[-------------------------Continents--------------------------]" <<
        endl << c.substr(0, c.length() - 3) << endl <<
        endl << "[-------------------------Territories--------------------------]" <<
        endl << t.substr(0, t.length() - 3) << endl <<
        endl << "[-------------------------Edges--------------------------]" <<
        endl << e.substr(0, e.length() - 3);
}

// Map assignment operator
Map& Map::operator = (const Map& toAssign){
    name = toAssign.name;
    continents = toAssign.continents;
    continentBonuses = toAssign.continentBonuses;
    territories = toAssign.territories;
    edges = toAssign.edges;
    return *this;
}

// Map accessors
string Map::getName() { return name; }
vector<string> Map::getContinents() { return continents; }
vector<int> Map::getContinentBonuses() { return continentBonuses; }
vector<Territory*> Map::getTerritories() { return territories; }
vector<Edge*> Map::getEdges() { return edges; }

// Map mutators
void Map::setName(string n) { name = n; }
void Map::setContinents(vector<string> c) {
    continents = vector<string>();

    for (string i : c) {
        continents.push_back(i);
    }
}
void Map::setContinentBonuses(vector<int> b) {
    continentBonuses = vector<int>();

    for (int i : b) {
        continentBonuses.push_back(i);
    }
}
void Map::setTerritories(vector<Territory*> t) {
    for (Territory *i : territories) {
        delete i;
        i = NULL;
    }

    territories = vector<Territory*>();

    for (Territory *j : t) {
        territories.push_back(j);
    }
}
void Map::setEdges(vector<Edge*> e) {
    for (Edge *i : edges) {
        delete i;
        i = NULL;
    }

    edges = vector<Edge*>();

    for (Edge *j : e) {
        edges.push_back(j);
    }
}

void Map::addContinent(string c) { continents.push_back(c); } // Method to add a string continent to a Map
void Map::addContinentBonus(int b) { continentBonuses.push_back(b); } // Method to add an int continent bonus to a Map
void Map::addTerritory(Territory *t) { territories.push_back(t); } // Method to add a Territory to a Map
void Map::addEdge(Edge *e) { edges.push_back(e); } // Method to add an Edge to a Map

// Method to recursively determine if two given Territories are connected between edges on a Map
bool Map::validateEdge(Map *m, Territory *start, Territory *end) {
    // Checking all the edges for matches
    for (Edge *i : m->getEdges()) {
        if (!i->visited) { // Making sure not to check previously used edges
            bool valid;

            // True if the desired destination edge has been reached
            if (i->a->getName() == end->getName() || i->b->getName() == end->getName()) {
                valid = true;
            }
            // Visiting the edge and checking the other Territory if not yet found
            else if (i->a->getName() == start->getName()) {
                i->visited = true;
                valid = validateEdge(m, i->b, end);
            }
            else if (i->b->getName() == start->getName()) {
                i->visited = true;
                valid = validateEdge(m, i->a, end);
            }
            // False if no other option
            else {
                valid = false;
            }

            // Immediately returning true if the destination has been found
            if (valid) {
                return true;
            }
        }
    }

    return false; // False if no matches
}

// Method to determine if a Map is valid
bool Map::validate() {
    // Checking paths from every Territory to every other
    for (int i = 0; i < territories.size(); i++) {
        for (int j = i+1; j < territories.size(); j++) {
            if (j < territories.size()) {
                // Making sure to set the edges to un-visited each new check
                for (int k = 0; k < edges.size(); k++) {
                    edges[k]->visited = false;
                }

                // Verifying that the map is a connected graph
                if (!validateEdge(this, territories[i], territories[j])) {
                    //cout << "Validation of " << name << " failed!" << endl;
                    return false;
                }

                // Verifying that continents are connected subgraphs
                if (territories[i]->getContinent() == territories[j]->getContinent() && !validateEdge(this, territories[i], territories[j])) {
                    //cout << "Validation of " << name << " failed!" << endl;
                    return false;
                }
            }
        }

        // Verifying that each country belongs to one and only one continent
        if (!doesContain(continents, territories[i]->getContinent())) {
            //cout << "Validation of " << name << " failed!" << endl;
            return false;
        }
    }

    //cout << "Validation of " << name << " succeeded!" << endl;
    return true;
}

vector<Territory*> Map::getConnectedTerritories(string n) {
    vector<Territory*> connected = vector<Territory*>();

    for (Edge *i : edges) {
        Territory *other = new Territory;
        other->setName("null");

        if (i->a->getName() == n) {
            other = i->b;
        }
        else if (i->b->getName() == n) {
            other = i->a;
        }

        if (other->getName() != "null") {
            connected.push_back(other);
        }
    }
    
    return connected;
}

vector<Territory*> Map::getContinentTerritories(string c) {
    vector<Territory*> terrs = vector<Territory*>();

    if (doesContain(continents, c)) {
        for (Territory *i : territories) {
            if (i->getContinent() == c) {
                terrs.push_back(i);
            }
        }
    }
    else {
        cout << "Continent does not exist in Map!" << endl;
    }

    return terrs;
}

// Method to check if two territories are adjacent
bool Map::adjacentTerritories(Territory* t1, Territory* t2) {
    vector<Territory*> ct = getConnectedTerritories(t1->getName());
    if(count(ct.begin(), ct.end(), t2)){
    return true;}

    else
    return false;
}

// Method to read the information at a given file, and output a fully-crafted Map object
Map *MapLoader::load(string f) {
    ifstream input(f);
    string line;
    Map *m = new Map;

    // Checking to see if the file can even be read from
    if (!getline(input, line)) {
        cout << "Unable to read file: " << f << endl;
    }
    else {
        // Catching any issues that might arise from a bad map file
        try {
            int section = 0;

            cout << "Loading name..." << endl;

            vector<string> nameSplit = stringSplit(line, ' ');

            // Making sure the first line (which contains the name) is valid
            if (nameSplit[0] != ";") {
                throw "INVALID MAP: no name!";
            }

            string mapName = nameSplit[2];

            m->setName(mapName.substr(0, mapName.length() - 4)); // Setting the new Map's name

            // Reading every subsequent line in the file
            while (getline(input, line)) {
                vector<string> lineSplit = stringSplit(line, ' '); // Splitting the line

                // Checking to see if a new section of the file has been reached
                if (line == "[continents]" || line == "[countries]" || line == "[borders]") {
                    section++;

                    if (line == "[continents]") {
                        cout << "Loading continents..." << endl;
                    }
                    else if (line == "[countries]") {
                        cout << "Loading territories..." << endl;

                        // Making sure no sections have been left out
                        if (section != 2) {
                            throw "INVALID MAP: no continents!";
                        }
                    }
                    else if (line == "[borders]") {
                        cout << "Loading edges..." << endl;

                        // Making sure no sections have been left out
                        if (section != 3) {
                            throw "INVALID MAP: no continents OR no territories!";
                        }
                    }
                }
                else {
                    // Skipping over blank lines
                    if (line != "") {
                        // Adding each continent
                        if (section == 1) {
                            if (lineSplit.size() == 3) {
                                m->addContinent(lineSplit[0]);
                                m->addContinentBonus(stoi(lineSplit[1]));
                            }
                            else {
                                throw "INVALID MAP: improper continent!";
                            }
                        }
                        // Adding each Territory
                        else if (section == 2) {
                            if (lineSplit.size() == 5) {
                                Territory *t = new Territory(lineSplit[1], m->getContinents()[stoi(lineSplit[2]) - 1], NULL, 0);
                                m->addTerritory(t);
                            }
                            else {
                                throw "INVALID MAP: improper territory!";
                            }
                        }
                        // Adding each Edge
                        else if (section == 3) {
                            if (lineSplit.size() > 1) {
                                Territory *t1 = m->getTerritories()[stoi(lineSplit[0]) - 1];

                                // Comparing each Territory with the others on the line, and adding the new Edge if it doesn't yet exist
                                for (int i = 1; i < lineSplit.size(); i++) {
                                    Territory *t2 = m->getTerritories()[stoi(lineSplit[i]) - 1];

                                    Edge *tempEdge = new Edge;
                                    tempEdge->a = t1;
                                    tempEdge->b = t2;
                                    m->addEdge(tempEdge);
                                }
                            }
                            else {
                                throw "INVALID MAP: improper edge!";
                            }
                        }
                    }
                }
            }

            //cout << m->getName() << " loaded!" << endl;
        }
        // Setting the Map to bad, and printing the error message
        catch (const char* message) {
            m->isGoodMap = false;
            cout << message << endl;
        }
    }

    return m;
}