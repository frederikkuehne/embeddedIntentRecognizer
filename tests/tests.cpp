#include "catch.hpp"

#include "intent.hpp"
#include "handle_data.hpp"

using namespace std;

TEST_CASE("Test intent functionality", "[intent]")
{
    string name = "Get weather";
    vector<string> keywords = {"weather", "rain"};
    vector<string> entities = {"location", "time"};
    Intent* intent = new Intent(name, keywords, entities);
    map<string, vector<string>> entityValues;
    populateEntities(&entities, &entityValues);

    REQUIRE(intent->getName() == name);
    REQUIRE(intent->matchKeywords("How is the weather?"));
    REQUIRE(intent->matchEntity("How is the weather today?", &entityValues) == " time");
}

TEST_CASE("Test example user input 1", "[user-input-1]")
{
    vector<Intent*> intents;
    Intent* guessedIntent;
    string guessedEntity;
    vector<string> allEntities;
    map<string, vector<string>> entityValues;
    
    populateIntents(&intents, &allEntities);
    populateEntities(&allEntities, &entityValues);
    guessedIntent = getMatchingIntent(&intents, "what is the weather like today?");
    guessedEntity = guessedIntent->matchEntity("what is the weather like today?", &entityValues);

    REQUIRE(guessedIntent->getName() == "Get weather");
    REQUIRE(guessedEntity == " time");
}

TEST_CASE("Test example user input 2", "[user-input-2]")
{
    vector<Intent*> intents;
    Intent* guessedIntent;
    string guessedEntity;
    vector<string> allEntities;
    map<string, vector<string>> entityValues;
    
    populateIntents(&intents, &allEntities);
    populateEntities(&allEntities, &entityValues);
    guessedIntent = getMatchingIntent(&intents, "what is the weather like in paris today?");
    guessedEntity = guessedIntent->matchEntity("what is the weather like in paris today?", &entityValues);

    REQUIRE(guessedIntent->getName() == "Get weather");
    REQUIRE(guessedEntity == " time, location");
}

TEST_CASE("Test example user input 3", "[user-input-3]")
{
    vector<Intent*> intents;
    Intent* guessedIntent;
    string guessedEntity;
    vector<string> allEntities;
    map<string, vector<string>> entityValues;
    
    populateIntents(&intents, &allEntities);
    populateEntities(&allEntities, &entityValues);
    guessedIntent = getMatchingIntent(&intents, "tell me an interesting fact.");
    guessedEntity = guessedIntent->matchEntity("tell me an interesting fact.", &entityValues);

    REQUIRE(guessedIntent->getName() == "Get fact");
    REQUIRE(guessedEntity == "");
}