#include "../Cards/Cards.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "Map.h"

int mapMain() {
    // Creating an array of file names and a MapLoader
    const int len = 5;
    string *files = new string[len]{ "canada.map", "europe.map", "LOTR2.map", "usa8regions.map", "solar.map"};
    MapLoader loader;

    // Looping through the files and creating a Map for each
    for (int i = 0; i < len; i++) {
        cout << endl;
        Map *temp = loader.load(files[i]);

        // Only printing and validating the Map if it's from a good file
        if (temp->isGoodMap) {
            cout << endl;
            cout << temp << endl;
            cout << endl;
            temp->validate();
        }

        cout << "\n==========" << endl;
    }

    // Freeing the string pointer array memory
    delete[] files;
    files = NULL;

    return 0;
}