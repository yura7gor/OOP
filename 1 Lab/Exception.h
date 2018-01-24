#pragma once

#include <exception>
#include <string>
namespace lol
{
	class Exception_IO : std::exception // исключение ввода-вывода
		//если не открылся файл или имя файла некорректно
	{
		std::string errorName;
	public:
		Exception_IO(std::string &);
		std::string Exception_IO::what();
	};
	class Exception_Format_File : std::exception // исключение формата файла
		//файл имеет неверный формат, например имя секции не заключено в квадратные скобки с двух сторон
	{
		std::string errorName;
	public:
		Exception_Format_File(std::string &);
		std::string Exception_Format_File::what();
	};
	class Exception_Section_Parametr : std::exception // исключение параметра-секции
		//требуемого парамера или секции нет в структуре
	{
		std::string errorName;
	public:
		Exception_Section_Parametr(std::string &);
		std::string Exception_Section_Parametr::what();
	};

	class Exception_Type_Data : std::exception // исключение типа данных
													  //тип, который пытаются извлечь, не является int, double, string
	{
		std::string errorName;
	public:
		Exception_Type_Data(std::string &);
		std::string Exception_Type_Data::what();
	};
}
