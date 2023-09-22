#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

// argc represents the NUMBER of command line arguments (cl arg).
// arc defaults to 1 if no cl args are passed (only 1 argument in the argv array, the program name)

// argv[], each entry in the array is a pointer to a c-string for a cl arg
// argv[1] is the name of the program

int main(int argc, char *argv[]) {

    ifstream fin(argv[1]);
    string filename, line, word;
    int numWords;
    cout << "Enter a filename" << endl;
    cin >> filename;
    if (argc < 2) {
        cerr << "NO SPECIFIED INPUT FILE NAME" << endl; //1st is the program name, the 2nd is the inputFile
        exit(1);
    }
    if (string(argv[1]) != "-all" && string(argv[1]) != "-sp") { //why and if its just gonnna be one argument?
        cerr << "UNRECOGNIZED FLAG " << string(argv[1]) << endl;
        exit(1);
    }

    while (getline(fin, line)) {
        cout << line << endl;
        istringstream iss(line);
            while(iss >> word) {
                cout << word<< endl;
            }
        
    }
    fin.close();
    cout << numWords << endl;
    return 0;
}
