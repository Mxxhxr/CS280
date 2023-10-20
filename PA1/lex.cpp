#include <iostream>
#include <sstream>
#include <map>
#include <cctype>
#include <string>
#include <fstream>
#include "lex.h"

using namespace std;

LexItem id_or_kw(const string &lexeme, int linenum) {

    //map of string lexeme to Token
    map<string, Token> lexToTok;

    lexToTok["if"] = IF;
    lexToTok["else"] = ELSE;
    lexToTok["writeln"] = WRITELN;
    lexToTok["write"] = WRITE;
    lexToTok["integer"] = INTEGER;
    lexToTok["real"] = REAL;
    lexToTok["boolean"] = BOOLEAN;
    lexToTok["string"] = STRING;
    lexToTok["begin"] = BEGIN;
    lexToTok["end"] = END;
    lexToTok["var"] = VAR;
    lexToTok["then"] = THEN;
    lexToTok["program"] = PROGRAM;

    lexToTok["true"] = BCONST;
    lexToTok["false"] = BCONST;

    lexToTok["+"] = PLUS;
    lexToTok["-"] = MINUS;
    lexToTok["*"] = MULT;
    lexToTok["/"] = DIV;
    lexToTok["div"] = IDIV;
    lexToTok["mod"] = MOD;
    lexToTok[":="] = ASSOP;
    lexToTok["="] = EQ;
    lexToTok[">"] = GTHAN;
    lexToTok["<"] = LTHAN;
    lexToTok["and"] = AND;
    lexToTok["or"] = OR;
    lexToTok["not"] = NOT;
    
    lexToTok[","] = COMMA;
    lexToTok[";"] = SEMICOL;
    lexToTok["("] = LPAREN;
    lexToTok[")"] = RPAREN;
    lexToTok["."] = DOT;
    lexToTok[":"] = COLON;
    lexToTok[""] = DONE;

    //create iterator for map
    map<string, Token>::iterator iterator = lexToTok.find(lexeme);

    //if iterator doesnt reach the bottom(means match is foudn) return LexItem
    if (iterator != lexToTok.end()) {
        return LexItem(iterator->second, iterator->first, linenum);
    }

    //base return case
    return LexItem(IDENT, lexeme, linenum);
}


