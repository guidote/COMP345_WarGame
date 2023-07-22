#pragma once
#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
using namespace std;

/****************************** Iloggable *******************************/
/// Class inherited with a single method to be overriden in respective subclasses
class Iloggable {
    public:
        ///Default Constructor
        Iloggable();

        ///Default Destructor
        ~Iloggable();

        /**
        Virtual function to be overriden in subclasses. Allows to create a string to output as a log entry.
        @param None
        @return string to output as a log entry
        */
        string virtual stringToLog()=0;
};

/****************************** Observer *******************************/
/// Abstract Class
class Observer {
    public:
        ///Default Constructor
        Observer();
        /// Destructor
        ~Observer();

        /**
        Virtual method that will be called upon by the Notify() from the Concrete Subject as implemented in the LogObserver
        @param pointer to an Illogable object
        @return void
        */
        virtual void update(Iloggable* il) = 0;
};

/****************************** LogObserver *******************************/
/// Concrete Class to log into an output file
class LogObserver : public Observer {

    public:
        /// Default Constructor
        LogObserver();
        /// Parameterized Constructor
        LogObserver(string fileName);
        /// Destructor
        ~LogObserver();

        /**
        Implentation of the virtual method form SuperClass Observer called upon by the Notify() from the Concrete Subject
        @param pointer to an Illogable object
        @return void
        */
        void update(Iloggable* il);

    public:
        /// Name of file to output game logs
        string fileName;
        /// output Stream for the game logs
        ofstream outputFile;
};

/****************************** Subject *******************************/
class Subject {
    public:
        /// Default Constructor
        Subject();
        /// Destructor
        ~Subject();

        /**
        Accessor for the LogObserver pointer member of the Subject Class
        @param None
        @return LogObserver pointer
        */
        LogObserver* getLogObserver();

        /**
        Mutator for the LogObserver pointer member of the Subject Class
        @param pointer to a LogObserver
        @return void
        */
        static void setLogObserver(LogObserver* logobs);

        /**
        Method to call the update() in the LogObserver and pass the Illogable* to it
        @param pointer to a LogObserver
        @return void
        */
        void notify(Iloggable* il);
    public:
        /// Static member of the class Subject to output to one single file for all subclasses of Subject
        static LogObserver* logObs;
};