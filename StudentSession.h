﻿#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

class StudentSession {
public:
	//предмет
	string subject;
	//оценка
	__int32 mark;

	//Конструктор по умолчанию
	StudentSession();

	//Изменение структуры Student
	StudentSession ChangeStudentSession(StudentSession &result);

	//Перегруженный оператор присваивания для структуры Student
	StudentSession& operator = (StudentSession s);
	//загрузка результатов сессии из файла
	void StudentSessionToFile(fstream *file);
};
//получение результатов сессии из файла
StudentSession StudentSessionFromFile(fstream *file, bool &ok);

//Функция ввода структуры Student с консоли
StudentSession InputScreenStudentSession();

//Функция вывода структуры Student на консоль
void OutputScreenStudentSession(StudentSession st);

//Перевод структуры Student в строку
string ToString(StudentSession st, __int32 i);

bool IsEqual(StudentSession st1, StudentSession st2);

//считывание структуры Student из строки
StudentSession ReadFromString(ifstream& input);
