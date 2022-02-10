#include <string>
using namespace std;

class Intent {
    private:
        string name_;
        string keyword_;
        string description_;

    public:
        Intent(string name, string keyword, string description);

        string getName();
};