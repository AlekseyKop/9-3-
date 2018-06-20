#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "HelpUtils.h"
using namespace std;

template <class Type>
class Task {
	
private:
	vector<Type> vect; //контейнер

	//Сортировка по заданному критерию, Compare - функция, сравнивающая два элемента  
	void Sort(__int32 n, __int32 type_search, int(*Compare)(Type, Type, int))
	{
		__int32 i, j, step;
		Type tmp;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				tmp = vect[i];
				for (j = i; j >= step; j -= step)
				{
					if ((Compare(tmp, vect[j - step], type_search) == -1))
						vect[j] = vect[j - step];
					else
						break;
				}
				vect[j] = tmp;
			}

	}
	//Бинарный поиск, Compare - функция, сравнивающая два элемента 
	__int32 BinarySearchElement(__int32 left, __int32 right, __int32 type_search, Type d, int(*Compare)(Type, Type, int))
	{
		__int32 mid = 0;
		while (1)
		{
			mid = (left + right) / 2;

			if (Compare(d, vect[mid], type_search) == -1)
				right = mid - 1;				
			else if (Compare(d, vect[mid], type_search) == 1) 
				left = mid + 1;					
			else                      
				return mid;          

			if (left > right)
				return -1;
		}
	}
public:
	//получить значение вектора
	vector<Type> GetVector()
	{
		return vect;
	}
	//задать значение вектора
	vector<Type> SetVector(vector<Type> value)
	{
		vect = value;
		return vect;
	}
	//Удаление элемента
	void Remove(__int32 numb)
	{
		if (numb != 0)
			vect.erase(vect.begin() + numb - 1);
	}

	//Добавление элемента
	void Add(Type &elem)
	{
		for (__int32 i = 0; i < vect.size(); i++)
		{
			if (IsEqual(elem, vect[i]))
			{
				if (InputNumber(0, 1, "\nХотите ли вы заменить запись (0 - нет, 1 - да)\nВаш выбор: ") == 1)
				{
					vect[i] = elem;
					cout << "Запись заменена";
					return;
				}
				else
				{
					cout << "Запись не заменена";
					return;
				}
			}
		}
		
		vect.push_back(elem);
	}

	//Размер вектора
	__int32 size()
	{
		return vect.size();
	}

	//Проверка на пустоту
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	//Вывод в файл, f - функция, записывающая одну структуру в файл  
	void OutputFile(vector<Type> items, string(*f)(Type, int))
	{
		string newfname = InputFileName();
		ofstream fout(newfname);
		if (fout)
		{
			vector<Type>::const_iterator pos;
			__int32 count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos, count) << ' ';
				count++;
			}
			cout << endl << "Файл заполнен" << endl;
			fout.close();
		}
		else
		{
			cout << "Файл не заполнен" << endl;
		}
	}

	//Вывод на экран, f - функция, которая выводит одну структуру на экран  
	void OutputScreen(vector<Type> items, void(*f) (Type))
	{
		vector<Type>::const_iterator pos;
		__int32 count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(10) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "Пусто" << endl;
	}

	//Ввод из файла, f - функция, которая считывает одну структуру из файла 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "Невозможно открыть файл" << endl;
			return false;
		}
		else
		{
			while (!input.eof())
			{
				vect.push_back(f(input));
			}
			vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	//Ввод с экрана, f - функция, которая вводит одну структуру с консоли
	void ReadFromScreen(Type(*f)())
	{
		__int32 n;
		Type elem;
		do
		{
			Add(f());
			n = InputNumber(0, 1, "\nХотите ли добавить запись? (1 - Да, 0 - Нет)\nВаш выбор: ");
		} while (n != 0);
	}

	//Линейный поиск, Equal - функция, проверяющая равенство эл-та с текущим по type_search
	vector<Type> LineSearch(Type search_elem, bool(*Equal)(Type, Type, int), __int32 type_search)
	{
		vector<Type> NewVect;
		for (auto iter = vect.begin(); iter != vect.end(); iter++)
		{
			if (Equal(search_elem, *iter, type_search))
				NewVect.push_back(*iter);
		}

		return NewVect;
	}

	//Бинарный поиск, Compare - функция, сравнивающая два элемента по type_search, Equal - функция, проверяющая равенство искомого эл-та с текущим по type_search
	vector<Type> BinarySearch(__int32 type_search, Type find_element, int(*Compare)(Type, Type, int), bool(*Equal)(Type, Type, int))
	{
		vector<Type> NewVect;
		Sort(vect.size(), type_search, Compare);
		__int32 left = 0;
		__int32 right = vect.size();
		__int32 index;
		if ((index = BinarySearchElement(left, right - 1, type_search, find_element, Compare)) != -1)
		{
			NewVect.push_back(vect[index]);
			__int32 first_index = index;
			while ((++index<right) && Equal(vect[index], find_element, type_search))
				NewVect.push_back(vect[index]);
			while ((--first_index >= 0) && Equal(vect[first_index], find_element, type_search))
				NewVect.push_back(vect[first_index]);
		}
		return NewVect;
	}
};
