#pragma once

class CStringTokenizer 
{
public:
	CStringTokenizer (char const * szTokens, char const * szSeparators);
	~CStringTokenizer ();
	char const * GetNextToken ();
	long GetPos();

private:
	char *AllocStr (char const * s);
	bool IsSeparator (const char &c);
	void Increment();
	
	char * m_lpszOriginal;
	char * m_lpszTokens;
	char * m_lpszNextToken;
	char * m_lpszSeparators;

	long m_nCurrentPos;
	long m_nNextPos;
};
