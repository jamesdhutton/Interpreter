#pragma once
#include <exception>

class SyntaxError : public std::exception
{
public:
	SyntaxError(const std::string &err)
		: m_Err(err)
	{}

	virtual const char *what()
	{
		return m_Err.c_str();
	}
private:
	std::string m_Err;

};