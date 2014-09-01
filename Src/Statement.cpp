// Statement.cpp: implementation of the Statement class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Statement.h"

using namespace std;

// Statement

void Statement::Expect(eTokenID eExpected, const sToken &sActual) throw (SyntaxError)
{
	if (eExpected != sActual.tok)
	{
		stringstream sErrMsg;
		sErrMsg << "Expected something else at " << sActual.s;
		throw SyntaxError(sErrMsg.str());
	}
}

Statement *Statement::Create(tokenIt &it)
{
	switch (it->tok)
	{
	case tIf:
		return new IfStatement(it);
	case tPrint:
		return new PrintStatement(it);
	case tWhile:
		return new WhileStatement(it);
	case tBegin:
		return new CompoundStatement(it);
	case tIdentifier:
		return new AssignmentStatement(it);
	default:
		throw SyntaxError(string("Unexpected: ") + it->s);
	}
}

void Statement::OutputTabs(long tabLevel)
{
	while (tabLevel-- > 0)
		cout << "\t";
}

// IfStatement

IfStatement::IfStatement(tokenIt &it)
{
	Expect(tIf, *it++);
	m_expression = Expression::Parse(it);
	m_statement = StatementPtr(Statement::Create(it));
}

void IfStatement::Execute(Context &context)
{
	if (m_expression->Evaluate(context))
		m_statement->Execute(context);
}

void IfStatement::PrettyPrint(long &tabLevel)
{
	OutputTabs(tabLevel);
	cout << "if ";
	m_expression->PrettyPrint();
	cout << endl;
	tabLevel++;
	m_statement->PrettyPrint(tabLevel);
	tabLevel--;
}

// WhileStatement

WhileStatement::WhileStatement(tokenIt &it)
{
	Expect(tWhile, *it++);
	m_expression = Expression::Parse(it);
	m_statement = StatementPtr(Statement::Create(it));
}

void WhileStatement::Execute(Context &context)
{
	while (m_expression->Evaluate(context))
		m_statement->Execute(context);
}

void WhileStatement::PrettyPrint(long &tabLevel)
{
	OutputTabs(tabLevel);
	cout << "while ";
	m_expression->PrettyPrint();
	cout << endl;
	tabLevel++;
	m_statement->PrettyPrint(tabLevel);
	tabLevel--;
}

// PrintStatement

PrintStatement::PrintStatement(tokenIt &it)
{
	Expect(tPrint, *it++);
	m_expression = Expression::Parse(it);
}

void PrintStatement::Execute(Context &context)
{
	cout << m_expression->Evaluate(context) << endl;
}

void PrintStatement::PrettyPrint(long &tabLevel)
{
	OutputTabs(tabLevel);
	cout << "print ";
	m_expression->PrettyPrint();
	cout << endl;
}

// CompoundStatement

CompoundStatement::CompoundStatement(tokenIt &it)
{
	Expect(tBegin, *it++);
	while (it->tok != tEnd && it->tok != tEOF)
		m_statements.push_back (StatementPtr(Statement::Create(it)));
	Expect(tEnd, *it++);
}

void CompoundStatement::Execute(Context &context)
{
	for (statementList::iterator it = m_statements.begin(); it != m_statements.end(); it++)
		it->get()->Execute(context);
}

void CompoundStatement::PrettyPrint(long &tabLevel)
{
	OutputTabs(tabLevel);
	cout << "begin " << endl;
	tabLevel++;
	for (statementList::iterator it = m_statements.begin(); it != m_statements.end(); it++)
		it->get()->PrettyPrint(tabLevel);
	tabLevel--;
	OutputTabs(tabLevel);
	cout << "end " << endl;
}


// AssignmentStatement

AssignmentStatement::AssignmentStatement(tokenIt &it)
{
	Expect(tIdentifier, *it);
	m_variable = it->s;
	it++;
	Expect(tAssignment, *it++);
	m_expression = Expression::Parse(it);		
}

void AssignmentStatement::Execute(Context &context)
{
	context.SetValue(m_variable, m_expression->Evaluate(context));
}

void AssignmentStatement::PrettyPrint(long &tabLevel)
{
	OutputTabs(tabLevel);
	cout << m_variable << " := ";
	m_expression->PrettyPrint();
	cout << endl;
}
