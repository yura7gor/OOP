#include "Exception.h"
#include <iostream>
namespace lol
{
	Exception_IO::Exception_IO(std::string &exception_name) :
		errorName(exception_name) {}
	std::string Exception_IO::what()
	{
		std::cerr << "\n" << errorName << "\n";
		system("pause");
		return errorName;
		
	}
	Exception_Format_File::Exception_Format_File(std::string &exception_name) :
		errorName(exception_name) {}
	std::string Exception_Format_File::what()
	{
		std::cerr << "\n" << errorName << "\n";
		system("pause");
		return errorName;
	}
	Exception_Section_Parametr::Exception_Section_Parametr(std::string &exception_name) :
		errorName(exception_name) {}
	std::string Exception_Section_Parametr::what()
	{
		std::cerr << "\n" << errorName << "\n";
		system("pause");
		return errorName;
	}
	Exception_Type_Data::Exception_Type_Data(std::string &exception_name) :
		errorName(exception_name) {}
	std::string Exception_Type_Data::what()
	{
		std::cerr << "\n" << errorName << "\n";
		system("pause");
		return errorName;
	}
}
