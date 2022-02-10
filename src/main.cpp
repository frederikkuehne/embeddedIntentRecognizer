#include <iostream>
using namespace std;

#include "intent.hpp"

int main()
{
    string name;

    getline(cin, name);

    Intent* intent = new Intent(name, "", "");

    cout << "Name: " << intent->getName() << endl;
    return 0;
}