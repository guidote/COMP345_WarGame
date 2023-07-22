#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"

int commandProcessingMain() {
    // Creating the CommandProcessor and (possibly unused) FileCommandProcessorAdapter
    CommandProcessor *cp;
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
        cp = temp;

        cout << "Please give a command: " << endl;
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
        cp = fcpa;
    }

    // Creating the GameEngine and connecting it to and from the CommandProcessor
    GameEngine *e = new GameEngine;
    cp->setEngine(e);
    e->setProcessor(cp);
    e->setState(start);

    cp->getCommand(); // Getting a single Command

    Command *c = cp->getCommands()[cp->getCommands().size() - 1];

    c->saveEffect("Driver Effect");

    // Printing the CommandProcessor and the single Command
    cout << endl << *cp << endl << endl;
    cout << *c << endl << endl;

    cout << "Is valid command: " << cp->validate(c) << endl; // Validating the Command

    delete e;
    e = NULL;

    return 0;
}