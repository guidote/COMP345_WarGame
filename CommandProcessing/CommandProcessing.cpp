#include "../Cards/Cards.h"
#include "CommandProcessing.h"
#include "../GameEngine/GameEngine.h"
#include "../Map/Map.h"
#include "../Orders/Orders.h"
#include "../Player/Player.h"
#include "../PlayerStrategy/PlayerStrategies.h"

// Command default constructor
Command::Command() {
    command = "";
    validIn = vector<int>();
    transitionsTo = "";
    effect = "";

    //cout << "[Command default constructor]" << endl;
}

// Command parameterized constructor 1 (un-parameterized Commands)
Command::Command(string c) : command(c) {
    validIn = vector<int>();
    effect = "";

    isPossibleCommand = true;

    if (c == "validatemap") {
        addValidInState(2);
        transitionsTo = "mapvalidated";
    }
    else if (c == "gamestart") {
        addValidInState(4);
        transitionsTo = "assignreinforcement";
    }
    else if (c == "replay") {
        addValidInState(8);
        transitionsTo = "start";
    }
    else if (c == "quit") {
        addValidInState(8);
        transitionsTo = "exit program";
    }
    else {
        if (c != "loadmap" && c != "addplayer" && c != "tournament") {
            isPossibleCommand = false;
        }

        cout << "Invalid command!" << endl;
    }

    //cout << "[" + command + " Command parameterized constructor]" << endl;
}

// Command parameterized constructor 2 (parameterized Commands)
Command::Command(string c, string p) : command(c + " <" + p + ">") {
    validIn = vector<int>();
    effect = "";

    isPossibleCommand = true;

    if (c == "loadmap") {
        addValidInState(1);
        addValidInState(2);
        transitionsTo = "maploaded";
    }
    else if (c == "addplayer") {
        addValidInState(3);
        addValidInState(4);
        transitionsTo = "playersadded";
    }
    else {
        if (c != "validatemap" && c != "gamestart" && c != "replay" && c != "quit" && c != "tournament") {
            isPossibleCommand = false;
        }

        cout << "Invalid command!" << endl;
    }

    //cout << "[" + command + " Command parameterized constructor]" << endl;
}

// Command parameterized constructor 3 (tournament Command)
Command::Command(string c, string m, string p, int g, int d) : command(c + " -M <" + m + ">" + " -P <" + p + ">" + " -G <" + to_string(g) + ">" + " -D <" + to_string(d) + ">") {
    isPossibleCommand = true;

    if (c == "tournament") {
        transitionsTo = "none";
        effect = "";

        validIn = vector<int>();
        addValidInState(1);
    }
    else {
        if (c != "loadmap" && c != "validatemap" && c != "addplayer" && c != "gamestart" && c != "replay" && c != "quit" && c != "tournament") {
            isPossibleCommand = false;
        }

        cout << "Invalid command!" << endl;
    }

    //cout << "[" + command + " Command tournament constructor]" << endl;
}

// Command copy constructor
Command::Command(const Command &c) {
    command = c.command;
    transitionsTo = c.transitionsTo;
    effect = c.effect;

    validIn = vector<int>();

    for (int i : c.validIn) {
        validIn.push_back(i);
    }

    isPossibleCommand = c.isPossibleCommand;

    //cout << "[" + command + " Command copy constructor]" << endl;
}

// Command destructor
Command::~Command() {
    //cout << "[" + command + " Command destructor]" << endl;
}

// Command stream insertion operator
ostream& operator<<(ostream &strm, const Command &c) {
    string temp = "";

    for (int i : c.validIn) {
        temp += to_string(i) + " | ";
    }

    return strm <<
        "[COMMAND PRINT: " << c.command << "]" <<
        endl << "[--- Transitions to: " << c.transitionsTo << " ---]" <<
        endl << "[--- Effect: " << c.effect << " ---]" <<
        endl << "[--- Valid in: " << temp.substr(0, temp.length() - 3) << " ---]";
}

// Command assignment operator
Command& Command::operator = (const Command& toAssign) {
    command = toAssign.command;
    transitionsTo = toAssign.transitionsTo;
    effect = toAssign.effect;
    validIn = toAssign.validIn;
    isPossibleCommand = toAssign.isPossibleCommand;
    return *this;
}

// Accessors
string Command::getCommand() { return command; }
vector<int> Command::getValidIn() { return validIn; }
string Command::getTransitionsTo() { return transitionsTo; }
string Command::getEffect() { return effect; }

// Mutators
void Command::setCommand(string c) { command = c; }
void Command::setValidIn(vector<int> v) {
    validIn = vector<int>();

    for (int i : v) {
        validIn.push_back(i);
    }
}
void Command::setTransitionsTo(string t) { transitionsTo = t; }
void Command::saveEffect(string e) {
    effect = e;
    notify(this);
}

