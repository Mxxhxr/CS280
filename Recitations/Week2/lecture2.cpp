#include <fstream>
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
    string filename, line;
    int totalLineCount = 0, commentedLineCount = 0, numWordsToBeFormatted = 0,
    boldCommandCount = 0, italicCommandCount = 0, regularCommandCount = 0;
    ifstream fin;


    cout << "Please enter a file name: " << endl;
    cin >> filename;

    fin.open(filename.c_str());
    if (!fin) {
        cerr << "File cannot be opened " << filename << endl; 
        exit(1);
    }

    while (fin.good()) {
        getline(fin, line);
        cout << line << endl;
        totalLineCount++;
    }



    fin.close();
    cout << "Total Lines: " << totalLineCount;
    //cout << "Commented Lines: " << commentedLineCount;
    //cout << "Number of words in the Text to be formatted: " << commentedLineCount;
    //cout << "Bold commands: " << commentedLineCount;
    //cout << "Italic commands: " << commentedLineCount;
    //cout << "Regular commands: " << commentedLineCount;

    return 0;
}