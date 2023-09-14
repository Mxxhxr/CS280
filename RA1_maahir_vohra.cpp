#include <iostream>
using namespace std;

int main(int argc, char *arhv[]) {
    string fname, lname;
    int section;
    
    cout << "Please enter your first name >>" << endl;
    cin >> fname;
    cout << "Please enter your last name >>" << endl;
    cin >> lname;
    cout << "Please enter your CS 280 section number >>" << endl;
    cin >> section;
    cout << "Hello " << fname << ", welcome to CS 280 section " << section << endl;
    return 0;
};