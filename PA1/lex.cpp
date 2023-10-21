#include <iostream>
#include <sstream>
#include <map>
#include <cctype>
#include <string>
#include <fstream>
#include "lex.h"
#include <unordered_set>

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

    //create iterator for map and look for token
    map<string, Token>::iterator iterator = lexToTok.find(lexeme);

    //if iterator doesnt reach the bottom(means match is foudn) return LexItem
    if (iterator != lexToTok.end()) {
        return LexItem(iterator->second, lexeme, linenum);
    }
    else {
        return LexItem(IDENT, lexeme, linenum);
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
        {ERR, "ERR"},
        {DONE, ""} //added
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
        out << "IF" << endl;
        break;

        case ELSE:
        out << "ELSE" << endl;
        break;

        case WRITELN:
        out << "WRITELN" << endl;
        break;

        case WRITE:
        out << "WRITE" << endl;
        break;

        case INTEGER:
        out << "INTEGER" << endl;
        break;

        case REAL:
        out << "REAL" << endl;
        break;

        case BOOLEAN:
        out << "BOOLEAN" << endl;
        break;

        case STRING:
        out << "STRING" << endl;
        break;

        case BEGIN:
        out << "BEGIN" << endl;
        break;

        case END:
        out << "END" << endl;
        break;

        case VAR:
        out << "VAR" << endl;
        break;

        case THEN:
        out << "THEN" << endl;
        break;

        case PROGRAM:
        out << "PROGRAM" << endl;
        break;

        //delimiters
        case COMMA:
        out << "COMMA" << endl;
        break;

        case SEMICOL:
        out << "SEMICOL" << endl;
        break;

        case LPAREN:
        out << "LPAREN" << endl;
        break;

        case RPAREN:
        out << "RPAREN" << endl;
        break;

        case DOT:
        out << "DOT" << endl;
        break;

        case COLON:
        out << "COLON" << endl;
        break;

        case DONE:
        out << "" << endl;
        break;

        //ICONST/RCONST/BCONST
        case ICONST:
            out << "ICONST: \"" << lexeme << "\"" << endl;
            break;

        case RCONST:
            out << "RCONST: \"" << lexeme << "\"" << endl;
            break;

        case BCONST:
            out << "BCONST: \"" << lexeme << "\"" << endl;
            break;

        case TRUE:
            out << "BCONST: \"" << lexeme << "\"" << endl;
            break;
            
        case FALSE:
            out << "BCONST: \"" << lexeme << "\"" << endl;
            break;
        
        //SCONST
        case SCONST:
            out << "SCONST: \"" << lexeme << "\"" << endl;
            break;
        
        //operators
        case PLUS: case MINUS: case MULT: case DIV: case IDIV: case MOD: case ASSOP: case EQ: case GTHAN: case LTHAN: case AND: case OR: case NOT:
            out << tokenName << endl;
            break;

        //error
        case ERR:
        out << "Error: {" << lexeme << "} at line no. " << line << endl;
        break;
    }
    return out;
}


LexItem getNextToken(istream& in, int& linenum) {

    char ch;
    string lexeme;
    string tempLex;
    enum LexState {START, seenIDENT, seenINT, seenREAL, seenSTR, seenERR, seenComment};
    LexState state = START;

    
    while(in.get(ch)) {
        if(ch == '\n') {
            linenum++;
            continue;
        }

        switch(state) {
//start case
            case START:
                if (isspace(ch)) {
                    continue; // Ignore leading spaces
                }
                // if(isdigit(ch)){
                //     lexeme += ch;
                //     state = seenINT;
                // }
                if(isalpha(ch) || ch == '_' || ch == '$') {
                    lexeme += ch;
                    state = seenIDENT;
                    continue;
                }
                else {
                    if (ch == '\n') {
                        linenum++;
                        continue;
                    }
                    if(ch == '{') {
                        state = seenComment;
                        continue;
                    }
                    if(isdigit(ch)) {
                        lexeme += ch;
                        state = seenINT;
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
                    if(ch == '\'') {
                        state = seenSTR;
                        continue;
                    }
                    if(ch == '"') {
                        lexeme += ch;
                        state = seenERR;
                    }
                }
                break;
//ident case                
            case seenIDENT:
                if(isalnum(ch)|| ch == '_' || ch == '$') {
                    lexeme +=ch;
                }
                else {
                    in.unget();
                    state = START;
                    string tempLex = lexeme;
                    lexeme = "";
                    return id_or_kw(tempLex, linenum);
                }
                break;
//integer case                    
            case seenINT:
                if(isalpha(ch)) {
                    lexeme += ch;
                    state = seenIDENT;
                    continue;
                }
                else if(isdigit(ch)) {
                    lexeme += ch;
                }
                else if(ch == '.') {
                    lexeme += ch;
                    state = seenREAL;
                    continue;
                }
                else if(ch == ';') {
                    in.unget();
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ICONST, tempLex, linenum);
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
            // case seenEND:
            //     if(in.eof()) {
            //         return LexItem(DONE, lexeme, linenum);
            //     }
            //     break;
        }
    }
    return LexItem(DONE, "", linenum);
}