// Method to add a new state in which the Command is valid
void Command::addValidInState(int s) { validIn.push_back(s); }

string Command::stringToLog() {
    string logString = "Command entered: \"" + command + "\" changing the Game Engine State to " + transitionsTo + " and having the effect of \"" + effect +"\"\n";
    return logString;
}

//  CommandProcessor default constructor
CommandProcessor::CommandProcessor() {
    engine = NULL;
    commands = vector<Command*>();

    maps = vector<string>();
    playerStrategies = vector<string>();

    //cout << "[CommandProcessor default constructor]" << endl;
}

// CommandProcessor parameterized constructor
CommandProcessor::CommandProcessor(GameEngine *e) : engine(e) {
    commands = vector<Command*>();

    maps = vector<string>();
    playerStrategies = vector<string>();

    //cout << "[CommandProcessor parameterized constructor]" << endl;
}

// CommandProcessor copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor &cp) {
    engine = cp.engine;
    setCommands(cp.commands);

    setMaps(cp.maps);
    setPlayerStrategies(cp.playerStrategies);
    setNumberOfGames(cp.numberOfGames);
    setMaxTurns(cp.maxTurns);

    //cout << "[CommandProcessor copy constructor]" << endl;
}

// CommandProcessor destructor
CommandProcessor::~CommandProcessor() {
    for (Command *i : commands) {
        delete i;
        i = NULL;
    }

    //cout << "[CommandProcessor destructor]" << endl;
}

// CommandProcessor stream insertion operator
ostream& CommandProcessor::write(ostream &strm) const {
    string temp = "";

    for (Command *i : commands) {
        temp += i->getCommand() + " | ";
    }

    State s;

    if (engine != NULL) {
        s = *(engine->getState());
    }
    else {
        s = null;
    }

    return strm <<
        "[COMMANDPROCESSOR PRINT]" <<
        endl << "[--- Engine: " << s << " ---]" <<
        endl << "[--- Commands: " << temp.substr(0, temp.length() - 3) << " ---]";
}

// CommandProcessor assignment operator
CommandProcessor& CommandProcessor::operator = (const CommandProcessor& toAssign) {
    engine = toAssign.engine;
    commands = toAssign.commands;

    maps = toAssign.maps;
    playerStrategies = toAssign.playerStrategies;
    numberOfGames = toAssign.numberOfGames;
    maxTurns = toAssign.maxTurns;

    return *this;
}

// Accessors
GameEngine *CommandProcessor::getEngine() { return engine; }
vector<Command*> CommandProcessor::getCommands() { return commands; }
vector<string> CommandProcessor::getMaps() { return maps; }
vector<string> CommandProcessor::getPlayerStrategies() { return playerStrategies; }
int CommandProcessor::getNumberOfGames() { return numberOfGames; }
int CommandProcessor::getMaxTurns() { return maxTurns; }

// Mutators
void CommandProcessor::setEngine(GameEngine *e) { engine = e; }
void CommandProcessor::setCommands(vector<Command*> c) {
    for (Command *i : commands) {
        delete i;
        i = NULL;
    }

    commands = vector<Command*>();

    for (Command *j : c) {
        commands.push_back(j);
    }
}
void CommandProcessor::setMaps(vector<string> m) {
    maps = vector<string>();

    for (string j : m) {
        maps.push_back(j);
    }
}
void CommandProcessor::setPlayerStrategies(vector<string> ps) {
    playerStrategies = vector<string>();

    for (string j : ps) {
        playerStrategies.push_back(j);
    }
}
void CommandProcessor::setNumberOfGames(int n) { numberOfGames = n; }
void CommandProcessor::setMaxTurns(int m) { maxTurns = m; }

void CommandProcessor::addMap(string m) { maps.push_back(m); }
void CommandProcessor::addPlayerStrategy(string ps) { playerStrategies.push_back(ps); }

