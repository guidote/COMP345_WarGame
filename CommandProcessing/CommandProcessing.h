#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

#include "../LoggingObserver/LoggingObserver.h"

/// Forward declaration of GameEngine and Map
class GameEngine;
class Map;

/**
 * Class representing one Command that gets executed in (primarily) the startup phase
 */
class Command :public Iloggable, public Subject {
    public:
        /// Default constructor
        Command();

        /**
        Parameterized constructor for validatemap, gamestart, replay, and quit commands
        @param string command name
        @return the Command created
        */
        Command(string);

        /**
        Parameterized constructor for loadmap and addplayer commands
        @param string command name, string command parameter
        @return the Command created
        */
        Command(string, string);

        /**
        Parameterized constructor for tournament commands
        @param string command name, string Map list, string PlayerStrategies list, int number of games, int max turns
        @return the Command created
        */
        Command(string, string, string, int, int);

        /**
        Copy constructor that creates a deep copy
        @param constant Commands reference
        @return the Commands created
        */
        Command(const Command &c);

        /// Destructor
        ~Command();

        /**
        Friend method to override the stream insertion operator
        @overload
        @param stream reference and the Command as a constant reference
        @return output stream reference
        */
        friend ostream& operator<<(ostream &strm, const Command &c);

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param Command reference that will be copied and assigned
        @return Command reference
        */
        Command& operator = (const Command& toAssign);

        /**
        Accessor for the name of the Command
        @param None
        @return string that is the name of the Command
        */
        string getCommand();

        /**
        Accessor for the name of the state the Command transitions to
        @param None
        @return string that is the name of the state the Command transitions to
        */
        string getTransitionsTo();

        /**
        Accessor for the effect of the Command
        @param None
        @return string that is the effect of the Command
        */
        string getEffect();

        /**
        Accessor for the states that the Command is valid in
        @param None
        @return vector of integers that is the states that the Command is valid in
        */
        vector<int> getValidIn();

        /**
        Mutator for the name of the Command
        @param string that is the name of the Command
        @return None
        */
        void setCommand(string);

        /**
        Mutator for the name of the state the Command transitions to
        @param string that is the name of the state the Command transitions to
        @return None
        */
        void setTransitionsTo(string);

        /**
        Mutator for the effect of the Command
        @param string that is the effect of the Command
        @return None
        */
        void saveEffect(string);

        /**
        Mutator for the states that the Command is valid in
        @param vector of integers that is the states that the Command is valid in
        @return None
        */
        void setValidIn(vector<int>);

        /**
        Method to add a new state in which the Command is valid
        @param int new state in which the Command is valid
        @return None
        */
        void addValidInState(int); // Method to add a new state in which the Command is valid

        string stringToLog() override; // From Iloggable

        /// Whether the Command name has been inputted correctly, but the parameters are missing
        bool isPossibleCommand;
    private:
        /// Name of the Command
        string command;
        /// The name of the state the Command transitions to
        string transitionsTo;
        /// Effect of the Command
        string effect;
        /// The states that the Command is valid in
        vector<int> validIn;
};

/**
 * Class to get and store Commands from the console for use in drivers and phases
 */
class CommandProcessor : public Iloggable, public Subject {
    public:
        /// Default constructor
        CommandProcessor();

        /**
        Parameterized constructor for engine
        @param pointer to GameEngine engine
        @return the CommandProcessor created
        */
        CommandProcessor(GameEngine*);

        /**
        Copy constructor that creates a deep copy
        @param constant CommandProcessor reference
        @return the CommandProcessor created
        */
        CommandProcessor(const CommandProcessor &cp);

        /// Destructor
        ~CommandProcessor();

        /**
        Virtual method to write the class
        @overload
        @param stream reference
        @return output stream reference
        */
        virtual ostream& write(ostream &strm) const;

        /**
        Friend method to override the stream insertion operator
        @overload
        @param stream reference and the CommandProcessor as a constant reference
        @return call to write method
        */
        friend ostream& operator<<(ostream &strm, CommandProcessor const &cp) { return cp.write(strm); }

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param CommandProcessor reference that will be copied and assigned
        @return CommandProcessor reference
        */
        CommandProcessor& operator = (const CommandProcessor& toAssign);

        /**
        Accessor for the engine of the CommandProcessor
        @param None
        @return pointer to GameEngine that is the engine of the CommandProcessor
        */
        GameEngine *getEngine();

        /**
        Accessor for the commands of the CommandProcessor
        @param None
        @return vector of pointers to Commands that are the commands of the CommandProcessor
        */
        vector<Command*> getCommands();

        /**
        Accessor for the tournament Maps of the CommandProcessor
        @param None
        @return vector of strings that are the tournament maps of the CommandProcessor
        */
        vector<string> getMaps();

        /**
        Accessor for the tournament PlayerStrategies of the CommandProcessor
        @param None
        @return vector of strings that are the tournament PlayerStrategies of the CommandProcessor
        */
        vector<string> getPlayerStrategies();

