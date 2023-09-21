#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;


bool isWord(ifstream& fin, string line) {
    while(getline(fin, line)) {
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


int main(int argc, char *argv[]) {
    string filename, line;
    int numWords;
    ifstream fin;

    if(isWord(fin, line) == true) {
        numWords++;
    }
}

