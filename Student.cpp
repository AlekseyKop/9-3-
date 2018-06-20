#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "Operations.h"
#include "StudentSession.h"
#include "Student.h"

	//����������� �� ���������
	Student::Student()
	{
		__int32 course = 1;
		string group = "";
		string surname = "";
		string numberRecordBook = "";
		Task<StudentSession> marks;
	}

	//��������� ��������� Student
	Student Student::ChangeStudent(Student &result)
	{
		if (InputNumber(0, 1, "������ �������� ���� " + to_string(result.course) + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.course = InputNumber(1, 6, "������� ����� ����: ");
		if (InputNumber(0, 1, "������ �������� ������ " + result.group + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.group = InputInformation("������� ����� ������: ");
		if (InputNumber(0, 1, "������ �������� ������� " + result.surname + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.surname = InputInformation("������� ����� �������: ");
		if (InputNumber(0, 1, "������ �������� ����� ������� " + result.numberRecordBook + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.numberRecordBook = InputInformation("������� ����� �����: ");

		return result;
	}

	bool Student::operator == (Student st)
	{
		return ((course == st.getcourse()) &&
			(group == st.getgroup()) &&
			(surname == st.getsurname()) &&
			(numberRecordBook == st.getnumberRecordBook()));
	}

	void Student::StudentToFile(fstream *file) {
		file->write(reinterpret_cast<char*>(&(this->course)), sizeof(this->course));
		StrToBin(file, this->group);
		StrToBin(file, this->surname);
		StrToBin(file, this->numberRecordBook);
	}

Student StudentFromFile(fstream *file, bool &ok) {
	Student st;
	__int32 temp;
	ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
	if (ok)
	{
		st.setcourse(temp);
		st.setgroup(StrFromBin(file));
		st.setsurname(StrFromBin(file));
		st.setnumberRecordBook(StrFromBin(file));
	}

	return st;
}

//������� ����� ��������� Student � �������
Student InputScreenStudent()
{
	Student st;

	st.setcourse(InputNumber(1, 6, "������� ���� (1-6): "));
	st.setgroup(InputInformation("������� ������: "));
	st.setsurname(InputInformation("������� �������: "));
	st.setnumberRecordBook(InputInformation("������� ����� �������: "));

	return st;
}

//������� ������ ��������� Student �� �������
void OutputScreenStudent(Student st)
{
	cout << setw(1) << "|" << setw(10) << left << st.getcourse() << "|" << setw(10) << left << st.getgroup() << "|" << setw(20) << left << st.getsurname() << "|" << setw(25) << left << st.getnumberRecordBook() << "|";
}

//������� ��������� Student � ������
string ToString(Student st, __int32 i)
{
	string result = "������ - " + to_string(i) + "\n" + "����: " + to_string(st.getcourse()) + "\n" + "������: " + st.getgroup() + "\n" + "�������: " + st.getsurname() + "\n" + "����� �������: " + st.getnumberRecordBook() + "\n";
	return result;
}

bool IsEqual(Student st1, Student st2)
{
	return ((st1.getcourse() == st2.getcourse()) &&
		(st1.getgroup() == st2.getgroup()) &&
		(st1.getsurname() == st2.getsurname()) &&
		(st1.getnumberRecordBook() == st2.getnumberRecordBook()));
}

//���������� ��������� Student �� ������
Student ReadFromStringSudent(ifstream& input)
{
	Student result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s);
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����: ";
			result.setcourse(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "������: ";
			result.setgroup(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "�������: ";
			result.setsurname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� �������: ";
			result.setnumberRecordBook(s.substr(wrd.length(), s.length()));
		}
	}
	catch (...)
	{
		cout << "������ ������ �����!" << endl;
	}
	return result;
}

/*����� ������� �������� �� ���������� ��������
type_search - ��� ������:
1 - �� ������
2 - �� �����
3 - �� ������ �������� ������
4 - �� �������*/
bool SearchElement(Student a, Student b, __int32 type_search)
{
	switch (type_search)
	{
	case 1:
		return (a.getgroup() == b.getgroup());
	case 2:
		return (a.getcourse() == b.getcourse());
	case 3:
		return (a.getnumberRecordBook() == b.getnumberRecordBook());
	case 4:
		return (a.getsurname() == b.getsurname());
	default:
		return false;
	}
}

/*���� �������� ������ � ����������� �� ���������� ����
type_search - ��� ������:
1 - �� ������ ������
2 - �� ������ �����
3 - �� ������ �������
4 - �� �������*/
Student InputChangeTypeSearchStudent(__int32 type_search)
{
	Student result;
	switch (type_search)
	{
	case 1:
		result.setgroup(InputInformation("������� ������: "));
		return result;
	case 2:
		result.setcourse(InputNumber(1, 6, "������� ����: "));
		return result;
	case 3:
		result.setnumberRecordBook(InputInformation("������� ����� �������: "));
		return result;
	case 4:
		result.setsurname(InputInformation("������� �������: "));
		return result;
	default:
		return result;
	}
}

/*��������� �������� �� ���������� ����
type_search - ��� ������:
1 - �� ������ ������
2 - �� ������ �����
3 - �� ������ �������
4 - �� �������*/
__int32 Sorte(Student a, Student b, __int32 type_search)
{
	switch (type_search)
	{
	case 1:
		if (a.getgroup() > b.getgroup()) return 1;
		else if (a.getgroup() < b.getgroup()) return -1;
		else return 0;
	case 2:
		if (a.getcourse() > b.getcourse()) return 1;
		else if (a.getcourse() < b.getcourse()) return -1;
		else return 0;
	case 3:
		if (a.getnumberRecordBook() > b.getnumberRecordBook()) return 1;
		else if (a.getnumberRecordBook() < b.getnumberRecordBook()) return -1;
		else return 0;
	case 4:
		if (a.getsurname() > b.getsurname()) return 1;
		else if (a.getsurname() < b.getsurname()) return -1;
		else return 0;
	default:
		return -2;
	}
}

double AverageScope(Student st)
{
	double res = 0;
	__int32 count = 0;
	for (__int32 i = 0; i < st.getmarks().size(); i++)
	{
		res += st.getmarks().GetVector()[i].mark;
		count++;
	}
	if (count == 0) return 0;
	else
		return res / count;
}



