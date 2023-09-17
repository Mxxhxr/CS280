#include <fstream>
#include <iostream>

using namespace std;

int main() {
    string filename;
    int totalLineCount = 0, commentedLineCount = 0, numWords = 0,
    boldCommandCount = 0, italicCommandCount = 0, regularCommandCount = 0;
    ifstream inFile;

    cout << "Enter the name of a file to read from:" << endl;
    cin >> filename;
    cout << endl;

    inFile.open(filename.c_str());

    if (!inFile) {
        cerr << "File cannot be opened " << filename << endl;
        exit(1);
    }

    string currentLine;
    while(getline(inFile, currentLine)) {
        cout << currentLine << endl;
    }
    
    inFile.close();
    // cout << "Total Lines: " << totalLineCount << endl;
    // cout << "Commented Lines: " << commentedLineCount << endl;
    // cout << "Number of words in the Text to be formatted: " << numWords << endl;
    // cout << "Bold commands: " << boldCommandCount << endl;
    // cout << "Italic commands: " << italicCommandCount << endl;
    // cout << "Regular commands: " << regularCommandCount << endl;
    return 0;
}