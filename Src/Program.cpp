// Program.cpp: implementation of the Program class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "StringTokenizer.h"
#include "Program.h"
#include <string.h>

using namespace std;

struct sTokenStr
{
	eTokenID tok;
	const char *str;
};

static const sTokenStr Tokens[] =
{
	tWhile, "while",
	tIf, "if",
	tPrint, "print",
	tBegin, "begin",
	tEnd, "end",
	tOr, "or",
	tAnd, "and",
	tPlus, "+",
	tMinus, "-",
	tTimes, "*",
	tDiv, "/",
	tAssignment, ":=",
	tNe, "<>",
	tLt, "<",
	tGt, ">",
	tEq, "=",
	tOpenBracket, "(",
	tCloseBracket, ")",
	tNot, "not",
	tMod, "mod",
	tEOF, NULL
};


Program::Program(string program) throw(SyntaxError)
{
	tokenList tl = Lexical(program);

	tokenList::iterator it = tl.begin();

	while (it->tok != tEOF)
		m_statements.push_back(StatementPtr (Statement::Create(it)));
}

void Program::Execute()
{
	for (statementList::iterator it = m_statements.begin(); it != m_statements.end(); it++)
		it->get()->Execute(m_context);
}

tokenList Program::Lexical(string sProgram)
{
	tokenList result;

	CStringTokenizer s (sProgram.c_str(), " \r\n\t");
	for (char const *sTok = s.GetNextToken(); sTok != NULL; sTok = s.GetNextToken())
	{

		bool bFound = false;
		for (const sTokenStr *pTokenStr = Tokens; pTokenStr->str != NULL && !bFound; pTokenStr++)
			if ((bFound = (strcmp(pTokenStr->str, sTok)) == 0))
				result.push_back (sToken(pTokenStr->tok, sTok));

		if (!bFound)
		{
			string ident (sTok);
			long nNumber = 0;
			if (ident == "0" || (nNumber = atol(ident.c_str())) != 0)
				result.push_back (sToken(tNumber, nNumber));
			else
				result.push_back (sToken(tIdentifier, ident.c_str()));
		}

	}

	result.push_back (sToken(tEOF, ""));

	return result;
}

void Program::PrettyPrint()
{
	long tabLevel = 0;
	for (statementList::iterator it = m_statements.begin(); it != m_statements.end(); it++)
		it->get()->PrettyPrint(tabLevel);
}