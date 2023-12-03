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


bool Prog(istream &in, int &line)
{

	

	if (Parser::GetNextToken(in, line) != PROGRAM)
	{
		ParseError(line, "Missing PROGRAM.");
		return false;
	}

	LexItem identToken = Parser::GetNextToken(in, line);

	if (identToken != IDENT)
	{
		ParseError(line, "Missing Program Name.");
		return false;
	}

	// save ident in map
	defVar[identToken.GetLexeme()] = true;

	if (Parser::GetNextToken(in, line) != SEMICOL)
	{
		ParseError(line, "Missing semicolon in Statement.");
		return false;
	}

	if (!DeclPart(in, line))
	{
		ParseError(line, "Incorrect Declaration Section.");
		// print error wrong declaration section
		return false;
	}

	if (!CompoundStmt(in, line))
	{
		ParseError(line, "Incorrect Program Body.");
		// print error wrong body
		return false;
	}

	return true;
}
// DeclPart ::= VAR DeclStmt; { DeclStmt ; }
bool DeclPart(istream &in, int &line) {

	if (Parser::GetNextToken(in, line) != VAR) {
		ParseError(line, "Missing 'VAR' in DeclPart");
		return false;
	}

	while (true) {

		if (!DeclStmt(in, line)) {
			ParseError(line, "Syntactic error in Declaration Block.");
			return false;
		}

		LexItem currentToken = Parser::GetNextToken(in, line);

		//cout << "Should be a semicolon: " << currentToken << " on line " << line << endl;

		if (currentToken != SEMICOL)
		{
			ParseError(line, "Missing semicolon");
			return false;
		}

		currentToken = Parser::GetNextToken(in, line);
		Parser::PushBackToken(currentToken);		
		if (currentToken == BEGIN) {
			break;
		}

	}
	return true;
}

// DeclStmt ::= IDENT {, IDENT } : Type [:= Expr]
bool DeclStmt(istream &in, int &line) {
	while (true) {
		LexItem currentToken = Parser::GetNextToken(in, line);
		if (currentToken != IDENT) {
			return false;
		}
		bool isDefined = defVar.find(currentToken.GetLexeme())->second == true;
		if (isDefined) {
			ParseError(line, "Variable Redefinition");
			ParseError(line, "Incorrect variable in Declaration Statement.");
			return false;
		}
		else {

			defVar[currentToken.GetLexeme()] = true;
		}

		LexItem commaToken = Parser::GetNextToken(in, line);
		if (commaToken != COMMA) {
			Parser::PushBackToken(commaToken);
			break;
		}
	}

	LexItem colonToken = Parser::GetNextToken(in, line);
	if (colonToken != COLON) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << colonToken.GetLexeme() << ")" << endl;
		ParseError(line, "Incorrect identifiers(?) in Declaration Statement.");
		return false;
	}

	LexItem dataType = Parser::GetNextToken(in, line);
	if (dataType != INTEGER && dataType != REAL && dataType != STRING && dataType != BOOLEAN) {
		ParseError(line, "Incorrect Declaration Type.");
		return false;
	}

	LexItem isAssop = Parser::GetNextToken(in, line);
	if(isAssop == ASSOP) { 
		if (!Expr(in, line)) {
			ParseError(line, "Syntactic error in Declaration Statement.");
			return false;
		}
		return true;
	}
	else {
		Parser::PushBackToken(isAssop);
	}
	return true;
}

// CompoundStmt ::= BEGIN Stmt {; Stmt } END
bool CompoundStmt(istream &in, int &line) {
	LexItem currentToken = Parser::GetNextToken(in, line);
	if(currentToken != BEGIN) {
		ParseError(line, "No BEGIN in CompoundStmt.");
		return false;
	}

	if (Stmt(in, line) == false) {
		ParseError(line, "Syntactic error in CompountStmt.");
		return false;
	}

	while (true) {
		currentToken = Parser::GetNextToken(in, line);
		if (currentToken != SEMICOL) {
			Parser::PushBackToken(currentToken);
			break;
		}

		if (Stmt(in, line) == false) {
			ParseError(line, "Syntactic error in Program Body.");
			return false;
		}
	}
	if(currentToken == END) {
		return true;
	}
	return false;
}

