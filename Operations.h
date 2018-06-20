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
	vector<Type> vect; //���������

	//���������� �� ��������� ��������, Compare - �������, ������������ ��� ��������  
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
	//�������� �����, Compare - �������, ������������ ��� �������� 
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
	//�������� �������� �������
	vector<Type> GetVector()
	{
		return vect;
	}
	//������ �������� �������
	vector<Type> SetVector(vector<Type> value)
	{
		vect = value;
		return vect;
	}
	//�������� ��������
	void Remove(__int32 numb)
	{
		if (numb != 0)
			vect.erase(vect.begin() + numb - 1);
	}

	//���������� ��������
	void Add(Type &elem)
	{
		for (__int32 i = 0; i < vect.size(); i++)
		{
			if (IsEqual(elem, vect[i]))
			{
				if (InputNumber(0, 1, "\n������ �� �� �������� ������ (0 - ���, 1 - ��)\n��� �����: ") == 1)
				{
					vect[i] = elem;
					cout << "������ ��������";
					return;
				}
				else
				{
					cout << "������ �� ��������";
					return;
				}
			}
		}
		
		vect.push_back(elem);
	}

	//������ �������
	__int32 size()
	{
		return vect.size();
	}

	//�������� �� �������
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	//����� � ����, f - �������, ������������ ���� ��������� � ����  
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
			cout << endl << "���� ��������" << endl;
			fout.close();
		}
		else
		{
			cout << "���� �� ��������" << endl;
		}
	}

	//����� �� �����, f - �������, ������� ������� ���� ��������� �� �����  
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
			cout << "�����" << endl;
	}

	//���� �� �����, f - �������, ������� ��������� ���� ��������� �� ����� 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "���������� ������� ����" << endl;
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

	//���� � ������, f - �������, ������� ������ ���� ��������� � �������
	void ReadFromScreen(Type(*f)())
	{
		__int32 n;
		Type elem;
		do
		{
			Add(f());
			n = InputNumber(0, 1, "\n������ �� �������� ������? (1 - ��, 0 - ���)\n��� �����: ");
		} while (n != 0);
	}

	//�������� �����, Equal - �������, ����������� ��������� ��-�� � ������� �� type_search
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

	//�������� �����, Compare - �������, ������������ ��� �������� �� type_search, Equal - �������, ����������� ��������� �������� ��-�� � ������� �� type_search
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
