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
	//геттеры и сеттеры для полей
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
	//Конструктор по умолчанию
	Student();

	//Изменение структуры Student
	Student ChangeStudent(Student &result);

	bool operator == (Student st);

	void StudentToFile(fstream *file);
};

Student StudentFromFile(fstream *file, bool &ok);

//Функция ввода структуры Student с консоли
Student InputScreenStudent();

//Функция вывода структуры Student на консоль
void OutputScreenStudent(Student st);

//Перевод структуры Student в строку
string ToString(Student st, __int32 i);

bool IsEqual(Student st1, Student st2);

//считывание структуры Student из строки
Student ReadFromStringSudent(ifstream& input);

/*Поиск равного элемента по выбранному критерию
type_search - тип поиска:
1 - по группе
2 - по курсу
3 - по номеру зачетной книжки
4 - по фамилии*/
bool SearchElement(Student a, Student b, __int32 type_search);

/*Ввод критерия поиска в зависимости от выбранного типа
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
Student InputChangeTypeSearchStudent(__int32 type_search);

/*Сравнение структур по выбранного полю
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
__int32 Sorte(Student a, Student b, __int32 type_search);
//средняя успеваемость
double AverageScope(Student st);



