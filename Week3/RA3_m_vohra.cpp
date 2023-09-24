#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>
using namespace std;

string word;

bool isSpecialName(string word) {
    if((word[0] == '_' || word[0] == '@') && isalpha(word[1]) == true) { 
        if(word.find("__") != std::string::npos) { //checks if __ is in the word
            return false;
        }
        else if(word.find('@', 1) != std::string::npos) {
            return false;
        }
        //else if(isalnum(static_cast<unsigned char>(word[word.length() -1])) != true) {
        else if(!isalnum(word.back())){
        return false;
        }
        return true;
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
                    if(isSpecialName(word) == true) {
                        numSpecialName++;
                    }
                } 
                else if(flag == "-sp") {
                    //count special names only
                    if(isSpecialName(word) == true) {
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

