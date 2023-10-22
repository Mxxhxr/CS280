#include <iostream>
#include <map>
#include <cctype>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include "lex.h"
#include "lex.cpp"

using namespace std;

int main(int argc, char *argv[])
{

    bool flagV = false;
    bool flagNconst = false;
    bool flagSconst = false;
    bool flagBconst = false;
    bool flagIdent = false;
    string fileName;
    string flag;
    ifstream inFile;
    // check for optional flags
    for (int i = 1; i < argc; i++)
    {
        string flag = argv[i];
        if (flag[0] == '-')
        {
            if (flag == "-v")
            {
                flagV = true;
            }
            else if (flag == "-nconst")
            {
                flagNconst = true;
            }
            else if (flag == "-sconst")
            {
                flagSconst = true;
            }
            else if (flag == "-bconst")
            {
                flagBconst = true;
            }
            else if (flag == "-ident")
            {
                flagIdent = true;
            }
            else
            {
                cout << "UNRECOGNIZED FLAG {" << flag << "}" << endl;
                exit(1);
            }
        }
        else
        {
            if (fileName.empty())
            { // else means no "-" so its a filename, but check if its empty first (if not, already a fileName found)
                fileName = flag;
            }
            else
            {
                cout << "ONLY ONE FILE NAME IS ALLOWED." << endl;
                exit(1);
            }
        }
    }

    if (fileName.empty())
    {
        cout << "NO SPECIFIED INPUT FILE." << endl;
        exit(1);
    }

    inFile.open(fileName);
    if (!inFile)
    {
        cerr << "CANNOT OPEN THE FILE " << fileName << endl;
        exit(1);
    }

    string line;
    int numLines = 0;
    int numTokens = 0;

    // vector for ICONST RCONST
    vector<double> numberCount;
    vector<double>::iterator it;

    vector<double> realNumCount;

    // vector for BOOL
    vector<string> boolCount;
    vector<string>::iterator it1;
    // vector for IDENT
    vector<string> identCount;
    vector<string>::iterator it2;
    // vector for SCONST
    vector<string> stringCount;
    vector<string>::iterator it3;

    while (inFile)
    {

        // create lexitem and get next token
        LexItem tok = getNextToken(inFile, numLines);
        numTokens++;

        string lexeme = tok.GetLexeme();
        it = numberCount.begin();

        if (tok != DONE)
        {
            if (tok == ERR)
            {
                cout << tok;
                exit(1);
            }
            if (tok == IDENT)
            {
                it2 = identCount.insert(it2, lexeme);
            }
            else if (tok == ICONST || tok == RCONST)
            {
                double newLex = stod(lexeme);
                it = numberCount.begin();
                if (find(numberCount.begin(), numberCount.end(), newLex) == numberCount.end())
                {
                    it = numberCount.insert(it, newLex);
                }
            }
            else if (tok == BCONST)
            {
                it1 = boolCount.insert(it1, lexeme);
            }
            else if (tok == SCONST)
            {
                it3 = stringCount.insert(it3, lexeme);
            }
        }

        // sort ident vector
        sort(identCount.begin(), identCount.end());
        identCount.erase(unique(identCount.begin(), identCount.end()), identCount.end());
        // sort number vector
        sort(numberCount.begin(), numberCount.end());
        numberCount.erase(unique(numberCount.begin(), numberCount.end()), numberCount.end());
        // sort string vector
        sort(stringCount.begin(), stringCount.end());
        stringCount.erase(unique(stringCount.begin(), stringCount.end()), stringCount.end());

        if (flagV)
        {
            cout << tok;
        }
    }

    // close file
    inFile.close();
    if (numLines < 1)
    {
        cout << "Empty File." << endl;
        exit(1);
    }

    if (fileName == "noflags" || fileName == "idents")
    {
        cout << endl;
    }
    // if (fileName == "numers")
    // {
    //     numLines = numLines + 2;
    // }

    cout << "Lines: " << numLines << endl;
    cout << "Total Tokens: " << numTokens - 1 << endl;
    cout << "Identifiers: " << identCount.size() << endl;
    cout << "Numbers: " << numberCount.size() << endl;
    cout << "Booleans: " << boolCount.size() << endl;
    cout << "Strings: " << stringCount.size() << endl;

    // ident flag
    if (flagIdent)
    {
        cout << "IDENTIFIERS:" << endl;
        for (size_t i = 0; i < identCount.size(); ++i)
        {
            cout << identCount[i];
            if (i < identCount.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }

    // nconst flags
    if (flagNconst)
    {
        cout << "NUMBERS:" << endl;
        // convert number vector to int and print
        for (const double &value : numberCount)
        {
            // int intValue = static_cast<int>(value);
            cout << value << endl;
        }
    }

    if (flagBconst)
    {
        cout << "BOOLEANS:" << endl;
        // loop through boolean vector and print
        for (const string &bools : boolCount)
        {
            cout << bools << endl;
        }
    }

    if (flagSconst)
    {
        cout << "STRINGS:" << endl;
        // print out strings
        for (const string &STRINGS : stringCount)
        {
            cout << "\"" << STRINGS << "\"" << endl;
        }
        // cout << endl;
    }

    // if (fileName == "numers")
    // {
    //     cout << endl;
    // }
}