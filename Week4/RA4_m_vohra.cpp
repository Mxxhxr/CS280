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
    string propositions[9] = {"about", "after", "below", "for", "from", "in", "into", "under", "with"};

	map<string, int> myMap;

    
    while (getline(inFile, line)) {
        lineCount++;
        istringstream iss(line);
        string word;
        while(iss >> word) {
            //clean words first
            string cleanWrd = cleanWord(word);
            //if word is in array but not in map, add it
            if(find(begin(propositions)), end(propositions), cleanWord) {

            }
            // if word is in array and in map, increment in
            // if word is not in array, continue
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