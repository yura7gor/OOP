 #include "Iniparser.h"
#include <iostream>
#include <vector>

namespace lol
{

	IniParser::IniParser() : //конструктор дефолтный
		file("default_file_name") {}

	IniParser::~IniParser() // деструктор класса
	{
		dataFromFile.clear();
		input.close();
		file = "";
	}

	bool IniParser::isHaveSection(std::string &sectionName) // проверка на наличие секции
	{
		return dataFromFile.find(sectionName) != dataFromFile.end();
	}

	bool IniParser::IsHaveParam(std::string &sectionName, std::string &paramName) // проверка на наличие параметра в секции
	{
		if (!isHaveSection(sectionName))
			return false;
		return dataFromFile.find(sectionName)->second.find(paramName) != dataFromFile.find(sectionName)->second.end();
	}

	int IniParser::GetValueInt(std::string &sectionName, std::string &paramName)
	{
		if (!IsHaveParam(sectionName, paramName))
			throw Exception_Section_Parametr(std::string("ERROR! This ini file haven't this Section or Parametr"));
		// кидаем исключение, т.к. такой секции или параметра нет
		int n = std::stoi(dataFromFile[sectionName][paramName]); // переводим строку в число
		return n;
	}

	std::string IniParser::GetValueString(std::string &sectionName, std::string &paramName)
	{
		if (!IsHaveParam(sectionName, paramName))
			throw Exception_Section_Parametr(std::string("ERROR! This ini file haven't this Section or Parametr"));
		// кидаем исключение, т.к. такой секции или параметра нет
		return dataFromFile[sectionName][paramName]; //просто возвращаем строку
	}

	double IniParser::GetValueDouble(std::string &sectionName, std::string &paramName)
	{
		if (!IsHaveParam(sectionName, paramName))
			throw Exception_Section_Parametr(std::string("ERROR! This ini file haven't this Section or Parametr"));
		// кидаем исключение, т.к. такой секции или параметра нет
		double n = std::atof(dataFromFile[sectionName][paramName].c_str()); // переводим строку в вещ. число
		return n;
	}

	void IniParser::parse(std::vector<std::string> &m)
	{
		std::string sectionname = "";
		std::string value = "";
		std::string name = "";
		bool sthFind = false;
		for (int i = 0; i < m.size(); i++)
		{
			if (m[i].find("[") != -1 && m[i].find("]")) // ищем название секции, заключенное в квадратные скобки
			{
				sectionname = m[i].substr(m[i].find("[") + 1, m[i].find("]") - 1);
				sthFind = true;
			}
			if (m[i].find("=") != -1 && !sthFind) // ищем пару значение-имя
			{
				name = m[i].substr(0, m[i].find("="));
				value = m[i].substr(m[i].find("=") + 1, m[i].size() - 1);
				if (value != "" && name != "")
					sthFind = true;
			}

			if (!sthFind) // если ничего не нашли - формируем исключение
				throw Exception_Format_File(std::string("ERROR! Format of input file isn't correct!"));

			if (sectionname != "" && value != "" && name != "") // если найдены секци¤, имя и значение - добавл¤ем в структуру
			{
				dataFromFile.insert(std::make_pair(sectionname, std::map<std::string, std::string>()));
				dataFromFile[sectionname].insert(make_pair(name, value));
				name = value = "";
				
			}
			sthFind = false;
		}
	}

	void IniParser::Initialize(const char * fileName) throw (Exception_IO)
	{
		input.open(fileName); // открываем поток ввода из файла
		if (input.is_open() == false) //проверка на открытие файла
			throw Exception_IO(std::string("ERROR! Name of file isn't correct!"));
		file = std::string(fileName);
		std::vector<std::string> mas;
		std::string str;
		int i;
		while (!input.eof())
		{
			getline(input, str);
			i = str.find(";"); // удал¤ем комментарии 
			if (i != -1)
				str = str.substr(0, i);
			i = str.find(" "); // удал¤ем лишние пробелы
			while (i != -1)
			{
				str.erase(i, 1);
				i = str.find(" ");
			}
			i = str.find("\t"); // удал¤ем табул¤цию
			while (i != -1)
			{
				str.erase(i, 1);
				i = str.find("\t");
			}
			if (str != "") // если строка не пуста¤, тогда добавл¤ем ее в вектор
				mas.push_back(str);
		}
		parse(mas);	// парсим получившийс¤ вектор
	}
}
