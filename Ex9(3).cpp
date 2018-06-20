/*
����������� ���������� ��������. ����������� ���������� ������� ��������� (�����������, ���������� ������ � ����������).
������������� ����� ����������� ������ � ������������ �� ��������� �������� (��������, ����, ������, ���������� � �.�.).
*/
#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include "HelpUtils.h"
#include "Operations.h"
#include "StudentSession.h"
#include "Student.h"
using namespace std;

void SaveStudentsToFile(string fileName, Task<Student> students) {
	fstream file;
	file.open(fileName, ios::out | ios::binary);
	if (!file.is_open())
		throw "���� �� ������� �������";
	__int32 i;
	for (i = 0; i < students.size(); ++i) {
		students.GetVector()[i].StudentToFile(&file);
	}
	file.close();
}

void SaveStudentMarksToFile(string fileName, Student student) {
	fstream file;
	file.open(fileName, ios::out | ios::binary);
	if (!file.is_open())
		throw "���� �� ������� �������";

	student.StudentToFile(&file);
	for (__int32 i = 0; i < student.getmarks().size(); ++i) {
		student.getmarks().GetVector()[i].StudentSessionToFile(&file);
	}
	file.close();
}

void LoadStudentsFromFile(string fileName, Task<Student> &students) {
	fstream file;
	file.open(fileName, ios::binary | ios::in);
	if (!file.is_open())
		return;

	bool ok;
	while (!file.eof())
	{
		Student st = StudentFromFile(&file, ok);
		if (ok)
			students.Add(st);
	}
	file.close();
}

void LoadStudentMarksFromFile(string fileName, Task<Student> &students) {
	fstream file;
	file.open(fileName, ios::binary | ios::in);
	if (!file.is_open())
		throw "���� �� ������� �������";

	Student st;
	bool ok;
	st = StudentFromFile(&file, ok);
	
	for (__int32 i = 0; i < students.size(); i++) {
		if (IsEqual(st, students.GetVector()[i]))
		{

			bool ok = true;
			while (!file.eof())
			{
				StudentSession st_ex = StudentSessionFromFile(&file, ok);
				if (ok)
				{
					vector<Student> temp;
					Task<StudentSession> markstemp;
					temp = students.GetVector();
					markstemp = temp[i].getmarks();
					markstemp.Add(st_ex);
					temp[i].setmarks(markstemp);
					
					students.SetVector(temp)[i];
				}
			}
		}
	}
	file.close();
}


