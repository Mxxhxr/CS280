#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string filename;
    string line;
    int count = 0;
    ifstream fin;

    cout << "Please enter a file name > ";
    cin >> filename;

    fin.open(filename.c_str()); // The c_str method generates a C-style character string
    if (!fin) { // Overloaded ! operator
        cerr << "File cannot be opened " << filename << endl; 
        exit(1);
    }

    while (fin.good()) {
        getline(fin, line);
        cout << line << endl;
        count++;
    }
    fin.close();
    cout << "Line Count: " << count;
    return 0;
}