#include "lex.h"
#include <iostream>

using namespace std;

LexItem id_or_kw(const string &lexeme, int linenum)
{
    map<string, Token> lexToTok = {
        {"if", IF},
        {"else", ELSE},
        {"writeln", WRITELN},
        {"write", WRITE},
        {"integer", INTEGER},
        {"real", REAL},
        {"boolean", BOOLEAN},
        {"string", STRING},
        {"begin", BEGIN},
        {"end", END},
        {"var", VAR},
        {"then", THEN},
        {"program", PROGRAM},

        {"true", BCONST},
        {"false", BCONST},

        {"+", PLUS},
        {"-", MINUS},
        {"*", MULT},
        {"/", DIV},
        {"div", IDIV},
        {"mod", MOD},
        {":=", ASSOP},
        {"=", EQ},
        {">", GTHAN},
        {"<", LTHAN},
        {"and", AND},
        {"or", OR},
        {"not", NOT},

        {",", COMMA},
        {";", SEMICOL},
        {"(", LPAREN},
        {")", RPAREN},
        {".", DOT},
        {":", COLON}

        //{"done", DONE}
        //{"err", ERR}
        // {"rconst", RCONST},
        // {"sconst", SCONST},
        //{"iconst", ICONST}};
        //{"ident", PROGRAM}, if doesnt match, assign to IDENT
    };

    for (auto const &x : lexToTok)
    {
        cout << x.first << endl;
        cout << x.second << endl;
    }
}
// switch (lexeme)
// {
// case ";":
//     return LexItem(SEMICOL, lexeme, lineum);
// }

// create a map that has lexeme, token
// search map for lexeme and create LexItem with the corresponding token
// pass it to operator<<() function and print out Lexitem object according to token value

int main()
{
    id_or_kw(".", 3);
}