// Gets command from console
Command *CommandProcessor::readCommand() {
    string temp;
    fflush(stdin); // Making sure to flush the console
    getline(cin, temp);

    vector<string> words = vector<string>();
    string tempWord = "";

    // Splitting the input into words (if it can be split)
    for (char i : temp) {
        if (i == ' ') {
            words.push_back(tempWord);
            tempWord = "";
        }
        else {
            tempWord += i;
        }
    }

    words.push_back(tempWord);

    // Single word command
    if (words.size() == 1) {
        return new Command(words[0]);
    }
    // Double word command
    else if (words.size() == 2) {
        return new Command(words[0], words[1]);
    }
    // Tournament command
    else if (words.size() > 2) {
        string mapWords, playerStrategyWords;
        int tournamentParamNum = -1;

        for (int j = 1; j < words.size(); j++) {
            if (words[j] == "-M") {
                tournamentParamNum = 0;
            }
            else if (words[j] == "-P") {
                tournamentParamNum = 1;
            }
            else if (words[j] == "-G") {
                tournamentParamNum = -1;

                int tempNumberOfGames = stoi(words[j + 1]);

                if (tempNumberOfGames >= 1) {
                    if (tempNumberOfGames <= 5) {
                        numberOfGames = tempNumberOfGames;
                    }
                    else {
                        cout << "INVALID TOURNAMENT: too many games!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                }
                else {
                    cout << "INVALID TOURNAMENT: not enough games!" << endl;
                    return new Command("", "", "", 0, 0);
                }
            }
            else if (words[j] == "-D") {
                tournamentParamNum = -1;

                int tempMaxTurns = stoi(words[j + 1]);

                if (tempMaxTurns >= 10) {
                    if (tempMaxTurns <= 50) {
                        maxTurns = tempMaxTurns;
                    }
                    else {
                        cout << "INVALID TOURNAMENT: too many turns!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                }
                else {
                    cout << "INVALID TOURNAMENT: not enough turns!" << endl;
                    return new Command("", "", "", 0, 0);
                }
            }
            else {
                if (tournamentParamNum == 0) {
                    if (maps.size() < 5) {
                        maps.push_back(words[j]);
                        mapWords += words[j] + " ";
                    }
                    else {
                        cout << "INVALID TOURNAMENT: too many maps!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                }
                else if (tournamentParamNum == 1) {
                    if (maps.size() >= 1) {
                        if (playerStrategies.size() < 4) {
                            playerStrategies.push_back(words[j]);
                            playerStrategyWords += words[j] + " ";
                        }
                        else {
                            cout << "INVALID TOURNAMENT: too many players!" << endl;
                            return new Command("", "", "", 0, 0);
                        }
                    }
                    else {
                        cout << "INVALID TOURNAMENT: not enough maps!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                }
            }
        }

        if (playerStrategies.size() >= 2) {
            return new Command(words[0], mapWords, playerStrategyWords, numberOfGames, maxTurns);
        }
        else {
            cout << "INVALID TOURNAMENT: not enough players!" << endl;
            return new Command("", "", "", 0, 0);
        }
    }
    else {
        cout << "Invalid command!" << endl;
        return new Command("", "", "", 0, 0);
    }
}

// Stores the gotten Command in the array
void CommandProcessor::saveCommand(Command *c) {
    commands.push_back(c);
    notify(this); // FROM SUBJECT
}

// Reads and then saves a command from the console
void CommandProcessor::getCommand() {
    Command *temp = readCommand();

    if (temp != NULL) {
        saveCommand(temp);
    }
}

// Checks if the current Command is in the valid state
bool CommandProcessor::validate(Command *c) {
    bool isValid = false;

    for (int i : c->getValidIn()) {
        // Comparing each state in which the Command is valid to the current state
        if (i == *(engine->getState())) {
            isValid = true;
            break;
        }
    }

    if (isValid) {
        return true;
    }
    else {
        return false;
    }
}

string CommandProcessor::stringToLog() {
    string logString = "Saved the following command to the CommandProcessor: " + commands[commands.size() - 1]->getCommand() +"\n";
    return logString;
}

// Reads the given line from the given file and creates a Command out of it
Command *FileLineReader::readLineFromFile(CommandProcessor *cp, string f, int l) {
    ifstream input(f);
    string line;

    // Checking to see if the file can even be read from
    if (!getline(input, line)) {
        cout << "Unable to read file: " << f << endl;
    }
    else {
        // Looping through the file until the appropriate line is found
        for (int i = 0; i < l; i++) {
            getline(input, line);
        }
    }

    vector<string> words = vector<string>();
    string tempWord = "";

    // Splitting the input into words (if it can be split)
    for (char i : line) {
        if (i == ' ') {
            words.push_back(tempWord);
            tempWord = "";
        }
        else {
            tempWord += i;
        }
    }

    words.push_back(tempWord);

    // Single word command
    if (words.size() == 1) {
        return new Command(words[0]);
    }
    // Double word command
    else if (words.size() == 2) {
        return new Command(words[0], words[1]);
    }
    // Tournament command
    else if (words.size() > 2) {
        string mapWords, playerStrategyWords;
        int tournamentParamNum = -1;

        for (int j = 1; j < words.size(); j++) {
            if (words[j] == "-M") {
                tournamentParamNum = 0;
            } else if (words[j] == "-P") {
                tournamentParamNum = 1;
            } else if (words[j] == "-G") {
                tournamentParamNum = -1;

                int tempNumberOfGames = stoi(words[j + 1]);

                if (tempNumberOfGames >= 1) {
                    if (tempNumberOfGames <= 5) {
                        cp->setNumberOfGames(tempNumberOfGames);
                    } else {
                        cout << "INVALID TOURNAMENT: too many games!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                } else {
                    cout << "INVALID TOURNAMENT: not enough games!" << endl;
                    return new Command("", "", "", 0, 0);
                }
            } else if (words[j] == "-D") {
                tournamentParamNum = -1;

                int tempMaxTurns = stoi(words[j + 1]);

                if (tempMaxTurns >= 10) {
                    if (tempMaxTurns <= 50) {
                        cp->setMaxTurns(tempMaxTurns);
                    } else {
                        cout << "INVALID TOURNAMENT: too many turns!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                } else {
                    cout << "INVALID TOURNAMENT: not enough turns!" << endl;
                    return new Command("", "", "", 0, 0);
                }
            } else {
                if (tournamentParamNum == 0) {
                    if (cp->getMaps().size() < 5) {
                        cp->addMap(words[j]);
                        mapWords += words[j] + " ";
                    } else {
                        cout << "INVALID TOURNAMENT: too many maps!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                } else if (tournamentParamNum == 1) {
                    if (cp->getMaps().size() >= 1) {
                        if (cp->getPlayerStrategies().size() < 4) {
                            cp->addPlayerStrategy(words[j]);
                            playerStrategyWords += words[j] + " ";
                        } else {
                            cout << "INVALID TOURNAMENT: too many players!" << endl;
                            return new Command("", "", "", 0, 0);
                        }
                    } else {
                        cout << "INVALID TOURNAMENT: not enough maps!" << endl;
                        return new Command("", "", "", 0, 0);
                    }
                }
            }
        }

        if (cp->getPlayerStrategies().size() >= 2) {
            return new Command(words[0], mapWords, playerStrategyWords, cp->getNumberOfGames(), cp->getMaxTurns());
        } else {
            cout << "INVALID TOURNAMENT: not enough players!" << endl;
            return new Command("", "", "", 0, 0);
        }
    }
    else {
        cout << "Invalid command!" << endl;
        return new Command("", "", "", 0, 0);
    }
}

// FileCommandProcessorAdapter default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter() {
    currentFile = "";
    currentLine = 0;
    flr = new FileLineReader();

    //cout << "[FileCommandProcessorAdapter default constructor]" << endl;
}

// FileCommandProcessorAdapter parameterized constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(string f) :currentFile(f) {
    currentLine = 0;
    flr = new FileLineReader();

    //cout << "[FileCommandProcessorAdapter parameterized constructor]" << endl;
}

// FileCommandProcessorAdapter copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpa) {
    engine = fcpa.engine;
    setCommands(fcpa.commands);

    flr = fcpa.flr;
    currentFile = fcpa.currentFile;
    currentLine = fcpa.currentLine;

    //cout << "[FileCommandProcessorAdapter copy constructor]" << endl;
}

// FileCommandProcessorAdapter destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {
    delete flr;
    flr = NULL;

    //cout << "[FileCommandProcessorAdapter destructor]" << endl;
}

// FileCommandProcessorAdapter stream insertion operator
ostream& FileCommandProcessorAdapter::write(ostream &strm) const {
    string temp = "";

    for (Command *i : commands) {
        temp += i->getCommand() + " | ";
    }

    State s;

    if (engine != NULL) {
        s = *(engine->getState());
    }
    else {
        s = null;
    }

    return strm <<
        "[FILECOMMANDPROCESSORADAPTER PRINT]" <<
        endl << "[--- Engine: " << s << " ---]" <<
        endl << "[--- Commands: " << temp.substr(0, temp.length() - 3) << " ---]" <<
        endl << "[--- Current file: " << currentFile << " ---]" <<
        endl << "[--- Current line: " << currentLine << " ---]";
}

// FileCommandProcessorAdapter assignment operator
FileCommandProcessorAdapter& FileCommandProcessorAdapter::operator = (const FileCommandProcessorAdapter& toAssign) {
    engine = toAssign.engine;
    commands = toAssign.commands;
    currentFile = toAssign.currentFile;
    currentLine = toAssign.currentLine;
    return *this;
}

// Accessors
string FileCommandProcessorAdapter::getCurrentFile() { return currentFile; }
int FileCommandProcessorAdapter::getCurrentLine() { return currentLine; }

// Mutators
void FileCommandProcessorAdapter::setCurrentFile(string f) { currentFile = f; }
void FileCommandProcessorAdapter::setCurrentLine(int l) { currentLine = l; }

// Reads and then saves a command from a file
void FileCommandProcessorAdapter::getCommand() {
    Command *temp = flr->readLineFromFile(this, currentFile, currentLine);
    currentLine++;
    saveCommand(temp);
}

string FileCommandProcessorAdapter::stringToLog() {
    string logString = "Saved the following command to the CommandProcessor (from File): " + commands[commands.size() - 1]->getCommand() +"\n";
    return logString;
}