#include "StdAfx.h"
#include "Context.h"

using namespace std;

long Context::GetValue(string variable)
{
	long nResult;
	VarMap::iterator it = m_symbols.find(variable);
	if (it == m_symbols.end())
		nResult = SetValue(variable, 0);
	else
		nResult = it->second;

	return nResult;
}

long Context::SetValue(string variable, long value)
{
	return m_symbols[variable] = value;
}
