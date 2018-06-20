#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cstring>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;

template <class Type>
//��������������� ������� ��� ����� ����� � ��������� ���������
Type InputNumber(Type min, Type max, string message)
{
	Type n;
	do
	{
		cout << message;
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cin.clear();  // ��������������� ����� ���� �� � ��������� ���������
			cin.sync();   // ������� ����� �� ��������� ��������
			cout << message;
			cin.ignore(100, '\n');
		} 
	} while ((n < min) || (n > max));
	return n;
}

//���� ��������� ����������
string InputInformation(string message);

//���������� ������ �� ��������� �����
string StrFromBin(fstream *f);

//������ ������ � �������� ����
void StrToBin(fstream *f, string str);

//����� � �������

void PrintHeadStudents();

void PrintHeadMarks();