// Program.h: interface for the Program class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "SyntaxError.h"
#include "Statement.h"
#include "Token.h"
#include "Context.h"


class Program  
{
public:
	Program(std::string program) throw(SyntaxError);
	void Execute();
	void PrettyPrint();

private: 
	static tokenList Lexical(std::string sProgram);
	statementList m_statements;
	Context m_context;
};

