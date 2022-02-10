#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <string>
#include "intent.hpp"

using namespace std;

SCENARIO("An intent can be created and the name can be read") 
{
    GIVEN("An arbitrary intent")
    {
        string name = "Get weather";
        Intent* intent = new Intent(name, "GET_WEATHER", "The user wants to know the current weather at his location");

        THEN("The name should be returned properly")
        {
            REQUIRE(intent->getName() == name);
        }
    }
}