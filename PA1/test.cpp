#include <iostream>
#include<map>
#include<cctype>

using namespace std;

enum statetype {
    start, seenint, seenid
};

int main()
{
    string s="123+456x9 ", lexeme="";

    int i=0;
    statetype state=start;

    while(i<s.length()) {
        switch(state) {
            case start:

            if(s[i]=='+') {
                cout<<"PLUS ";
                i++; //go to the next character
                continue; //go to the next iteration of the loop
            }

            //check if s[i] is a digit
            if(isdigit(s[i])) {
                state=seenint;
                lexeme+=s[i];
                i++;
                continue;
            }

            //check for ident
            if(isalpha(s[i])) {
                state=seenid;
                lexeme+=s[i];
                i++;
                continue;
            }

            i++;

            break;
            case seenint:

            if(isdigit(s[i])) { //int continues
                lexeme+=s[i];
                i++;
                continue;
            }
            else { //int is over
                cout<<"ICONST ("<<lexeme<<") ";
                lexeme="";
                //no i++: in the case of stream, you MUS"T use peek() or putback() to determine if the next character is part of the current lexeme
                state=start;
                continue;
            }

            break;
            case seenid:

            if(isalnum(s[i]) || s[i]=='_' || s[i]=='$') { //ident continue
                lexeme+=s[i];
                i++;
                continue;
            }
            else { //ident is over
                cout<<"IDENT ("<<lexeme<<") ";
                lexeme="";
                //no i++
                state=start;
                continue;
            }

            break;
        }
    }

    return 0;
}