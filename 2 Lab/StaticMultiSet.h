#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

template <class T>
class StaticMultiset
{
	std::vector<T> data; //храним данные
	T max; // значение максимума
	T min; // значение минимума
	float avg; // среднее арифметическое
	std::vector<float> countUnderRequest; // только запросы кол-ва чисел меньше, чем для запрашиваемого (кэш)
	std::vector<float> countAboveRequest; // только запросы кол-ва чисел больше, чем для запрашиваемого (кэш)
	std::map<float, int> countUnderAnsw; // ответы для соответствующих запросов (кэш)
	std::map<float, int> countAboveAnsw;
public:
	StaticMultiset(); // конструтор по умолчанию
	void AddNum( T ); // добавление нового числа
	T GetMax() const; // максимум среди имеющихся чисел
	T GetMin() const; // минимум среди имеющихся чисел
	float GetAvg() const; // среднее фрифметическое значение имеющихся чисел
	int GetCountUnder(float); // кол-во чисел меньше, чем данное число
	int GetCountAbove(float); // кол-во чисел больше, чем данное число
};

template <class T>
StaticMultiset<T>::StaticMultiset() // конструктор
{}

template <class T>
void StaticMultiset<T>::AddNum( T num ) // добавление нового элемента
{	
	data.push_back(num); // добавляем новый элемент в конец вектора
	if (data.size() == 1) // если элемент первый, то присваиваем его значение максимуму, минимуму и среднему значению
	{
		min = data.front();
		max = data.back();
		avg = data.front();
	}
	else
	{
		if (min > data.back()) // если не первый элемент, то проверяем не является ли новый элемент минимумом
			min = data.back();
		if (max < data.back()) // или максимумом
			max = data.back();
		avg = (float)((avg * (data.size() - 1) + data.back()) / data.size()); // пересчитываем среднее значение
		countAboveAnsw.clear(); //очищаем кэш запросов
		countAboveRequest.clear();
		countUnderAnsw.clear();
		countUnderRequest.clear();
	}
}

template <class T>
T StaticMultiset<T>::GetMax() const // возвращаем значение максимального элемента
{
	return max;
}

template <class T>
T StaticMultiset<T>::GetMin() const // возвращаем значение минимального элемента
{
	return min;
}

template<class T>
float StaticMultiset<T>::GetAvg() const // возвращаем среднее значение
{
	return avg;
}

template <class T>
int StaticMultiset<T>::GetCountAbove(float threshold) // находим кол-во чисел больше, чем данное
{
	auto request = std::find(countAboveRequest.begin(), countAboveRequest.end(), threshold); // проверяем был ли уже такой запрос
	if (request == countAboveRequest.end()) // если не был, то выполняем его и заносим в кэш
	{
		int ans = 0;
		countAboveRequest.push_back(threshold); // добавляем запрос в кэш
		for (auto i : data) // перебираем все элементы в цикле и при нахождении элемента больше, чем данное увеличиваем счетчик
		{
			if (i > threshold)
				ans++;
		}
		countAboveAnsw.insert(std::make_pair(threshold, ans)); // добавляем ответ на запрос в кэш
		return ans;
	}
	else
		return countAboveAnsw[*request]; // если был, то берем ответ из кэша
}

template <class T>
int StaticMultiset<T>::GetCountUnder(float threshold) // находим кол-во чисел меньше, чем данное
{
	auto request = std::find(countUnderRequest.begin(), countUnderRequest.end(), threshold); // проверяем был ли такой запрос
	if (request == countUnderRequest.end()) // если нет, то заносим его в кэш
	{
		int ans = 0;
		countUnderRequest.push_back(threshold); //добавляем запрос в кэш
		for (auto i : data) // перебираем все элементы в цикле и при нахождении элемента больше, чем данное увеличиваем счетчик
		{
			if (i < threshold)
				ans++;
		}
		countUnderAnsw.insert(std::make_pair(threshold, ans)); // добавляем ответ на запрос в кэш
		return ans;
	}
	else
		return countUnderAnsw[*request]; // если был, то берем данные из кэша
}
