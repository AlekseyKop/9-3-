#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

class Student {
private:
	__int32 course;
	string group;
	string surname;
	string numberRecordBook;
	Task<StudentSession> marks;
public:
	//������� � ������� ��� �����
	__int32 getcourse()
	{
		return course;
	}

	__int32 setcourse(_int32 value)
	{
		return course = value;
	}

	string getgroup()
	{
		return group;
	}

	string setgroup(string value)
	{
		return group = value;
	}

	string getsurname()
	{
		return surname;
	}

	string setsurname(string value)
	{
		return surname = value;
	}
	string getnumberRecordBook()
	{
		return numberRecordBook;
	}

	string setnumberRecordBook(string value)
	{
		return numberRecordBook = value;
	}
	Task<StudentSession> getmarks()
	{
		return marks;
	}

	Task<StudentSession> setmarks(Task<StudentSession> value)
	{
		return marks = value;
	}
	//����������� �� ���������
	Student();

	//��������� ��������� Student
	Student ChangeStudent(Student &result);

	bool operator == (Student st);

	void StudentToFile(fstream *file);
};

Student StudentFromFile(fstream *file, bool &ok);

//������� ����� ��������� Student � �������
Student InputScreenStudent();

//������� ������ ��������� Student �� �������
void OutputScreenStudent(Student st);

//������� ��������� Student � ������
string ToString(Student st, __int32 i);

bool IsEqual(Student st1, Student st2);

//���������� ��������� Student �� ������
Student ReadFromStringSudent(ifstream& input);

/*����� ������� �������� �� ���������� ��������
type_search - ��� ������:
1 - �� ������
2 - �� �����
3 - �� ������ �������� ������
4 - �� �������*/
bool SearchElement(Student a, Student b, __int32 type_search);

/*���� �������� ������ � ����������� �� ���������� ����
type_search - ��� ������:
1 - �� ������ ������
2 - �� ������ �����
3 - �� ������ �������
4 - �� �������*/
Student InputChangeTypeSearchStudent(__int32 type_search);

/*��������� �������� �� ���������� ����
type_search - ��� ������:
1 - �� ������ ������
2 - �� ������ �����
3 - �� ������ �������
4 - �� �������*/
__int32 Sorte(Student a, Student b, __int32 type_search);
//������� ������������
double AverageScope(Student st);



