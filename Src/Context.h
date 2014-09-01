#pragma once

class Context
{
public:
	long GetValue(std::string variable);
	long SetValue(std::string variable, long value);
private:
	typedef std::map<std::string, long> VarMap;
	VarMap m_symbols;
};