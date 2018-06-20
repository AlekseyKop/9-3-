#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

class StudentSession {
public:
	string subject;
	__int32 mark;

	//����������� �� ���������
	StudentSession();

	//��������� ��������� Student
	StudentSession ChangeStudentSession(StudentSession &result);

	//������������� �������� ������������ ��� ��������� Student
	StudentSession& operator = (StudentSession s);

	void StudentSessionToFile(fstream *file);
};

StudentSession StudentSessionFromFile(fstream *file, bool &ok);

//������� ����� ��������� Student � �������
StudentSession InputScreenStudentSession();

//������� ������ ��������� Student �� �������
void OutputScreenStudentSession(StudentSession st);

//������� ��������� Student � ������
string ToString(StudentSession st, __int32 i);

bool IsEqual(StudentSession st1, StudentSession st2);

//���������� ��������� Student �� ������
StudentSession ReadFromString(ifstream& input);
