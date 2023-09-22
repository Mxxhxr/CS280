#include <iostream>
#include <fstream>
#include <sstream>
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
}

//argc = 3
//argv[0] = ./a.out
//argv[1] = input file
//argv[2] = flag
int main(int argc, char *argv[]) { 
    
    string filename = argv[1];
    if(argc == 0) {
        cerr << "nah bruh" << endl;
    }


    if(filename.substr(0,1) == "-") {
        cerr << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(1);
    }

    if(string(argv[2]) != "-all" && string(argv[2]) != "-sp") {
        cerr << "UNRECOGNIZED FLAG " << string(argv[2]) << endl;
        exit(1);
    }

    string flag, line, word;
    int numWords;
    int idk;
    ifstream inFile;
    flag = argv[2];

    inFile.open(filename.c_str());
    if (!inFile) {
        cerr << "CANNOT OPEN THE FILE " << filename << endl; 
        exit(1);
    }

    while (getline(inFile, line)) {
        cout << line << endl;
        istringstream iss(line);
            while(iss >> word) {
                if(isWord(inFile, line) == true) {
                numWords++; //also count how many special words
                }
            }
    }
    cout << "Total number of words: " << numWords << endl;
    return 0;
}

