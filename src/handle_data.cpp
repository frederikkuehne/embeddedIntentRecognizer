#include <algorithm>
#include <fstream>

#include "handle_data.hpp"

/*-----------------------------------------------------------------------------------------------*
 * Scans the intents source file for intents and populates them into Intent objects
 *-----------------------------------------------------------------------------------------------*/
bool populateIntents(vector<Intent*>* intents, vector<string>* allEntities)
{
    /* Create input file stream and open intent source line by line -----------------------------*/
    ifstream intentSrc(INTENTS_SRC);
    string intentName, line;
    vector<string> keywords, entities;

    if (!intentSrc.is_open())
    {
        return false;
    }

    /* Extract an intent and create an Intent object for every valid line -----------------------*/
    while (getline(intentSrc, line))
    {
        parseIntentLine(line, &intentName, &keywords, &entities, allEntities);
        intents->push_back(new Intent(intentName, keywords, entities));
        keywords.clear();
        entities.clear();
    }

    return true;
}

/*-----------------------------------------------------------------------------------------------*
 * Scans Intents for all entity names and populates an entity list with keywords
 *-----------------------------------------------------------------------------------------------*/
int populateEntities(vector<string>* allEntities, map<string, vector<string>>* entityValues)
{
    string line;
    int iError = 0;

    /* Loop over all entities names to get their sets of keys from its file ---------------------*/
    for (int iEntity = 0; iEntity < allEntities->size(); iEntity++)
    {
        vector<string> entityValue;
        ifstream entitySrc(DATA_FOLDER + allEntities->at(iEntity));

        /* Check if the entities associated file could be opened --------------------------------*/
        if (!entitySrc.is_open())
        {
            iError++;
            continue;
        }

        /* Each line represents an entity key. It is pushed into the vector held by the map -----*/ 
        while (getline(entitySrc, line))
        {
            if(!line.empty())
            {
                entityValue.push_back(line);
            }
        }
        (*entityValues)[allEntities->at(iEntity)] = entityValue;
    }
}

/*-----------------------------------------------------------------------------------------------*
 * Takes a line from the strictly predefined intents file and extracts the parameters
 *-----------------------------------------------------------------------------------------------*/
bool parseIntentLine(
    string line,
    string* intentName, 
    vector<string>* keywords, 
    vector<string>* entities,
    vector<string>* allEntities)
{
    size_t pos_start = 0, pos_end = 0, pos_sub_start = 0, pos_sub_end = 0;
    string subLine, entity;

    /* Extract the intents name -----------------------------------------------------------------*/
    pos_end = line.find(MAIN_DELIMITER, pos_start);
    *intentName = line.substr(pos_start, pos_end);

    /* Extract the intents keywords -------------------------------------------------------------*/
    pos_start = pos_end + 1;
    pos_end = line.find(MAIN_DELIMITER, pos_start);
    subLine = line.substr(pos_start, pos_end - pos_start);

    /* Iterate over all the keywords and push them into the keyword list ------------------------*/
    while (pos_sub_end = subLine.find(SUB_DELIMITER, pos_sub_start))
    {
        string tmp = subLine.substr(pos_sub_start, pos_sub_end - pos_sub_start);
        if (!tmp.empty())
        {
            keywords->push_back(tmp);
        }
        pos_sub_start = pos_sub_end + 1;
        if (pos_sub_end == string::npos)
        {
            break;
        }
    }

    /* Extract the intents entities -------------------------------------------------------------*/
    pos_start = pos_end + 1;
    pos_end = line.find(MAIN_DELIMITER, pos_start);
    subLine = line.substr(pos_start, pos_end - pos_start);

    /* Iterate over all the entities and push them into the entity list -------------------------*/
    while (pos_sub_end = subLine.find(SUB_DELIMITER, pos_sub_start))
    {
        if(entity = subLine.substr(pos_sub_start, pos_sub_end - pos_sub_start), !entity.empty());
        {
            entities->push_back(entity);
        }
        pos_sub_start = pos_sub_end + 1;

        /* Check if this entity is already present in the list of all entities ------------------*/
        if (!entity.empty() && 
            find(allEntities->begin(), allEntities->end(), entity) == allEntities->end())
        {
            allEntities->push_back(entity);
        }

        if (pos_sub_end == string::npos)
        {
            break;
        }
    }
}

/*-----------------------------------------------------------------------------------------------*
 * Feeds the user input to all Intents in order for them to find out if it matches
 *-----------------------------------------------------------------------------------------------*/
Intent* getMatchingIntent(vector<Intent*>* intents, string userInput)
{
    /* Iterate over all intents to compare them with the user input -----------------------------*/
    for (int iIntent = 0;iIntent < intents->size(); iIntent++)
    {
        if (intents->at(iIntent)->matchKeywords(userInput))
        {
            return intents->at(iIntent);
        }
    }

    /* No intent did match the user input -------------------------------------------------------*/
    return nullptr;
}