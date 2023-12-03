#include <iostream>
#include <sstream>
#include <map>
#include <cctype>
#include <string>
#include <fstream>
#include "lex.h"
#include <unordered_set>

using namespace std;

LexItem id_or_kw(const string &lexeme, int linenum)
{

    // map of string lexeme to Token
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

    // create iterator for map and look for token
    map<string, Token>::iterator iterator = lexToTok.find(lexeme);

    // if iterator doesnt reach the bottom(means match is foudn) return LexItem
    if (iterator != lexToTok.end())
    {
        return LexItem(iterator->second, lexeme, linenum);
    }
    else
    {
        return LexItem(IDENT, lexeme, linenum);
    }

    // base return case
    return LexItem(IDENT, lexeme, linenum);
}

ostream &operator<<(ostream &out, const LexItem &tok)
{
    // initialize and call the get function for line, Token, lexeme
    int line;
    line = tok.GetLinenum();
    Token toks = tok.GetToken();
    string lexeme = tok.GetLexeme();

    // map for token to string
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
        {DONE, ""} // added
    };

    // find Token in map, get the value of it (string value) (used for printing out)
    string tokenName = tokenToString.find(toks)->second;

    // switch cases for tokens
    switch (toks)
    {
    // IDENT
    case IDENT:
        out << "IDENT: \"" << lexeme << "\"" << endl;
        break;
    // keywords
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

    // delimiters
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

    // ICONST/RCONST/BCONST
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

    // SCONST
    case SCONST:
        out << "SCONST: \"" << lexeme << "\"" << endl;
        break;

    // operators
    case PLUS:
    case MINUS:
    case MULT:
    case DIV:
    case IDIV:
    case MOD:
    case ASSOP:
    case EQ:
    case GTHAN:
    case LTHAN:
    case AND:
    case OR:
    case NOT:
        out << tokenName << endl;
        break;

    // error
    case ERR:
        out << "Error in line " << line << ": Unrecognized Lexeme {" << lexeme << "}" << endl;
        break;
    }
    return out;
}

LexItem getNextToken(istream &in, int &linenum)
{

    char ch;
    string lexeme;
    string tempLex;
    enum LexState
    {
        START,
        seenIDENT,
        seenINT,
        seenREAL,
        seenSTR,
        seenERR,
        seenComment
    };
    LexState state = START;

    while (in.get(ch))
    {
        switch (state)
        {
            // start case
        case START:
            if (isspace(ch))
            {
                if (ch == '\n')
                {
                    ++linenum;
                }
                continue; // Ignore leading spaces
            }
            if (isalpha(ch) || ch == '_' || ch == '$')
            {

                lexeme += ch;
                state = seenIDENT;
                continue;
            }
            else
            {

                if (ch == '{')
                {
                    state = seenComment;
                    continue;
                }
                if (isdigit(ch))
                {
                    lexeme += ch;
                    state = seenINT;
                    continue;
                }
                if (ch == '?')
                {
                    linenum++;
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ERR, tempLex, linenum);
                }
                if (ch == '+')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(PLUS, tempLex, linenum);
                }
                if (ch == '-')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(MINUS, tempLex, linenum);
                }
                if (ch == '*')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(MULT, tempLex, linenum);
                }
                if (ch == '/')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(DIV, tempLex, linenum);
                }
                if (ch == ':')
                {
                    lexeme += ch;
                    char nxtCh = in.peek();
                    if (nxtCh == '=')
                    {
                        in.get();
                        lexeme += nxtCh;
                        string tempLex = lexeme;
                        lexeme = "";
                        return LexItem(ASSOP, tempLex, linenum);
                    }
                    else
                    {
                        string tempLex = lexeme;
                        lexeme = "";
                        return LexItem(COLON, tempLex, linenum);
                    }
                }
                if (ch == '=')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(EQ, tempLex, linenum);
                }
                if (ch == '<')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(LTHAN, tempLex, linenum);
                }
                if (ch == '>')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(GTHAN, tempLex, linenum);
                }
                if (ch == ',')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(COMMA, tempLex, linenum);
                }
                if (ch == ';')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(SEMICOL, tempLex, linenum);
                }
                if (ch == '(')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(LPAREN, tempLex, linenum);
                }
                if (ch == ')')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(RPAREN, tempLex, linenum);
                }
                if (ch == '.')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(DOT, tempLex, linenum);
                }
                if (isalnum(ch) || ch == '_' || ch == '$')
                {
                    lexeme += ch;
                    state = seenIDENT;
                    continue;
                }
                if (ch == '\'')
                {
                    state = seenSTR;
                    //cout << "SAW A STR OMG -------->" << ch << endl;  ///////////////////////////////////////////////////
                    continue;
                }
                if (ch == '"')
                {
                    lexeme += ch;
                    state = seenERR;
                }
                //             }
                break;
                // ident case
            case seenIDENT:
                if (ch == '\n')
                {
                    in.unget();
                    state = START;
                    string tempLex = lexeme;
                    lexeme = "";
                    return id_or_kw(tempLex, linenum);
                }
                if (isalnum(ch) || ch == '_' || ch == '$')
                {
                    lexeme += ch;
                }
                else
                {
                    if (ch == '\n')
                    {
                        in.putback(ch);
                        state = START;
                        string tempLex = lexeme;
                        lexeme = "";
                        return id_or_kw(tempLex, linenum);
                    }
                    else
                    {
                        in.unget();
                        state = START;
                        string tempLex = lexeme;
                        lexeme = "";
                        return id_or_kw(tempLex, linenum);
                    }
                }
                break;

                // integer case
            case seenINT:
                if (ch == '.')
                {
                    lexeme += ch;
                    state = seenREAL;
                    continue;
                }
                else if (isalpha(ch))
                {
                    in.unget();
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ICONST, tempLex, linenum);
                }
                else if (isdigit(ch))
                {
                    lexeme += ch;
                }
                else if (ch == ',')
                {
                    in.unget();
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ICONST, tempLex, linenum);
                }
                else if (ch == ';')
                {
                    in.unget();
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ICONST, tempLex, linenum);
                }
                else
                {
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(ICONST, tempLex, linenum);
                }
                break;
                // real case
            case seenREAL:
                if (in.peek() == ',')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(RCONST, tempLex, linenum);
                }
                if (ch == '.')
                {
                    lexeme += ch;
                    string tempLex = lexeme;
                    lexeme = "";
                    linenum += 1;
                    return LexItem(ERR, tempLex, linenum);
                }
                if (isdigit(ch) || (ch == '.' && isdigit(in.peek())))
                {
                    lexeme += ch;
                }
                else
                {
                    in.putback(ch);
                    string tempLex = lexeme;
                    lexeme = "";
                    return LexItem(RCONST, tempLex, linenum);
                }
                break;

            case seenSTR:
                if( ch == '\n' ) {
                    return LexItem(ERR, lexeme, linenum);
                }
                lexeme += ch;
                if( ch == '\'' ) {
                    lexeme = lexeme.substr(1, lexeme.length()-2);
                    return LexItem(SCONST, lexeme, linenum);
                }
                break;

                // error case
            case seenERR:
                tempLex = lexeme;
                lexeme = "";
                return LexItem(ERR, tempLex, linenum + 1);
                break;
                // comment case
            case seenComment:
                if (ch != '}')
                {
                    if (ch != '\n')
                    {
                        continue;
                    }
                    else
                    {
                        linenum++;
                    }
                }
                else
                {
                    state = START;
                }
                break;
            }
        }
    }
    return LexItem(DONE, "", linenum);
}