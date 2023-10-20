#include <iostream>
#include <map>
#include<cctype>
#include <fstream>
#include <sstream>
#include "lex.h"



using namespace std;

int main(int argc, char *argv[]) {

    bool flagV = false;
    bool flagNconst = false;
    bool flagSconst = false;
    bool flagBconst = false;
    bool flagIdent = false;
    string fileName;
    string flag;
    ifstream inFile;
    //check for optional flags
    for(int i = 1; i < argc; i++) {
        string flag = argv[i];
        if(flag[0] == '-') {
            if(flag == "-v") {
                flagV = true;
            }
            else if(flag == "-nconst") {
                flagNconst = true;
            }
            else if(flag == "-sconst") {
                flagSconst = true;
            }
            else if(flag == "-bonst") {
                flagBconst = true;
            }
            else if(flag == "-ident") {
                flagIdent = true;
            }
            else {
                cout << "UNRECOGNIZED FLAG {" << flag << "}" << endl;
                exit(1);
            }
        }
        else {
            if(fileName.empty()) { //else means no "-" so its a filename, but check if its empty first (if not, already a fileName found)
                fileName = flag;
            }
            else {
                cout << "ONLY ONE FILE NAME IS ALLOWED." << endl;
                exit(1);
            }
        }
    }

    if(fileName.empty()) {
        cout << "NO SPECIFIED INPUT FILE." << endl;
        exit(1);
    }
    
    
    inFile.open(fileName);
    if (!inFile) {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        exit(1);
    }

    string line;
    int numLines = 0;
    int numTokens = 0;
    int numIdentifiers = 0;
    int numNumbers = 0;
    int numBooleans = 0;
    int numStrings = 0;
    string identifiers[20]; 

    while(inFile) {
        LexItem tok = getNextToken(inFile, numLines);
        cout << tok << endl;
        numLines++; //prolly not gonna work
    }

    inFile.close();
    if(numLines == 1) {
        cout << "Empty File." << endl;
        exit(1);

    }
    cout << flagV << endl;
    cout << flagBconst << endl;
    cout << flagIdent << endl;
    cout << flagNconst << endl;
    cout << flagSconst << endl;
    
    cout << "Lines: " << numLines << endl;
    cout << "Total Tokens: " << numTokens << endl;
    cout << "Identifiers: " << numIdentifiers << endl;
    cout << "Numbers: " << numNumbers << endl;
    cout << "Booleans: " << numBooleans << endl;
    cout << "Strings: " << numStrings << endl;
}