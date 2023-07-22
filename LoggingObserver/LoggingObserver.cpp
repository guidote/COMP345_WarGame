#include "LoggingObserver.h"

/****************************** Iloggable *******************************/

Iloggable::Iloggable() {};

Iloggable::~Iloggable() {};

string Iloggable::stringToLog(){
    return "";
}

/****************************** Observer *******************************/

Observer::Observer() { };

Observer::~Observer() { };

/****************************** LogObserver *******************************/

LogObserver::LogObserver() {
    fileName = "";
    outputFile.open(fileName);
}

LogObserver::LogObserver(string name) {
    fileName = name;
    outputFile.open(fileName);
}

LogObserver::~LogObserver() {
    outputFile.close();
}

void LogObserver::update(Iloggable* il) {
    outputFile << (*il).stringToLog() << "\n";
}

/****************************** Subject *******************************/

Subject::Subject() { }

Subject::~Subject() { };

LogObserver* Subject::getLogObserver(){ return logObs; }

void Subject::setLogObserver(LogObserver* lo){ logObs = lo; }

void Subject::notify(Iloggable* il){ logObs->update(il); }

//LogObserver* Subject::logObs = new LogObserver();