// SimpleStmt ::= AssignStmt | WriteLnStmt | WriteStmt
bool SimpleStmt(istream& in, int& line) {
	bool statementStatus;

	LexItem currentToken = Parser::GetNextToken(in, line);
	switch (currentToken.GetToken()) {

	case WRITE:
		statementStatus = WriteStmt(in, line);
		break;

	case WRITELN:
		statementStatus = WriteLnStmt(in, line);
		break;

	case IDENT:
		Parser::PushBackToken(currentToken);
		statementStatus = AssignStmt(in, line);
		break;

	default:
		Parser::PushBackToken(currentToken);
		return false;
	}

	return statementStatus;
}

// StructuredStmt ::= IfStmt | CompoundStmt
bool StructuredStmt(istream& in, int& line) {
	bool statementStatus;

	LexItem currentToken = Parser::GetNextToken(in, line);
	switch (currentToken.GetToken()) {

	case IF:
		statementStatus = IfStmt(in, line);
		break;

	case BEGIN:
		Parser::PushBackToken(currentToken);
		statementStatus = CompoundStmt(in, line);
		break;

	default:
		Parser::PushBackToken(currentToken);
		return false;
	}

	return statementStatus;
}




// Stmt ::= SimpleStmt | StructuredStmt
bool Stmt(istream &in, int &line) {
	return SimpleStmt(in, line) || StructuredStmt(in, line);
}


// WriteLnStmt ::= WRITELN (ExprList)
bool WriteLnStmt(istream &in, int &line) {
	LexItem currentToken = Parser::GetNextToken(in, line);

	if (currentToken != LPAREN) {
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}

	bool expression = ExprList(in, line);

	if (!expression) {
		ParseError(line, "Missing expression after WriteLn");
		return false;
	}

	currentToken = Parser::GetNextToken(in, line);

	if (currentToken != RPAREN) {
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}

	return expression;
}


// WriteStmt ::= WRITE (ExprList)
bool WriteStmt(istream& in, int& line) {
		LexItem currentToken = Parser::GetNextToken(in, line);

	if (currentToken != LPAREN) {
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}

	bool expression = ExprList(in, line);

	if (!expression) {
		ParseError(line, "Missing expression after WriteLn");
		return false;
	}

	currentToken = Parser::GetNextToken(in, line);

	if (currentToken != RPAREN) {
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}

	return expression;
}



// IfStmt ::= IF Expr THEN Stmt [ ELSE Stmt ]
bool IfStmt(istream& in, int& line) {
	//Already checked if in STMT

    // Parse the logical expression (Expr)
    bool exprResult = Expr(in, line);
    if (!exprResult) {
        ParseError(line, "Failed Expr in IfStmt");
        return false;
    }

    // Parse the "THEN" keyword
    LexItem thenToken = Parser::GetNextToken(in, line);
    if (thenToken != THEN) {
        ParseError(line, "Expected THEN in IfStmt");
        return false;
    }

    // Parse the statement in the If-clause
    bool thenStmtResult = Stmt(in, line);
    if (!thenStmtResult) {
        ParseError(line, "Missing Statement in If-Stmt Then-Part");
        return false;
    }

    // Check if there is an optional "ELSE" clause
    LexItem elseToken = Parser::GetNextToken(in, line);
    if (elseToken == ELSE) {
        // Parse the statement in the Else-clause
        bool elseStmtResult = Stmt(in, line);
        if (!elseStmtResult) {
            ParseError(line, "Failed Stmt in Else-clause of IfStmt");
            return false;
        }
    }
	else {
        Parser::PushBackToken(elseToken);
    }

    // If all components of the IfStmt rule are successfully parsed, return true
    return true;
}

bool AssignStmt(istream &in, int &line)
{
	if (!Var(in, line)) {
		ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
		return false;
	}

	if (Parser::GetNextToken(in, line) != ASSOP) {
		ParseError(line, "Missing Assignment Operator");
		return false;
	}
	if (!Expr(in, line)) {
		ParseError(line, "Missing Expression in Assignment Statment");
		return false;
	}
	return true;
}

