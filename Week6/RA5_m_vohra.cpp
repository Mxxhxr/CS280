#include "lex.h"
#include <iostream>
#include <regex>

using namespace std;

LexItem id_or_kw(const string &lexeme, int linenum) {

    if(lexeme.empty()) {
        return LexItem(DONE, "EOF", linenum); // do i need this?
    }

    if (lexeme.size() >= 2 && lexeme[0] == '"' && lexeme[lexeme.size() - 1] == '"') {
        // It's a string enclosed in double quotes.
        return LexItem(SCONST, lexeme, linenum);
    }

    if (lexeme == ":") {
        return LexItem(COLON, ":", linenum);
    }
    else if (lexeme == "=") {
        return LexItem(EQ, "=", linenum);
    }
    else if (lexeme == ":=") {
        return LexItem(ASSOP, ":=", linenum);
    }

//check if its a number, if it is, check if its decimal or integer
    if (isdigit(lexeme[0])) {
        // If it starts with a digit, it's not an identifier.
        bool isNumber = true;

        for (char c : lexeme) {
            if (!isdigit(c) && c != '.') {
                isNumber = false;
                break;
            }
        }

    if (isNumber) {
        if (lexeme.find('.') != string::npos) {
            return LexItem(RCONST, lexeme, linenum);
        } else {
            return LexItem(ICONST, lexeme, linenum);
        }
    }
    }
    
    if(lexeme == "false" || lexeme == "true") {
        return LexItem(BCONST, lexeme, linenum);
    }


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
    // lexToTok[":="] = ASSOP;
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

    map<string, Token>::iterator it = lexToTok.find(lexeme);
    if (it != lexToTok.end()) {
            if (lexeme.length() == 1 || !isalnum(lexeme[lexeme.length() - 1])) {
                // It's a keyword only if it's not followed by a letter or digit
                return LexItem(it->second, it->first, linenum);
            }
        }

    // if(it != lexToTok.end()) {
    //     return LexItem(it->second, it->first, linenum);
    // }
    
    // Check if the lexeme consists of only valid characters for an IDENT
    bool isIdent = true;
    for (char c : lexeme) {
        if (!isalnum(c) && c != '_') {
            isIdent = false;
            break;
        }
    }

    // Return either IDENT or ERR based on the isIdent flag
    if (isIdent) {
        return LexItem(IDENT, lexeme, linenum);
    } 
    else {
        return LexItem(ERR, lexeme, linenum);
    }

    return LexItem(IDENT, lexeme, linenum);

}

    ostream& operator<<(ostream& out, const LexItem& tok) {
        int line;
        line = tok.GetLinenum();
        Token toks = tok.GetToken();
        string lexeme = tok.GetLexeme();

        switch(toks) {
            //IDENT
            case IDENT:
            out << "IDENT: \"" << lexeme << "\" at Line no. " << line << endl;
            break;
            //keywords
            case IF:
            out << "IF: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case ELSE:
            out << "ELSE: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case WRITELN:
            out << "WRITELN: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case WRITE:
            out << "WRITE: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case INTEGER:
            out << "INTEGER: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case REAL:
            out << "REAL: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case BOOLEAN:
            out << "BOOLEAN: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case STRING:
            out << "STRING: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case BEGIN:
            out << "BEGIN: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case END:
            out << "END: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case VAR:
            out << "VAR: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case THEN:
            out << "THEN: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case PROGRAM:
            out << "PROGRAM: [" << lexeme << "] at Line no. " << line << endl;
            break;

            //delimiters
            case COMMA:
            out << "COMMA: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case SEMICOL:
            out << "SEMICOL: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case LPAREN:
            out << "LPAREN: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case RPAREN:
            out << "RPAREN: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case DOT:
            out << "DOT: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case COLON:
            out << "COLON: [" << lexeme << "] at Line no. " << line << endl;
            break;

            case DONE:
            out << "DONE: [" << lexeme << "] at Line no. " << line << endl;
            break;

            //ICONST/RCONST/BCONST
            case ICONST:
                out << "ICONST: (" << lexeme << ") at Line no. " << line << endl;
                break;

            case RCONST:
                out << "RCONST: (" << lexeme << ") at Line no. " << line << endl;
                break;

            case BCONST:
                out << "BCONST: (" << lexeme << ") at Line no. " << line << endl;
                break;

            case TRUE:
                out << "BCONST: (" << lexeme << ") at Line no. " << line << endl;
                break;
                
            case FALSE:
                out << "BCONST: (" << lexeme << ") at Line no. " << line << endl;
                break;
            
            //SCONST
            case SCONST:
                out << "SCONST: '" << lexeme << "' at Line no. " << line << endl;
                break;
            
            //operators
            case PLUS: case MINUS: case MULT: case DIV: case IDIV: case MOD: case ASSOP: case EQ: case GTHAN: case LTHAN: case AND: case OR: case NOT:
                out << toks << ": [" << lexeme << "] at Line no. " << line << endl;
                break;

            //error
            case ERR:
            out << "ERROR: {" << lexeme << "} at Line no. " << line << endl;
            break;
        }
        return out;
    }
// create a map that has lexeme, token
// search map for lexeme and create LexItem with the corresponding token
// pass it to operator<<() function and print out Lexitem object according to token value
