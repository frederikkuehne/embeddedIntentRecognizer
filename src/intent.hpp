#ifndef INTENT_H
#define INTENT_H

#include <map>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Intent {
    private:
        string name_;
        vector<string> keywords_;
        vector<string> entities_;
        bool matchesInput_ = false;

    public:
        Intent(string name, vector<string> keywords, vector<string> entities);

        string getName();
        bool matchKeywords(string userInput);
        string matchEntity(string userInput, map<string, vector<string>>* entityValues);
};

#endif