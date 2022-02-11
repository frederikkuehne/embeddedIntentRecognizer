#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

#include "intent.hpp"

void populateIntents(vector<Intent*>* intents);
void parseLine(string line, string* intentName, vector<string>* keywords, vector<string>* entities);
Intent* getIntent(vector<Intent*>* intents, string userInput);

int main()
{
    string userInput;
    vector<Intent*> intents;
    Intent* guessedIntent;

    populateIntents(&intents);

    cout << "What can I do for you?" << endl;
    getline(cin, userInput);

    guessedIntent = getIntent(&intents, userInput);

    cout << guessedIntent->getName();

    return 0;
}

/*-----------------------------------------------------------------------------------------------*
 * Scans the intents source file for intents and populates them into Intent objects
 *-----------------------------------------------------------------------------------------------*/
void populateIntents(vector<Intent*>* intents)
{
    /* Create input file stream and open intent source line by line -----------------------------*/
    string line;
    ifstream intentSrc("./../data/intents");
    string delimiterField = ";", delimiterSubField = ",";
    string intentName;
    vector<string> keywords, entities;

    /* Extract an intent and create an Intent object for every valid line -----------------------*/
    for (string line; getline(intentSrc, line);)
    {
        parseLine(line, &intentName, &keywords, &entities);
        intents->push_back(new Intent(intentName, keywords, entities));
    }
}

/*-----------------------------------------------------------------------------------------------*
 * Takes a line from the predefined intents file and extracts the parameters
 *-----------------------------------------------------------------------------------------------*/
void parseLine(string line, string* intentName, vector<string>* keywords, vector<string>* entities)
{
    *intentName = "Get weather";
    keywords->push_back("weather");
    keywords->push_back("rain");
    entities->push_back("location");
    entities->push_back("time");
}

/*-----------------------------------------------------------------------------------------------*
 * Feeds the user input to all Intents in order for them to find out if it matches
 *-----------------------------------------------------------------------------------------------*/
Intent* getIntent(vector<Intent*>* intents, string userInput)
{
    int iIntent = 0;

    /* Iterate over all intents to compare them with the user input -----------------------------*/
    for (;iIntent < intents->size(); iIntent++)
    {
        if (intents->at(iIntent)->checkMatch(userInput) != nullptr)
        {
            return intents->at(iIntent);
        }
    }

    /* No intent did match the user input -------------------------------------------------------*/
    return nullptr;
}