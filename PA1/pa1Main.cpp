#include <iostream>
#include <map>
#include<cctype>
#include <fstream>
#include <sstream>
#include "lex.h"
#include "lex.cpp"



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
            else if(flag == "-bconst") {
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
        if(flagV && flagNconst && flagSconst && flagBconst && flagIdent) {
            //all flags
            LexItem tok = getNextToken(inFile, numLines);
            numTokens++; 
            cout << tok << endl;

            //count all the tokens,idents,nums,bools,and string (gotta delete duplicates)
            if(tok.GetToken() == IDENT) {
                numIdentifiers++;
            }
            if(tok.GetToken() == ICONST || tok.GetToken() == RCONST) {
                numNumbers++;
            }
            if(tok.GetToken() == SCONST) {
                numStrings++;
            }
            if(tok.GetToken() == BCONST && (tok.GetLexeme() == "true" || tok.GetLexeme() == "false")) {
                numBooleans++;
            }

        }
        else if(BCONST) {
            LexItem tok = getNextToken(inFile, numLines);
            if(tok.GetToken() = BCONST {
                cout << tok << endl;
            })

        }










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
    cout << "Total Tokens: " << numTokens - 1 << endl;
    cout << "Identifiers: " << numIdentifiers << endl;
    cout << "Numbers: " << numNumbers << endl;
    cout << "Booleans: " << numBooleans << endl;
    cout << "Strings: " << numStrings << endl;
}