#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <map>

using namespace std;

string cleanWord(string oldWord) {
    string cleanWord;
    for(int i = 0; i < oldWord.length(); i++) {
        char c = tolower(oldWord[i]);
        if(isalpha(c)) {
            cleanWord += c;
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
    string propositions[9] = {"about", "after", "below", "for", "from", "in", "into", "under", "with"};
    int arrLen = sizeof(propositions) / sizeof(propositions[0]);

	map<string, int> myMap;
    map<string, int>::iterator it;
    
    while (getline(inFile, line)) {
        lineCount++;
        istringstream iss(line);
        string word;
        while(iss >> word) {
            //clean words first
            string cleanWrd = cleanWord(word);
            //check if proposition is in array
            bool isPropos = false;
            for(int i = 0; i < arrLen; i++) {
                if(cleanWrd == propositions[i]) {
                    isPropos = true;
                    break; // if its in, break out and check if its in the map
                }
            }

            if(isPropos) {
                it = myMap.find(cleanWrd);
                if(it != myMap.end()) { // if its already in map, increment
                    it->second++;
                }
                else { //if not, initialize it in the map
                    myMap[cleanWrd] = 1;
                }
            }
        }
    }

    //check if file was empty and exit
    inFile.close();
    if(lineCount == 0) {
        cout << "File is empty." << endl;
        exit(1);
    }
    




    string maxKey = "";
    int maxCnt = -1;

    for(it = myMap.begin(); it != myMap.end(); it++) {
        if(it->second > maxCnt){
            maxCnt = it->second;
            maxKey = it->first;
        }
    }


    if(myMap.empty()) {
        cout << "No Preposition words from the given list are found in the file." << endl;
    }
    else {
        cout << "List of Prepositions seen in the file and their number of occurrences:" << endl;
        cout << endl;
        for(it = myMap.begin(); it != myMap.end(); it++) {
            cout << it->first << ": " << it->second << endl;
        }
        if(!maxKey.empty()) {
            cout << "The preposition with maximum occurrences is " << "\"" << maxKey << "\"" << ", which is found " << maxCnt << " times." << endl;
        }
    }

    // if(maxCnt == 0) {
    //     cout << "No Preposition words from the given list are found in the file." << endl;
    // } else {
    //     cout << "List of Prepositions seen in the file and their number of occurrences:" << endl;
    //     cout << endl;
    //     for(it = myMap.begin(); it != myMap.end(); it++) {
    //         cout << it->first << ": " << it->second << endl;
    //     }
    //     cout << "The preposition with maximum occurrences is " << "\"" << maxKey << "\"" << ", which is found " << maxCnt << " times." << endl;
    // }
}