bool Expr(istream &in, int &line) {

	LexItem currentToken;
	while (true) {
		if (!LogANDExpr(in, line)) {
			ParseError(line, "Missing operand after operator");
			return false;
		}

		currentToken = Parser::GetNextToken(in, line);

		if (currentToken != OR) {
			Parser::PushBackToken(currentToken);
			break;
		}
	}
	return true;
}

bool ExprList(istream &in, int &line) {
	bool expressionStatus = false;

	expressionStatus = Expr(in, line);
	if (!expressionStatus) {
		ParseError(line, "Missing Expression");
		return false;
	}

	LexItem currentToken = Parser::GetNextToken(in, line);

	if (currentToken == COMMA) {
		expressionStatus = ExprList(in, line);
	}
	else if (currentToken.GetToken() == ERR) {
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << currentToken.GetLexeme() << ")" << endl;
		return false;
	}
	else {
		Parser::PushBackToken(currentToken);
		// send back
		return true;
	}
	return expressionStatus;
}


bool Term(istream &in, int &line) {
	while (true) {
		if (SFactor(in, line) == false)
		{
			// go back
			return false;
		}

		LexItem currentToken = Parser::GetNextToken(in, line);
		if (currentToken != MULT && currentToken != DIV && currentToken != IDIV && currentToken != MOD)	{
			Parser::PushBackToken(currentToken);
			break;
		}
	}
	return true;
}

bool SFactor(istream &in, int &line) {
	LexItem currentToken = Parser::GetNextToken(in, line);

	if (currentToken != PLUS && currentToken != MINUS && currentToken != NOT) {
		Parser::PushBackToken(currentToken);
	}

	int num = 0;
	if (!Factor(in, line, num)) {
		return false;
	}

	return true;
}

bool LogANDExpr(istream &in, int &line) {
	LexItem currentToken;
	while (true) {

		if (!RelExpr(in, line)) {
			ParseError(line, "Missing operand after operator");
			return false;
		}

		currentToken = Parser::GetNextToken(in, line);

		if (currentToken != AND) {
			// wrong input
			Parser::PushBackToken(currentToken);
			break;
		}
	}
	return true;
}

bool RelExpr(istream &in, int &line) {

	LexItem currentToken;

	if (!SimpleExpr(in, line)) {
		ParseError(line, "Missing operand after operator");
		return false;
	}

	currentToken = Parser::GetNextToken(in, line);

	if (currentToken != LTHAN && currentToken != GTHAN && currentToken != EQ) {
		// wrong input
		Parser::PushBackToken(currentToken);
		return true;
	}

	if (!SimpleExpr(in, line)) {
		ParseError(line, "Missing operand after operator");
		return false;
	}
	return true;
}

bool SimpleExpr(istream &in, int &line) {
	while(true) {
		LexItem currentToken;

		if (!Term(in, line)) {
			ParseError(line, "Missing operand after operator");
			return false;
		}

		currentToken = Parser::GetNextToken(in, line);

		if (currentToken != PLUS && currentToken != MINUS) {
			Parser::PushBackToken(currentToken);
			break;
		}
	}
	return true;
}

bool Factor(istream &in, int &line, int sign) {
	LexItem currentToken = Parser::GetNextToken(in, line);
	if (currentToken == SCONST || currentToken == ICONST || currentToken == RCONST || currentToken == BCONST || currentToken == IDENT) {
		return true;
	}

	if (currentToken != LPAREN) {
		ParseError(line, "Missing ( after expression");
		return false;
	}

	if (!Expr(in, line)) {
		ParseError(line, "Missing expression after LPAREN in Factor");
		return false;
	}

	LexItem rParenthToken = Parser::GetNextToken(in, line);
	if (rParenthToken != RPAREN) {
		//cout << "TOKEN: " << rParenthToken << endl;
		ParseError(line, "Missing ) after expression");
		return false;
	}
	return true;
}

bool Var(istream &in, int &line) {
	LexItem currentToken = Parser::GetNextToken(in, line);

	if (currentToken != IDENT)
	{
		ParseError(line, "not a valid variable because Not an IDENT in Var");
		return false;
	}
	bool isDeclared = defVar.find(currentToken.GetLexeme())->second == true;
	if (!isDeclared)
	{
		ParseError(line, "Undeclared Variable");
		return false;
	}

	return true;
}
