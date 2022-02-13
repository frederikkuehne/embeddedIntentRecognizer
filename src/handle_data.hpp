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

bool populateIntents(vector<Intent*>* intents, vector<string>* allEntities);
int populateEntities(vector<string>* allEntities, map<string, vector<string>>* entityValues);
bool parseIntentLine(string line, string* intentName, vector<string>* keywords, vector<string>* entities, vector<string>* allEntities);

#endif