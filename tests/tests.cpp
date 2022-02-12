#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include "intent.hpp"

using namespace std;

SCENARIO("An intent can be created and the name can be read and the user input can be identified") 
{
    GIVEN("An arbitrary intent")
    {
        string name = "Get weather";
        vector<string> keywords = {"weather", "rain"};
        vector<string> entities = {"city", "time"};
        Intent* intent = new Intent(name, keywords, entities);

        THEN("The name should be returned properly")
        {
            REQUIRE(intent->getName() == name);
            REQUIRE(intent->matchKeywords("How is the weather?") == intent);
        }
    }
}