#include "intent.hpp"

Intent::Intent(string name, string keyword, string description)
{
  this->name_ = name;
  this->keyword_ = keyword;
  this->description_ = description;
}

string Intent::getName()
{
  return this->name_;
}