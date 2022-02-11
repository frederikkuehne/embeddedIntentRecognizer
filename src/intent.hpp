#include <string>
#include <vector>
using namespace std;

class Intent {
    private:
        string name_;
        vector<string> keywords_;
        vector<string> entities_;

    public:
        Intent(string name, vector<string> keywords, vector<string> entities);

        string getName();
        Intent* checkMatch(string userInput);
};