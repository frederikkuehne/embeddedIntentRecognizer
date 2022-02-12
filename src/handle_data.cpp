#include <algorithm>
#include <fstream>

#include "handle_data.hpp"

/*-----------------------------------------------------------------------------------------------*
 * Scans the intents source file for intents and populates them into Intent objects
 *-----------------------------------------------------------------------------------------------*/
void populateIntents(vector<Intent*>* intents, vector<string>* allEntities)
{
    /* Create input file stream and open intent source line by line -----------------------------*/
    ifstream intentSrc("./../data/intents");
    string intentName, line;
    vector<string> keywords, entities;

    /* Extract an intent and create an Intent object for every valid line -----------------------*/
    while (getline(intentSrc, line))
    {
        parseIntentLine(line, &intentName, &keywords, &entities, allEntities);
        intents->push_back(new Intent(intentName, keywords, entities));
        keywords.clear();
        entities.clear();
    }
}

/*-----------------------------------------------------------------------------------------------*
 * Scans Intents for all entity names and populates an entity list with keywords
 *-----------------------------------------------------------------------------------------------*/
void populateEntities(vector<string>* allEntities, map<string, vector<string>>* entityValues)
{
    int iEntity;
    string line;
    map<string, vector<string>> entityValuess;

    for (iEntity = 0; iEntity < allEntities->size(); iEntity++)
    {
        vector<string> entityValue;
        ifstream entitySrc("./../data/" + allEntities->at(iEntity));
        while (getline(entitySrc, line))
        {
            entityValue.push_back(line);
        }
        (*entityValues)[allEntities->at(iEntity)] = entityValue;
    }
}

/*-----------------------------------------------------------------------------------------------*
 * Takes a line from the predefined intents file and extracts the parameters
 *-----------------------------------------------------------------------------------------------*/
void parseIntentLine(
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
        keywords->push_back(subLine.substr(pos_sub_start, pos_sub_end - pos_sub_start));
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
        entity = subLine.substr(pos_sub_start, pos_sub_end - pos_sub_start);
        entities->push_back(entity);
        pos_sub_start = pos_sub_end + 1;

        /* Check if this entity is already present in the list of all entities ------------------*/
        if (find(allEntities->begin(), allEntities->end(), entity) == allEntities->end())
        {
            allEntities->push_back(entity);
        }

        if (pos_sub_end == string::npos)
        {
            break;
        }
    }
}