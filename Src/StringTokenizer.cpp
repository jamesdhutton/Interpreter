#include "stdafx.h"
#include "StringTokenizer.h"

CStringTokenizer::CStringTokenizer (char const * szTokens, char const * szSeparators)
  : m_lpszTokens (NULL)
  , m_lpszSeparators (NULL)
  , m_nNextPos(0)
  , m_nCurrentPos(0)
{
	m_lpszTokens = AllocStr (szTokens);
	m_lpszSeparators = AllocStr (szSeparators);
	m_lpszNextToken = m_lpszTokens;
}

CStringTokenizer::~CStringTokenizer ()
{
	delete [] m_lpszTokens;
	delete [] m_lpszSeparators;
}

char const * CStringTokenizer::GetNextToken ()
{
	while (*m_lpszNextToken != NULL && IsSeparator (*m_lpszNextToken))
		Increment();

	if (*m_lpszNextToken == NULL)
		return NULL;
	
	m_nCurrentPos = m_nNextPos;

	char const * lpszResult = m_lpszNextToken;

	for (Increment(); *m_lpszNextToken != NULL && !IsSeparator (*m_lpszNextToken); Increment());

	if (*m_lpszNextToken != NULL)
	{
		*m_lpszNextToken = NULL;
		Increment();
	}

	return lpszResult;
}

bool CStringTokenizer::IsSeparator (const char &c)
{
	bool bResult = false;
	for (const char *pSep = m_lpszSeparators; *pSep != NULL; pSep++)
		if (bResult = (*pSep == c))
			break;
	return bResult;
}

char * CStringTokenizer::AllocStr (char const * s)
{
	char * lpszResult = new char[strlen(s) + 1];
	return strcpy (lpszResult, s);
}

long CStringTokenizer::GetPos() 
{ 
	return m_nCurrentPos;
}

void CStringTokenizer::Increment()
{
	m_nNextPos++;
	m_lpszNextToken++;
}

