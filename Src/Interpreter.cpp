// Interpreter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Program.h"

using namespace std;

void Usage()
{
	cout << "Interprets a C-- program." << endl << endl;
	cout << "interpret <option> <filename>" << endl;
	cout << "\t" << "option:" << endl;
	cout << "\t" << "/p pretty-print" << endl;
	cout << "\t" << "/e execute"  << endl;
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		Usage();
		return 1;
	}

	string opt = argv[1];
	bool bExecute = false;
	if (opt == "/e")
		bExecute = true;
	else if (opt != "/p")
	{
		Usage();
		return 1;
	}

	string programText;

	ifstream is(argv[2]);
	if (is)
	{
		while (!is.eof())
		{
			char c;
			is.get(c);
			programText += c;
		}
	}
	else
	{
		cout << "Could not open file " << argv[2] << endl;
		return 1;
	}
	

	try
	{
		Program p(programText);
		if (bExecute)
			p.Execute();
		else
			p.PrettyPrint();
	}
	catch (SyntaxError &e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unexpected error" << endl;
	}

	return 0;
}

