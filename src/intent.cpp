#include "intent.hpp"

/*-----------------------------------------------------------------------------------------------*
 * Constructs an Intent object that holds its parameters and can compare it to user input
 *-----------------------------------------------------------------------------------------------*/
Intent::Intent(string name, vector<string> keywords, vector<string> entities)
{
  if (name.empty())
  {
    throw invalid_argument("The intents name cannot be empty.");
  }
  if (keywords.empty())
  {
    throw invalid_argument("The keywords list cannot be empty.");
  }
  
  this->name_ = name;
  this->keywords_ = keywords;
  this->entities_ = entities;
}

/*-----------------------------------------------------------------------------------------------*
 * Returns the name of the intent
 *-----------------------------------------------------------------------------------------------*/
string Intent::getName()
{
  return this->name_;
}

/*-----------------------------------------------------------------------------------------------*
 * Takes the user input and checks if it contains a string that matches the intents keyword list
 *-----------------------------------------------------------------------------------------------*/
bool Intent::matchKeywords(string userInput)
{
  /* Iterate over the intents keywords and match it with the user input -------------------------*/
  for (string keyword : this->keywords_)
  {
    /* If the keyword is found in the users input, return the intent object ---------------------*/#
    return (userInput.find(keyword) != string::npos);
  }

  /* If the keyword does not match, return nullptr ----------------------------------------------*/
  return false;
}

/*-----------------------------------------------------------------------------------------------*
 * Looks for matching entities in the user input string if at least one keyword matches
 *-----------------------------------------------------------------------------------------------*/
string Intent::matchEntity(string userInput, map<string, vector<string>>* entityValues)
{
  string entitiesFound = " ";
  int iFound = 0;

  /* Iterate over the intents entities and the entities keywords --------------------------------*/
  for (string entity : this->entities_)
  {
    for (string entityKey : (*entityValues)[entity])
    {
      /* If the entities keywords are present in the user input string, return its category -----*/
      if (userInput.find(entityKey) != string::npos)
      {
        entitiesFound.append(entity).append(", ");
        iFound++;
        break;
      }
    }
  }

  /* Return an empty string if nothing has been found -------------------------------------------*/
  if (!iFound)
  {
    return "";
  }

  /* Remove the trailing comma and space and return result --------------------------------------*/
  return entitiesFound.substr(0, entitiesFound.length() - 2);
}