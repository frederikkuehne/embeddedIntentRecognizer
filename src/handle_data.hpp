#ifndef HANDLE_DATA_H
#define HANDLE_DATA_H

#include <map>
#include <string>
#include <vector>
#include "intent.hpp"

#define DATA_FOLDER "./../data/"
#define INTENTS_SRC DATA_FOLDER "intents"
#define MAIN_DELIMITER ";"
#define SUB_DELIMITER ","

void populateIntents(vector<Intent*>* intents, vector<string>* allEntities);
void populateEntities(vector<string>* allEntities, map<string, vector<string>>* entityValues);
void parseIntentLine(string line, string* intentName, vector<string>* keywords, vector<string>* entities, vector<string>* allEntities);

#endif