ostream& operator<<(ostream& out, const LexItem& tok) {
    //initialize and call the get function for line, Token, lexeme
    int line;
    line = tok.GetLinenum();
    Token toks = tok.GetToken();
    string lexeme = tok.GetLexeme();

    //map for token to string
    map<Token, string> tokenToString = {
        {IDENT, "IDENT"},
        {IF, "IF"},
        {ELSE, "ELSE"},
        {WRITELN, "WRITELN"},
        {WRITE, "WRITE"},
        {INTEGER, "INTEGER"},
        {REAL, "REAL"},
        {BOOLEAN, "BOOLEAN"},
        {STRING, "STRING"},
        {BEGIN, "BEGIN"},
        {END, "END"},
        {VAR, "VAR"},
        {THEN, "THEN"},
        {PROGRAM, "PROGRAM"},
        {COMMA, "COMMA"},
        {SEMICOL, "SEMICOL"},
        {LPAREN, "LPAREN"},
        {RPAREN, "RPAREN"},
        {DOT, "DOT"},
        {COLON, "COLON"},
        {DONE, "DONE"},
        {ICONST, "ICONST"},
        {RCONST, "RCONST"},
        {BCONST, "BCONST"},
        {TRUE, "TRUE"},
        {FALSE, "FALSE"},
        {SCONST, "SCONST"},
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {MULT, "MULT"},
        {DIV, "DIV"},
        {IDIV, "IDIV"},
        {MOD, "MOD"},
        {ASSOP, "ASSOP"},
        {EQ, "EQ"},
        {GTHAN, "GTHAN"},
        {LTHAN, "LTHAN"},
        {AND, "AND"},
        {OR, "OR"},
        {NOT, "NOT"},
        {ERR, "ERR"}
    };

    //find Token in map, get the value of it (string value) (used for printing out)
    string tokenName = tokenToString.find(toks)->second;


        //switch cases for tokens
    switch(toks) {
        //IDENT
        case IDENT:
        out << "IDENT: \"" << lexeme << "\"" << endl;
        break;
        //keywords
        case IF:
        out << "IF: [" << lexeme << "] at line no. " << line << endl;
        break;

        case ELSE:
        out << "ELSE: [" << lexeme << "] at line no. " << line << endl;
        break;

        case WRITELN:
        out << "WRITELN: [" << lexeme << "] at line no. " << line << endl;
        break;

        case WRITE:
        out << "WRITE: [" << lexeme << "] at line no. " << line << endl;
        break;

        case INTEGER:
        out << "INTEGER: [" << lexeme << "] at line no. " << line << endl;
        break;

        case REAL:
        out << "REAL" << endl;
        break;

        case BOOLEAN:
        out << "BOOLEAN: [" << lexeme << "] at line no. " << line << endl;
        break;

        case STRING:
        out << "STRING: [" << lexeme << "] at line no. " << line << endl;
        break;

        case BEGIN:
        out << "BEGIN: [" << lexeme << "] at line no. " << line << endl;
        break;

        case END:
        out << "END: [" << lexeme << "] at line no. " << line << endl;
        break;

        case VAR:
        out << "VAR: [" << lexeme << "] at line no. " << line << endl;
        break;

        case THEN:
        out << "THEN: [" << lexeme << "] at line no. " << line << endl;
        break;

        case PROGRAM:
        out << "PROGRAM" << endl;
        break;

        //delimiters
        case COMMA:
        out << "COMMA: [" << lexeme << "] at line no. " << line << endl;
        break;

        case SEMICOL:
        out << "SEMICOL: [" << lexeme << "] at line no. " << line << endl;
        break;

        case LPAREN:
        out << "LPAREN: [" << lexeme << "] at line no. " << line << endl;
        break;

        case RPAREN:
        out << "RPAREN: [" << lexeme << "] at line no. " << line << endl;
        break;

        case DOT:
        out << "DOT: [" << lexeme << "] at line no. " << line << endl;
        break;

        case COLON:
        out << "COLON: [" << lexeme << "] at line no. " << line << endl;
        break;

        case DONE:
        out << "DONE: [" << lexeme << "] at line no. " << line << endl;
        break;

        //ICONST/RCONST/BCONST
        case ICONST:
            out << "ICONST: (" << lexeme << ") at line no. " << line << endl;
            break;

        case RCONST:
            out << "RCONST: (" << lexeme << ") at line no. " << line << endl;
            break;

        case BCONST:
            out << "BCONST: (" << lexeme << ") at line no. " << line << endl;
            break;

        case TRUE:
            out << "BCONST: (" << lexeme << ") at line no. " << line << endl;
            break;
            
        case FALSE:
            out << "BCONST: (" << lexeme << ") at line no. " << line << endl;
            break;
        
        //SCONST
        case SCONST:
            out << "SCONST: '" << lexeme << "' at line no. " << line << endl;
            break;
        
        //operators
        case PLUS: case MINUS: case MULT: case DIV: case IDIV: case MOD: case ASSOP: case EQ: case GTHAN: case LTHAN: case AND: case OR: case NOT:
            out << tokenName << ": [" << lexeme << "] at line no. " << line << endl;
            break;

        //error
        case ERR:
        out << "Error: {" << lexeme << "} at line no. " << line << endl;
        break;
    }
    return out;
}


