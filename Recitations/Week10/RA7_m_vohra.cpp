#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

bool inLanguage(string & inputString) {
    if(inputString.empty()) {
        cout << "Empty string is not in the Language." << endl;
        return false;
    }
    
    if(inputString.find('#') == string::npos) {
        cout << "string is missing #." << endl;
        return false;
    }

    if(inputString == "#") {
        return true;
    }
     
    //by using queue before and stack for after, if it is in the language, they will be the same
    //example abc#cba -> queue will have CBA and stack will have ABC
    //since queue is FIFO, first one out will be A, stack is FILO so first one out wil be A. 
    //We can then compare the one we just pushed out and repeat this cycle

    //queue and stack initalization
    queue<char> beforeHashtag;
    stack<char> afterHashtag;

    //add everything into queue before hashtag
    int i = 0;
    while(inputString[i] != '#') {
        beforeHashtag.push(inputString[i]);
        i++;
    }

    //skip hashtag
    i++;

    //add everything else
    while(i< inputString.length()) {
        afterHashtag.push(inputString[i]);
        i++;
    }
        
    //compare queue and stack
    while(!beforeHashtag.empty() && !afterHashtag.empty()) {

        if(beforeHashtag.front() != afterHashtag.top()) {
            return false;
        }
        else {
            beforeHashtag.pop();
            afterHashtag.pop();
        }
        return true;
    }
    return false;
}