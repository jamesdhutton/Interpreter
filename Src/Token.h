#pragma once

enum eTokenID
{
	tIf, tWhile, tPrint, tAssignment, tBegin, tEnd,
	tIdentifier, tNumber, tPlus, tMinus, tOr, 
	tTimes, tDiv, tAnd, tLt, tGt, tEq, tNe, tOpenBracket,
	tCloseBracket, tNot, tMod, tEOF
};

struct sToken
{
	sToken(eTokenID _tok, char const *_s)
	 :  tok(_tok),
		s(_s)
	{}
	sToken(eTokenID _tok, long _nNumber)
	 :  tok(_tok),
		number(_nNumber)
	{}

	eTokenID tok;
	std::string s;
	long number;

};

typedef std::list<sToken> tokenList;
typedef tokenList::iterator tokenIt;