// you iterate until you get a token
// and then you return that token with the updated linenumber and token you got from that
// and then you call next token again
LexItem getNextToken(istream& in, int& linenum) {

    char ch;
    string lexeme;
    string tempLex;

    enum LexState {START, seenIDENT, seenINT, seenREAL, seenSTR, seenERR, seenComment, seenEND};
    LexState state = START;

    while(in.get(ch)) {
        switch(state) {
//start case
            case START:
                if(isspace(ch)) {
                    continue;
                }
                if (ch == '\n') {
                    linenum++;
                    continue;
                }
                if(ch == '+') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(PLUS, tempLex, linenum);
                }
                if(ch == '-') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(MINUS, tempLex, linenum);
                }
                if(ch == '*') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(MULT, tempLex, linenum);
                }
                if(ch == '/') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(DIV, tempLex, linenum);
                }
                if(ch == ':') {
                    lexeme += ch;
                    char nxtCh = in.peek();
                    if(nxtCh == '=') {
                        in.get();
                        lexeme += nxtCh;
                        string tempLex = lexeme;
                        lexeme = "";
                        return LexItem(ASSOP, tempLex, linenum);
                    }
                    else {
                        string tempLex = lexeme;
                        lexeme = "";
                        return LexItem(COLON, tempLex, linenum);
                    }
                }
                if(ch == '=') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(EQ, tempLex, linenum); 
                }
                if(ch == '<') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(LTHAN, tempLex, linenum); 
                }
                if(ch == '>') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(GTHAN, tempLex, linenum); 
                }
                if(ch == ',') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(COMMA, tempLex, linenum);
                } 
                if(ch == ';') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(SEMICOL, tempLex, linenum);
                } 
                if(ch == '(') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(LPAREN, tempLex, linenum);
                } 
                if(ch == ')') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(RPAREN, tempLex, linenum);
                } 
                if(ch == '.') {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(DOT, tempLex, linenum);
                }
                if(isalnum(ch) || ch == '_' || ch == '$') {
                    lexeme += ch;
                    state = seenIDENT;
                    continue;
                }
                if(isdigit(ch)) {
                    lexeme += ch;
                    state = seenINT;
                    continue;
                }
                if(ch == '\'') {
                    state = seenSTR;
                    continue;
                }
                if(ch == '"') {
                    lexeme += ch;
                    state = seenERR;
                }
                if(ch == '{') {
                    state = seenComment;
                    continue;
                }
                
                break;
//ident case                
            case seenIDENT:    ///////////////////check on resrved kws
                if(isalnum(ch)|| ch == '_' || ch == '$') {
                    lexeme +=ch;
                }
                else if(lexeme == "END") {
                    state = seenEND;
                }
                else {
                    return id_or_kw(lexeme, linenum);
                    lexeme = "";
                }
                break;
//integer case                    
            case seenINT:
                if(isdigit(ch)) {
                    lexeme += ch;
                }
                else if(ch == '.') {
                    lexeme += ch;
                    state = seenREAL;
                    continue;
                }
                else {
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ICONST, tempLex, linenum);
                }
                break;
//real case                
            case seenREAL:
                if(isdigit(ch) && ch != '.') {
                    lexeme += ch;
                }
                else {
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(RCONST, tempLex, linenum);
                }
                break;
//string case
            case seenSTR:
                if(ch != '\'' && ch != '\n' && !in.eof()) {
                    lexeme += ch;
                }
                else {
                    if(ch == '\n') {
                        state = seenERR;
                        continue;
                    }
                    else if(in.eof()) {
                        return LexItem(ERR, lexeme, linenum);
                        continue;
                    }
                    else {
                        string tempLex = lexeme;
                        lexeme = "";
                        return LexItem(SCONST, tempLex, linenum);
                    }
                }
                break;
//error caase
            case seenERR:
                tempLex = lexeme;
                lexeme = "";
                return LexItem(ERR, tempLex, linenum);
                break;
//coment case
            case seenComment:
                if(ch != '}') {
                    continue;
                }
                else {
                    state = START;
                }
                break;
//done case
            case seenEND:
                if(in.eof()) {
                    return LexItem(DONE, lexeme, linenum);
                }
                break;
        }
    }
    return LexItem(DONE, "", linenum);
}