#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

string cleanWord(string oldWord) {
    string cleanWord = oldWord;
    for(int i = 0; i < oldWord.length(); i++) {
        cleanWord[i] = tolower(cleanWord[i]);
        if(ispunct(cleanWord[i])) {
            cleanWord.erase(cleanWord[i]);
        } 
    }
    return cleanWord;
}



int main(int argc, char *argv[]) { 
    
    if(argc == 1 || string(argv[1]).substr(0,1) == "-") {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }

    string filename = argv[1];
    string flag;
    ifstream inFile;

    inFile.open(filename.c_str());
    if (!inFile) {
        cerr << "CANNOT OPEN THE FILE " << filename << endl; 
        exit(1);
    }

    string line;
    int lineCount = 0;
    map<string, int> preps;
    preps["about"] = 0;
    preps["after"] = 0;
    preps["below"] = 0;
    preps["for"] = 0;
    preps["from"] = 0;
    preps["in"] = 0;
    preps["into"] = 0;
    preps["under"] = 0;
    preps["with"] = 0;

    
    while (getline(inFile, line)) {
        lineCount++;
        istringstream iss(line);
        string word;
        while(iss >> word) {
            if preps
        }
    }

    //check if file was empty and exit
    inFile.close();
    if(lineCount == 0) {
        cout << "File is empty." << endl;
        exit(1);
    }

    cout << "List of Prepositions seen in the file and their number of occurrences:" << endl;
}