        /**
        Accessor for the number of tournament games of the CommandProcessor
        @param None
        @return int that is the number of tournament games of the CommandProcessor
        */
        int getNumberOfGames();

        /**
        Accessor for the max number of tournament turns of the CommandProcessor
        @param None
        @return int that is the max number of tournament turns of the CommandProcessor
        */
        int getMaxTurns();

        /**
        Mutator for the engine of the CommandProcessor
        @param pointer to GameEngine engine
        @return None
        */
        void setEngine(GameEngine*);

        /**
        Mutator for the commands of the CommandProcessor
        @param vector of Command pointers commands
        @return None
        */
        void setCommands(vector<Command*>);

        /**
        Mutator for the tournament Maps of the CommandProcessor
        @param vector of strings maps
        @return None
        */
        void setMaps(vector<string>);

        /**
        Mutator for the tournament PlayerStrategies of the CommandProcessor
        @param vector of strings player strategies
        @return None
        */
        void setPlayerStrategies(vector<string>);

        /**
        Mutator for the number of tournament games of the CommandProcessor
        @param int number of games
        @return None
        */
        void setNumberOfGames(int);

        /**
        Mutator for the max number of tournament turns of the CommandProcessor
        @param int max turns
        @return None
        */
        void setMaxTurns(int);

        /**
        Method to add a new tournament Map
        @param string map file name
        @return None
        */
        void addMap(string);

        /**
        Method to add a new tournament PlayerStrategy
        @param string player strategy name
        @return None
        */
        void addPlayerStrategy(string);

        /**
        Method that reads a command from the console
        @param None
        @return Command created from the console
        */
        Command *readCommand();

        /**
        Method that adds a command to the list of Commands
        @param pointer to Command
        @return None
        */
        void saveCommand(Command*);

        /**
        Virtual method that reads a command from the console, then saves it
        @param None
        @return None
        */
        virtual void getCommand();

        /**
        Method that checks to see if a Command is valid in the current GameEngine state
        @param pointer to Command
        @return None
        */
        bool validate(Command*); // Checks if the current Command is in the valid state

        string stringToLog() override; // From Iloggable
    protected:
        /// GameEngine on which the CommandProcessor is dependant for states
        GameEngine *engine;
        /// Collection of current and past Commands
        vector<Command*> commands;

        /// Collection of tournament Map file names
        vector<string> maps;
        /// Collection of tournament PlayerStrategies names
        vector<string> playerStrategies;
        /// Number  of tournament games
        int numberOfGames;
        /// Max number of tournament turns per game
        int maxTurns;
};

/**
 * Class used by FileCommandProcessorAdapter to read sequential lines from a file
 */
class FileLineReader {
    public:
        /**
        Method that reads the given line from the given file and creates a Command out of it
        @param pointer to CommandProcessor, string file name, int line number
        @return Command created from the file
        */
        Command *readLineFromFile(CommandProcessor*, string, int);
};

/**
 * Modified CommandProcessor that instead gets Commands from a file
 */
class FileCommandProcessorAdapter : public CommandProcessor {
    public:
        /// Default constructor
        FileCommandProcessorAdapter();

        /**
        Parameterized constructor for currentFile
        @param string file name
        @return the FileCommandProcessorAdapter created
        */
        FileCommandProcessorAdapter(string);

        /**
        Copy constructor that creates a deep copy
        @param constant FileCommandProcessorAdapter reference
        @return the FileCommandProcessorAdapter created
        */
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fcpa);

        /// Destructor
        ~FileCommandProcessorAdapter();

        /**
        Method to write the class
        @overload
        @param stream reference
        @return output stream reference
        */
        ostream& write(ostream &strm) const override;

        /**
        Assignment Operator overloading to assign a deep copy
        @overload
        @param FileCommandProcessorAdapter reference that will be copied and assigned
        @return FileCommandProcessorAdapter reference
        */
        FileCommandProcessorAdapter& operator = (const FileCommandProcessorAdapter& toAssign);

        /**
        Accessor for the currentFile
        @param None
        @return string the current file's name
        */
        string getCurrentFile();

        /**
        Accessor for the currentLine
        @param None
        @return int the current line of the current file
        */
        int getCurrentLine();

        /**
        Mutator for the current file
        @param string that is the name of the new current file
        @return None
        */
        void setCurrentFile(string);

        /**
        Mutator for the current line
        @param int that is the new current line of the current file
        @return None
        */
        void setCurrentLine(int);

        string stringToLog() override; // From Iloggable

        /**
        Overridden method that reads the next line from the current file, then saves it
        @param None
        @return None
        */
        void getCommand() override; // Reads and then saves a command from a file
    private:
        /// FileLineReader used to each line sequentially
        FileLineReader *flr;
        /// The current file of commands that is being read from
        string currentFile;
        /// The current line being read in the current file
        int currentLine;
};