void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Task<Student> students;
	LoadStudentsFromFile("Students.dat", students);
	for (__int32 i = 0; i < students.size(); i++)
	{
		LoadStudentMarksFromFile("Student" + to_string(i) + ".dat", students);
	}

	cout << "���� � ������ ������������: " << endl;
	cout << "1 - �������" << endl;
	cout << "2 - �����" << endl;
	cout << "0 - �����" << endl << endl;
	__int32 mode = InputNumber(0, 2, "��� �����: ");
	switch (mode)
	{
	case 1:
	{
		bool IsExist = false;
		string numbRecBook;
		__int32 i;
		do
		{
			numbRecBook = InputInformation("������� ����� �������(���� �� �������, ������ - 'DR'): ");
			if (numbRecBook == "DR")
			{
				exit(0);
				break;
			}
			for (i = 0; i < students.size(); i++)
			{
				if (students.GetVector()[i].getnumberRecordBook() == numbRecBook)
				{
					IsExist = true;
					break;
				}
			}
		} while (!IsExist);

		while (1)
		{
			cout << endl;
			cout << "1 - ���������� ���� ������" << endl;
			cout << "2 - ��������� ������� ������������" << endl;
			cout << "0 - �����" << endl;
			__int32 changemenu = InputNumber(0, 2, "��� �����: ");

			switch (changemenu)
			{
			case 1:
			{
				PrintHeadMarks();
				students.GetVector()[i].getmarks().OutputScreen(students.GetVector()[i].getmarks().GetVector(), OutputScreenStudentSession);
				break;
			}
			case 2:
			{
				double Average = AverageScope(students.GetVector()[i]);

				cout << "��� ������� ����: " << Average << endl;
				if (Average == 5)
					cout << "����� �����,� ������ �� �������! A �� ������ ������������." << endl;
				if ((Average > 4)&&(Average != 5))
					cout << "�� ������� ������,�� ����� � �����" << endl;
				if ((Average <= 4)&&(Average > 3.5))
					cout << "���� �������� ����� ���� ������!" << endl;
				if (Average <= 3.5)
					cout << "������ ���� ��� ���������" << endl;

				break;
			}
			default:
			{
				exit(0);
				break;
			}
			}
		}
		break;
	}
	case 2:
	{
		while (1)
		{
			cout << endl;
			cout << "1 - ��������� �����������" << endl;
			cout << "2 - �������� ������ � ��������" << endl;
			cout << "3 - ��������� ��������" << endl;
			cout << "4 - �������� ���������� ������" << endl;
			cout << "5 - ������� ������ ���������" << endl;
			cout << "0 - �����" << endl << endl;
			__int32 changemenu = InputNumber(0, 5, "��� �����: ");

			switch (changemenu)
			{
			case 1:
			{
				students.Add(InputScreenStudent());
				break;
			}
			case 2:
			{
				cout << "1 - �������� ������ ������ � ��������" << endl;
				cout << "2 - ���������� ������ ��������" << endl;
				cout << "3 - ��������� ������ ��������" << endl;
				cout << "4 - ������ ������ ��������" << endl;
				cout << "0 - �����" << endl << endl;
				__int32 a = InputNumber(0, 4, "��� �����: ");
				switch (a)
				{
				case 1:
				{
					cout << endl;
					PrintHeadStudents();
					students.OutputScreen(students.GetVector(), OutputScreenStudent);
					__int32 numb = InputNumber(0, students.size(), "������� ����� ������,������� ������ �������� (0 - ���� ����������): ");

					Student elem;

					if (numb != 0)
					{
						vector<Student> temp;
						temp = students.GetVector();
						temp[numb-1]=elem.ChangeStudent(students.GetVector()[numb - 1]);
						students.SetVector(temp)[numb - 1];
					}
					break;
				}
				case 2:
				{
					PrintHeadStudents();
					students.OutputScreen(students.GetVector(), OutputScreenStudent);
					__int32 numb = InputNumber(0, students.size(), "������� ����� ������,������� ������ �������� (0 - ���� ����������): ");

					if (numb != 0)
						do
						{
							/*temp = students.GetVector();
							markstemp = students.GetVector()[i].getmarks();
							markstemp.Add(st_ex);
							temp[i].setmarks(markstemp);*/
							vector<Student> temp;
							Task<StudentSession> markstemp;
							temp = students.GetVector();
							markstemp = temp[numb - 1].getmarks();
							markstemp.Add(InputScreenStudentSession());
							temp[numb - 1].setmarks(markstemp);
							students.SetVector(temp)[numb - 1];
						} while (InputNumber(0, 1, "\n������ �������� ������? (1 - ��, 0 - ���)\n��� �����: ") == 1);
						break;
				}
				case 3:
				{
					//����� ��������� ��� ������
					PrintHeadStudents();
					students.OutputScreen(students.GetVector(), OutputScreenStudent);
					__int32 numb = InputNumber(0, students.size(), "������� ����� ������,������� ������ �������� (0 - ���� ����������): ");

					//����� ������ ���������� �������� ��� ������
					if (numb != 0)
					{
						PrintHeadMarks();
						students.GetVector()[numb - 1].getmarks().OutputScreen(students.GetVector()[numb - 1].getmarks().GetVector(), OutputScreenStudentSession);
					}

					__int32 numb_mark = InputNumber(0, students.size(), "������� ����� ������ � �������,������� ������ �������� (0 - ���� ����������): ");
					StudentSession elem;

					if (numb_mark != 0)
					{
						vector<Student> temp;
						Task<StudentSession> markstemp;
						vector<StudentSession>vecmark;
						temp = students.GetVector();
						markstemp = temp[numb - 1].getmarks();
						vecmark = markstemp.GetVector();
						vecmark[numb_mark - 1] = elem.ChangeStudentSession(students.GetVector()[numb - 1].getmarks().GetVector()[numb_mark - 1]);
						markstemp.SetVector(vecmark);
						temp[numb - 1].setmarks(markstemp);
						//students.SetVector()[numb - 1] = elem.ChangeStudent(students.SetVector()[numb - 1]);
						students.SetVector(temp)[numb - 1];
						/*!*/			//students.GetVector()[numb - 1].marks.SetVector()[numb_mark - 1] = elem.ChangeStudentSession(students.GetVector()[numb - 1].marks.SetVector()[numb - 1]);
					}
					break;
				}
				case 4:
				{
					PrintHeadStudents();
					students.OutputScreen(students.GetVector(), OutputScreenStudent);
					__int32 numb = InputNumber(0, students.size(), "������� ����� ������ �� ���������,������� ������ �������� (0 - ���� ����������): ");

					if (numb != 0) {
						PrintHeadMarks();
						students.GetVector()[numb - 1].getmarks().OutputScreen(students.GetVector()[numb - 1].getmarks().GetVector(), OutputScreenStudentSession);
					}
					vector<Student> temp;
					Task<StudentSession> markstemp;
					temp = students.GetVector();
					markstemp = temp[numb - 1].getmarks();
					markstemp.Remove(InputNumber(0, students.GetVector()[numb - 1].getmarks().size(), "������� ����� ������ � �������,������� ������ ������� (0 - ���� ����������): "));
					temp[numb - 1].setmarks(markstemp);
					students.SetVector(temp)[numb - 1];
					/*!*/			//students.SetVector()[numb - 1].marks.Remove(InputNumber(0, students.GetVector()[numb - 1].marks.size(), "Enter the number of the mark to remove (0 - if you change your mind to delete): "));
					break;
				}
				default:
				{
					break;
				}
				}
				break;
			}
			case 3:
			{
				PrintHeadStudents();
				students.OutputScreen(students.GetVector(), OutputScreenStudent);
				students.Remove(InputNumber(0, students.size(), "������� ����� ������ �� ���������,������� ������ ������� (0 - ���� ����������): "));
				break;
			}
			case 4:
			{
				Student elem;
				vector<Student> subset;
				Student search_elem;
				__int32 numb = InputNumber(1, 4, "�������� ��� ������:\n 1 - �� ������\n 2 - �� �����\n 3 - �� ������ �������\n 4 - �� �������\n\n��� �����: ");
				search_elem = InputChangeTypeSearchStudent(numb);
				subset = students.LineSearch(search_elem, SearchElement, numb);
				if (subset.size() != 0)
				{
					for (__int32 i = 0; i<subset.size(); i++)
					{
						OutputScreenStudent(subset[i]);
						cout << endl;
						PrintHeadMarks();
						students.GetVector()[i].getmarks().OutputScreen(subset[i].getmarks().GetVector(), OutputScreenStudentSession);
						cout << endl;
					}
				}
				else
					cout << "������ �� �������" << endl;
				break;
			}
			case 5:
			{
				PrintHeadStudents();
				students.OutputScreen(students.GetVector(), OutputScreenStudent);
				break;
			}
			default:
			{
				SaveStudentsToFile("Students.dat", students);
				for (__int32 i = 0; i < students.size(); i++)
					SaveStudentMarksToFile("Student" + to_string(i) + ".dat", students.GetVector()[i]);
				exit(0);
				break;
			}
			}
		}
	default:
	{
		SaveStudentsToFile("Students.dat", students);
		for (__int32 i = 0; i < students.size(); i++)
			SaveStudentMarksToFile("Student" + to_string(i) + ".dat", students.GetVector()[i]);
		exit(0);
		break;
	}
	}
	}
}
