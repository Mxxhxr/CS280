#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;


bool isWord(ifstream& inFile, string line) {
    while(getline(inFile, line)) {
        for(int i=0; i<line.length(); i++) {
            if(i > 0) {
                if(line[i] == ' ' && line[i-1] != ' ') {
                    return true;
                }
                else if(line[i] != ' ' && line[i+1] == '\n') {
                    return true;
                }
                else {
                    return false;
                }
                return false;
            }
        }
    }
    return false;
}

string word;

bool isSpecialName(ifstream& inFile, string line) { //wait, i need to do utilizing istringstream so i can read each word
    while(getline(inFile, line)) {
        istringstream iss(line);
        while(iss >> word) {
            for(int j=0; j<line.length(); j++) {
                //if it starts with one of the special characters and the next one is a letter. and the next one is also the other
                //special character, thats not allowed, so return false
                if((word[0] == '_' || word[0] == '@') && isalpha(word[1]) == true) { //dont need to check if @_ bcuz 2nd char has to be letter
                    if(word.find("__") != std::string::npos) { //checks if __ is in the word
                        return false;
                    }
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
    return false;
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
    else if(argc == 3){
        //there is a 3rd argument, check for valid flag
        flag = argv[2];
        if(flag != "-all" && flag != "-sp") {
            cout << "UNRECOGNIZED FLAG " << flag << endl;
            exit(1);
        }
    }

    string line; //took out ,word; and placed it at the top so its global. (whats the affect of it being used twice in different places?)
    int numWords, lineCount, numSpecialName;
    
    while (getline(inFile, line)) {
        lineCount++;
        istringstream iss(line);
            while(iss >> word) {
                if(flag == "-all") {
                    //count words ans special name
                    numWords++;
                    if(isSpecialName(inFile, line) == true) {
                        numSpecialName++;
                    }
                } 
                else if(flag == "-sp") {
                    //count special names only
                    if(isSpecialName(inFile, line) == true) {
                        numSpecialName++;
                    }
                }
                else {
                    // count just words (we can do this because we checked for valid flags before the while loop)
                    numWords++;
                }
            }   
    }
    //check if file was empty and exit
    inFile.close();
    if(lineCount == 0) {
        cout << "File is empty." << endl;
        exit(1);
    //print outputs    
    }
    if(flag == "-all") {
        cout << "Total number of words: " << numWords << endl;
        cout << "Total number of special names: " << numSpecialName << endl;
    }
    else if(flag == "-sp") {
        cout << "Total number of special names: " << numSpecialName << endl;
    }
    else {
    cout << "Total number of words: " << numWords << endl;
    }
    return 0;
}

