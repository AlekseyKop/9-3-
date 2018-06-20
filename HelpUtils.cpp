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
#include "HelpUtils.h"
using namespace std;

//Ввод текстовой информации
string InputInformation(string message)
{
	string a;
	cout << message;
	getline(cin,a);
	while(a == "")
	{
		cout << "Ошибка!!!!" << endl;
		getline(cin, a);
	}
	return a;
}

//считывание строки из бинарного файла
string StrFromBin(fstream *f) {
	string result;
	_int32 len;
	if (!f->read(reinterpret_cast<char*>(&len), sizeof(len))) {
		return "";
	}
	char *buf = new char[len];
	if (!f->read(buf, len)) {
		return "";
	}
	result = buf;
	delete[] buf;
	return result;
}

//запись строки в бинарный файл
void StrToBin(fstream *f, string str) {
	_int32 len = str.length() + 1;
	f->write(reinterpret_cast<char*>(&len), sizeof(len));
	f->write(str.c_str(), len);
}



void PrintHeadStudents()
{
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(10) << left << "Запись" << "|" << setw(10) << left << "Курс" << "|" << setw(10) << left << "Группа" << "|" << setw(20) << left << "Фамилия" << "|" << setw(25) << left << "Номер зачётки" << "|" <<endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}

void PrintHeadMarks()
{
	cout << "----------------------------------------------------------------------" <<endl;
	cout << setw(1) << left << "|" << setw(10) << left <<"Запись" << "|" << setw(20) << left << "Дисциплина" << "|" << setw(36) << left << "Оценка" << "|" << endl;
	cout << "----------------------------------------------------------------------" <<endl;
}