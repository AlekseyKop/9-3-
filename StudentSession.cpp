#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "StudentSession.h"


	//����������� �� ���������
	StudentSession::StudentSession()
	{
		string subject = "";
		__int32 mark = 2;
	}

	//��������� ��������� Student
	StudentSession StudentSession::ChangeStudentSession(StudentSession &result)
	{
		if (InputNumber(0, 1, "������ �� �� �������� ������� " + result.subject + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.subject = InputInformation("������� �������: ");
		if (InputNumber(0, 1, "������ �� �� �������� ������ " + to_string(result.mark) + " (0 - ���, 1 - ��)\n��� �����: ") == 1)
			result.mark = InputNumber(2,5,"������� ������: ");

		return result;
	}

	//������������� �������� ������������ ��� ��������� Student
	StudentSession& StudentSession::operator = (StudentSession s)
	{
		subject = s.subject;
		mark = s.mark;

		return (*this);
	}

	void StudentSession::StudentSessionToFile(fstream *file) {
		StrToBin(file, this->subject);
		file->write(reinterpret_cast<char*>(&(this->mark)), sizeof(this->mark));
	}

StudentSession StudentSessionFromFile(fstream *file, bool &ok) {
	StudentSession st_ex;
	st_ex.subject = StrFromBin(file);
	ok = (bool)file->read(reinterpret_cast<char*>(&(st_ex.mark)), sizeof(st_ex.mark));

	return st_ex;
}

//������� ����� ��������� Student � �������
StudentSession InputScreenStudentSession()
{
	StudentSession s;

	s.subject = InputInformation("������� �������� ����������: ");
	s.mark = InputNumber(2,5,"������� ������ (2-5): ");

	return s;
}

//������� ������ ��������� Student �� �������
void OutputScreenStudentSession(StudentSession st)
{
	
	cout << setw(1) << left << "|" << setw(20) << left << st.subject << "|" << setw(36) << left << st.mark << "|";
}
//cout << setw(1) << "|" << setw(10) << left << st.course << "|" << setw(10) << left << st.group << "|" << setw(20) << left << st.surname << "|" << setw(25) << left << st.numberRecordBook << "|";
//������� ��������� Student � ������
string ToString(StudentSession st, __int32 i)
{
	string result = "������ - " + to_string(i) + "\n" + "�������: " + st.subject + "\n" + "������: " + to_string(st.mark) + "\n";
	return result;
}

bool IsEqual(StudentSession st1, StudentSession st2)
{
	return 
		((st1.subject == st2.subject) &&
		(st1.mark == st2.mark));
}

//���������� ��������� Student �� ������
StudentSession ReadFromString(ifstream& input)
{
	StudentSession result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����������: ";
			result.subject = s.substr(wrd.length(), s.length());
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "������: ";
			result.mark = atoi(s.substr(wrd.length(), s.length()).c_str());
		}
	}
	catch (...)
	{
		cout << "������ ������ � ����" << endl;
	}
	return result;
}
