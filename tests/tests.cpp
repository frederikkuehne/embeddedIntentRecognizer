/* Creates a catch2 main function as entry point ------------------------------------------------*/
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "intent.hpp"
#include "handle_data.hpp"

using namespace std;

/* Tests of the function getMatchingIntent() ----------------------------------------------------*/
TEST_CASE("The function getMatchingIntent() returns the expected values", "[main]")
{
    string userInput = "";
    vector<Intent*>* intents;

    REQUIRE(getMatchingIntent(intents, userInput) == nullptr);

    intents->push_back(new Intent("", {""}, {""}));
    intents->push_back(new Intent("Get weather", {"weather"}, {"location"}));
    intents->push_back(new Intent("Get fact", {"fact"}, {""}));
    
    REQUIRE(getMatchingIntent(intents, userInput) == nullptr);

    userInput = "Tell me the weather";
    REQUIRE(getMatchingIntent(intents, userInput) == intents->at(0));

    userInput = "Tell me a fact";
    REQUIRE(getMatchingIntent(intents, userInput) == intents->at(1));
}


/* Test of the function populateIntents() -------------------------------------------------------*/
TEST_CASE("The intents can be populated properly", "[handle_data]")
{
    vector<Intent*>* intents;
}


TEST_CASE("An intent can be created and the name can be read and the user input can be identified")
{
    string name = "Get weather";
    vector<string> keywords = {"weather", "rain"};
    vector<string> entities = {"location", "time"};
    Intent* intent = new Intent(name, keywords, entities);

    REQUIRE(intent->getName() == name);
    REQUIRE(intent->matchKeywords("How is the weather?"));

}