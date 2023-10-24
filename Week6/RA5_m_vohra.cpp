#include "lex.h"
#include <iostream>
#include <regex>

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

    //create iterator for map
    map<string, Token>::iterator iterator = lexToTok.find(lexeme);

    //if iterator doesnt reach the bottom(means match is foudn) return LexItem
    if (iterator != lexToTok.end()) {
        return LexItem(iterator->second, iterator->first, linenum);
    }

    #//base return case
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
        out << "IDENT: \"" << lexeme << "\" at line no. " << line << endl;
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
        out << "REAL: [" << lexeme << "] at line no. " << line << endl;
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
        out << "PROGRAM: [" << lexeme << "] at line no. " << line << endl;
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