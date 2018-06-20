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

//���� ��������� ����������
string InputInformation(string message)
{
	string a;
	cout << message;
	getline(cin,a);
	while(a == "")
	{
		cout << "������!!!!" << endl;
		getline(cin, a);
	}
	return a;
}

//���������� ������ �� ��������� �����
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

//������ ������ � �������� ����
void StrToBin(fstream *f, string str) {
	_int32 len = str.length() + 1;
	f->write(reinterpret_cast<char*>(&len), sizeof(len));
	f->write(str.c_str(), len);
}



void PrintHeadStudents()
{
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(10) << left << "������" << "|" << setw(10) << left << "����" << "|" << setw(10) << left << "������" << "|" << setw(20) << left << "�������" << "|" << setw(25) << left << "����� �������" << "|" <<endl;
	cout << "---------------------------------------------------------------------------------" << endl;
}

void PrintHeadMarks()
{
	cout << "----------------------------------------------------------------------" <<endl;
	cout << setw(1) << left << "|" << setw(10) << left <<"������" << "|" << setw(20) << left << "����������" << "|" << setw(36) << left << "������" << "|" << endl;
	cout << "----------------------------------------------------------------------" <<endl;
}