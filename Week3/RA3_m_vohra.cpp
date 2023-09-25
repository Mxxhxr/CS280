#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
using namespace std;

bool isSpecialName(string the_word) {
    if(the_word.length() == 1) return false;
    
    if((the_word[0] == '_' || the_word[0] == '@') && isalpha(the_word[1]) != 0) { 
        if(the_word.find("__") != std::string::npos) { //checks if __ is in the the_word
            return false;
        }
        else if(the_word.find('@', 1) != std::string::npos) {
            return false;
        }
        else if(!isalnum(the_word.back())){
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

    string line;
    int numWords = 0; 
    int lineCount = 0;
    int numSpecialName = 0;
    
    while (getline(inFile, line)) {
        lineCount++;
        istringstream iss(line);
        string word;
        while(iss >> word) {
            numWords++;
            bool is_spc_nm = isSpecialName(word);
            // cout << is_spc_nm << " : "<< word << endl;
            if( is_spc_nm == true) {
                numSpecialName++;
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