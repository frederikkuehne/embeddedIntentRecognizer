#include "intent.hpp"


/*-----------------------------------------------------------------------------------------------*
 * Constructs an Intent object that holds its parameters and can compare it to user input
 *-----------------------------------------------------------------------------------------------*/
Intent::Intent(string name, vector<string> keywords, vector<string> entities)
{
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
Intent* Intent::checkMatch(string userInput)
{
  /* Iterate over the intents keywords and match it with the user input -------------------------*/
  for (string keyword : this->keywords_)
  {
    /* If the keyword is found in the users input, return the intent object ---------------------*/
    if (userInput.find(keyword) != string::npos)
    {
      return this;
    }
  }

  /* If the keyword does not match, return nullptr ----------------------------------------------*/
  return nullptr;
}