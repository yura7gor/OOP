#include "Iniparser.h"
#include <string>
#include <iostream>

using namespace std;

void main()
{
	try
	{
		lol::IniParser parser;
		parser.Initialize("input.txt");

		cout << "\n" << parser.GetValueDouble(string("DEMODS"), string("BufferLenSeconds")) << "\n";
		//cout << "\n" << parser.GetValueString(string("NCMD"), string("Yura")) << "\n"; 
		// вызовет исключение, т.к. параметра Yura в структуре нет
		cout << "\n" << parser.GetValueString(string("DEMODS"), string("DefaultDemod")) << "\n";
		cout << "\n" << parser.GetValueInt(string("DEMODS"), string("StartDataPort")) << "\n";
		cout << "\n" << parser.getValue<string>(string("DEMODS"), string("StartDataPort")) << "\n";
		double x = parser.getValue<char>(string("DEMODS"), string("StartDataPort"));
		cout << "\n" << x << "\n";
		system("pause");
	}
	catch (lol::Exception_IO &e)
	{
		e.what();
	}
	catch (lol::Exception_Format_File &e)
	{
		e.what();
	}
	catch (lol::Exception_Section_Parametr &e)
	{
		e.what();
	}
	catch (lol::Exception_Type_Data &e)
	{
		e.what();
	}
}
