#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "handle_data.hpp"
#include "intent.hpp"

using namespace std;


Intent* getMatchingIntent(vector<Intent*>* intents, string userInput);

/*-----------------------------------------------------------------------------------------------*
 * Program entry point. Uses the first argument as user input and prints results to console
 *-----------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    vector<Intent*> intents;
    Intent* guessedIntent;
    string guessedEntity;
    vector<string> allEntities;
    map<string, vector<string>> entityValues;

    /* This application expects exactly one input: The user input string ------------------------*/
    if (argc != 2)
    {
        cout << "Usage" << endl;
        cout << argv[0] << " <Input string to extract the intent from>" << endl;
        return 0;
    }
    
    /* Take first argument as user input and convert it to lower case ---------------------------*/
    string userInput = argv[1];
    transform(userInput.begin(), userInput.end(), userInput.begin(),
    [](unsigned char c){ return tolower(c); });

    /* Parses the list of intents to Intent objects from default path ---------------------------*/
    populateIntents(&intents, &allEntities);

    /* Gathers all possible entity types and loads the corresponding keywords -------------------*/
    populateEntities(&allEntities, &entityValues);

    /* Returns the Intent that fits the most to the user input and prints its name to console ---*/
    guessedIntent = getMatchingIntent(&intents, userInput);

    /* If no intent can be matche to the user input, exit defeated ------------------------------*/
    if (!guessedIntent)
    {
        cout << "Sorry, I did not understand you. Try rephrasing your inquiry." << endl;
        return 0;
    }

    /* If an Intent is matched, look for possible entities --------------------------------------*/
    guessedEntity = guessedIntent->matchEntity(userInput, &entityValues);

    /* Print result to console ------------------------------------------------------------------*/
    cout << "Intent: " << guessedIntent->getName() << guessedEntity << endl;

    return 0;
}


/*-----------------------------------------------------------------------------------------------*
 * Feeds the user input to all Intents in order for them to find out if it matches
 *-----------------------------------------------------------------------------------------------*/
Intent* getMatchingIntent(vector<Intent*>* intents, string userInput)
{
    int iIntent = 0;

    /* Iterate over all intents to compare them with the user input -----------------------------*/
    for (;iIntent < intents->size(); iIntent++)
    {
        if (intents->at(iIntent)->matchKeywords(userInput) != nullptr)
        {
            return intents->at(iIntent);
        }
    }

    /* No intent did match the user input -------------------------------------------------------*/
    return nullptr;
}