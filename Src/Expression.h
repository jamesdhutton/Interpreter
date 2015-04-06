// Expression.h: interface for the Expression class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "SyntaxError.h"
#include "Token.h"
#include "Context.h"

class Expression  
{
public:
	typedef std::shared_ptr<Expression> ExprPtr;
	typedef std::list<ExprPtr> Exprs;
	typedef std::shared_ptr<Exprs> ExprsPtr;
	static ExprPtr Parse(tokenIt &it) throw(SyntaxError);
	virtual long Evaluate(Context &context) = 0;
	virtual void PrettyPrint() = 0;
	virtual ~Expression() {};
protected:
	static void Expect(eTokenID eExpected, const sToken &sActual) throw (SyntaxError);
};

class MultExp : public Expression
{
public:
	static ExprPtr Parse(tokenIt &it);
	virtual long Evaluate(Context &context);
	virtual void PrettyPrint();
private:
	Exprs m_exprs;
	std::list<eTokenID> m_ops;
};

class AddExp : public Expression
{
public:
	static ExprPtr Parse(tokenIt &it);
	virtual long Evaluate(Context &context);
	virtual void PrettyPrint();
private:
	Exprs m_exprs;
	std::list<bool> m_ops;
};

class ComparisonExp : public Expression
{
public:
	ComparisonExp(ExprPtr lhs, ExprPtr rhs, eTokenID tok);
	static ExprPtr Parse(tokenIt &it);
	virtual long Evaluate(Context &context);
	virtual void PrettyPrint();
private:
	ExprPtr m_lhs;
	ExprPtr m_rhs;
	eTokenID m_tok;
};

class AndExp : public Expression
{
public:
	static ExprPtr Parse(tokenIt &it);
	virtual long Evaluate(Context &context);
	virtual void PrettyPrint();
private:
	Exprs m_exprs;
};

class OrExp : public Expression
{
public:
	static ExprPtr Parse(tokenIt &it);
	virtual long Evaluate(Context &context);
	virtual void PrettyPrint();
private:
	Exprs m_exprs;
};

class Atom : public Expression
{
public:
	static ExprPtr Parse(tokenIt &it);
};

class Number : public Atom
{
public:
	Number (long number) : m_number(number) {}
	virtual long Evaluate(Context &context) { return m_number; }
	virtual void PrettyPrint() { std::cout << " " << m_number << " "; }
private:
	long m_number;
};

class Not : public Atom
{
public:
	Not (ExprPtr expr) : m_expr (expr) {}
	virtual long Evaluate(Context &context) { return !m_expr->Evaluate(context); }
	virtual void PrettyPrint() { std::cout << " not "; m_expr->PrettyPrint();  }
private:
	ExprPtr m_expr;
};

class Identifier : public Atom
{
public:
	Identifier (std::string identifier) : m_identifier(identifier) {}
	virtual long Evaluate(Context &context) { return context.GetValue(m_identifier); }
	virtual void PrettyPrint() { std::cout << " " << m_identifier << " "; }
private:
	std::string m_identifier;
};

class CompoundAtom : public Atom
{
public:
	CompoundAtom(ExprPtr expr) : m_expression(expr) {}
	virtual long Evaluate(Context &context) { return m_expression->Evaluate(context); }
	virtual void PrettyPrint();
private:
	ExprPtr m_expression;
};
