/* Implementation of Recursive-Descent Parser
	for a Simple Pasacal-Like Language
 * parser.cpp
 * Programming Assignment 2
 * Fall 2023
*/

//INCOMPLETE


#include "parser.h"

map<string, bool> defVar;
map<string, Token> SymTable;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}


bool Prog(istream& in, int& line) {
	//check for PROGRAM kwd

	if(Parser::GetNextToken(in, line) != PROGRAM) {
		ParseError(line, "Missing PROGRAM Keyword.");
		return false;
	}

	LexItem IdentTok = Parser::GetNextToken(in, line);

	//check if after PROGRAM is the IDENT program name
	if(IdentTok != IDENT) {
		ParseError(line, "Missing Program Name.");
	}

	//put ident in map(to save tok and skip to next, bcuz nothing to do with it)
	defVar[IdentTok.GetLexeme()] = true;

	LexItem s = Parser::GetNextToken(in, line);

	//check if after program name is a semicolon
	if(s != SEMICOL) {
		ParseError(line, "Missing SEMICOLON After Program Name.");
		return false;
	}

	if(!DeclPart) {
		ParseError(line, "Incorrect Declaration Statement.");
		return false;
	}

}





extern bool DeclPart(istream& in, int& line) {
	// LexItem nxt = Parser::GetNextToken(in, line);
	// Parser::PushBackToken(nxt);
	// if(nxt != VAR){
	// 	ParseError(line, "Non-recognizable Declaration Part. (Missing VAR Keyword)");
	// 	ParseError(line, "Incorrect Declaration Section.");
	// return false;
	// }
	// return true;
}


//WriteLnStmt ::= writeln (ExprList) 
bool WriteLnStmt(istream& in, int& line) {
	LexItem t;
	//cout << "in WriteStmt" << endl;
	
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression list for WriteLn statement");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	//Evaluate: print out the list of expressions values

	return ex;
}//End of WriteLnStmt


//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	//cout << "in ExprList and before calling Expr" << endl;
	status = Expr(in, line);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		//cout << "before calling ExprList" << endl;
		status = ExprList(in, line);
		//cout << "after calling ExprList" << endl;
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}//ExprList



