#pragma once
#include <exception>

class SyntaxError : public std::exception
{
public:
	SyntaxError(const std::string &err) throw()
		: m_Err(err)
	{}
    
    virtual ~SyntaxError() throw()
    {}

	virtual const char *what() const throw()
	{
		return m_Err.c_str();
	}
private:
	std::string m_Err;

};