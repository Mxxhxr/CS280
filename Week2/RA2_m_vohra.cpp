#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
    string filename, line;
    int totalLineCount = 0, commentedLineCount = 0, numWords = 0,
    boldCommandCount = 0, italicCommandCount = 0, regularCommandCount = 0;
    ifstream fin;

    cout << "Enter the name of a file to read from:" << endl;
    cin >> filename;
    cout << endl;

    fin.open(filename.c_str());

    if (!fin) {
        cerr << "File cannot be opened " << filename << endl;
        exit(1);
    }

    while(getline(fin, line)) {

        totalLineCount++;

        for (int i=0; i<line.length(); i++) { //int i = 0 might not work. size_t works then
            line[i] = tolower(line[i]);
        }
        
        if (line.substr(0,2) != "##" && line.substr(0,2) != "//") {
            for (int j=0; j<line.length(); j++) {
                if( j > 0 ){
                    if (line[j] == ' ' && line[j-1] != ' ') {
                        numWords++;
                    }
                    else if (j == (line.length() - 2) && line[j] != ' '){
                        numWords++;
                    }         
                }
            }
        }

        if (line.size() < 2) {
            continue;
        }
        else {
            if (line[0] == '/' && line[1] == '/') {
                commentedLineCount++;
            }
            else if (line[0] == '#' && line[1] == '#') {
                if (line.find("bold") != string::npos) {
                    boldCommandCount++;
                }
                else if (line.find("italic") != string::npos) {
                    italicCommandCount++;
                }
                else if (line.find("regular") != string::npos) {
                    regularCommandCount++;
                }
                else {
                    cerr << "Error: Unrecognizable command in line " << totalLineCount << endl << endl;
                }
            }
        }

    }

    fin.close();
    if (totalLineCount == 0){
        cout << "File is Empty" << endl;
        exit(1);
    }
    
    cout << "Total lines: " << totalLineCount << endl;
    cout << "Commented lines: " << commentedLineCount << endl;
    cout << "Number of words in the Text to be formatted: " << numWords << endl;
    cout << "Bold commands: " << boldCommandCount << endl;
    cout << "Italic commands: " << italicCommandCount << endl;
    cout << "Regular commands: " << regularCommandCount << endl;
    return 0;
}