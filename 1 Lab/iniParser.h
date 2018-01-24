#pragma once

#include <string>
#include <map>
#include <fstream>
#include <vector>
#include "Exception.h"
#include <sstream>

namespace lol
{
	class IniParser
	{
		std::string file; // имя файла
		std::ifstream input; // поток файлового ввода
		std::map<std::string, std::map<std::string, std::string>> dataFromFile; // структура для хранения данных
		void parse(std::vector<std::string> &); // функция парсинга
	public:
		IniParser();
		~IniParser();
		bool isHaveSection(std::string &); // проверка на наличие секции
		void Initialize(const char*) throw (Exception_IO); // инициализация
		bool IsHaveParam(std::string &, std::string &); // проверка на наличие параметра в секции
		int GetValueInt(std::string &, std::string &);
		double GetValueDouble(std::string &, std::string &);
		std::string GetValueString(std::string &, std::string &);
		template <class T>
		T getValue(std::string &, std::string &);
	};


	template <class T>
	T lol::IniParser::getValue(std::string &sectionName, std::string &paramName) 
	{
		if (!isHaveSection(sectionName) || !IsHaveParam(sectionName, paramName)) //проверяем есть ли такая секция и параметр
			throw Exception_Section_Parametr(string("File have not this section or parametr"));
		T val; //здесь будет хранить ответ на запрос
		std::istringstream strstream(this->dataFromFile[sectionName][paramName]); // инициализируем строковый поток
		if (typeid(T) == typeid(double) || typeid(T) == typeid(std::string) || typeid(T) == typeid(int)) 
		{ // если тип, который пытаются извлечь не является int или double, или string, то кидаем эксепшн
			strstream >> val; // достаем из потока 
			return val;
		}
		else
			throw Exception_Type_Data(string("Can't work with this type"));
	}

}
