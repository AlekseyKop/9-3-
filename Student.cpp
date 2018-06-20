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

	//Конструктор по умолчанию
	Student::Student()
	{
		__int32 course = 1;
		string group = "";
		string surname = "";
		string numberRecordBook = "";
		Task<StudentSession> marks;
	}

	//Изменение структуры Student
	Student Student::ChangeStudent(Student &result)
	{
		if (InputNumber(0, 1, "Хотите поменять курс " + to_string(result.course) + " (0 - нет, 1 - да)\nВаш выбор: ") == 1)
		{
			result.course = InputNumber(1, 6, "Введите новый курс: ");
		}
		if (InputNumber(0, 1, "Хотите поменять группу " + result.group + " (0 - нет, 1 - да)\nВаш выбор: ") == 1)
		{
			result.group = InputInformation("Введите новую группу: ");
		}
		if (InputNumber(0, 1, "Хотите поменять фамилию " + result.surname + " (0 - нет, 1 - да)\nВаш выбор: ") == 1)
		{
			result.surname = InputInformation("Введите новую фамилию: ");
		}
		if (InputNumber(0, 1, "Хотите поменять номер зачётки " + result.numberRecordBook + " (0 - нет, 1 - да)\nВаш выбор: ") == 1)
		{
			result.numberRecordBook = InputInformation("Введите новый номер: ");
		}

		return result;
	}

	bool Student::operator == (Student st)
	{
		return ((course == st.getcourse()) &&
			     (group == st.getgroup()) &&
			   (surname == st.getsurname()) &&
	  (numberRecordBook == st.getnumberRecordBook()));
	}

	//загрузка данных о студенте в файл
	void Student::StudentToFile(fstream *file)
	{
		file->write(reinterpret_cast<char*>(&(this->course)), sizeof(this->course));
		StrToBin(file, this->group);
		StrToBin(file, this->surname);
		StrToBin(file, this->numberRecordBook);
	}

//загрузка данных о студенте из файла
Student StudentFromFile(fstream *file, bool &ok) 
{
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

//Функция ввода структуры Student с консоли
Student InputScreenStudent()
{
	Student st;

	st.setcourse(InputNumber(1, 6, "Введите курс (1-6): "));
	st.setgroup(InputInformation("Введите группу: "));
	st.setsurname(InputInformation("Введите фамилию: "));
	st.setnumberRecordBook(InputInformation("Введите номер зачётки: "));

	return st;
}

//Функция вывода структуры Student на консоль
void OutputScreenStudent(Student st)
{
	cout << setw(1) << "|" << setw(10) << left << st.getcourse() << "|" << setw(10) << left << st.getgroup() << "|" << setw(20) << left << st.getsurname() << "|" << setw(25) << left << st.getnumberRecordBook() << "|";
}

//Перевод структуры Student в строку
string ToString(Student st, __int32 i)
{
	string result = "Запись - " + to_string(i) + "\n" + "Курс: " + to_string(st.getcourse()) + "\n" + "Группа: " + st.getgroup() + "\n" + "Фамилия: " + st.getsurname() + "\n" + "Номер зачётки: " + st.getnumberRecordBook() + "\n";

	return result;
}
//Сравнивание записей
bool IsEqual(Student st1, Student st2)
{
	return ((st1.getcourse() == st2.getcourse()) &&
		     (st1.getgroup() == st2.getgroup()) &&
		   (st1.getsurname() == st2.getsurname()) &&
  (st1.getnumberRecordBook() == st2.getnumberRecordBook()));
}

//считывание структуры Student из строки
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
			string wrd = "Курс: ";
			result.setcourse(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Группа: ";
			result.setgroup(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Фамилия: ";
			result.setsurname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Номер зачётки: ";
			result.setnumberRecordBook(s.substr(wrd.length(), s.length()));
		}
	}
	catch (...)
	{
		cout << "Ошибка записи файла!" << endl;
	}
	return result;
}

/*Поиск равного элемента по выбранному критерию
type_search - тип поиска:
1 - по группе
2 - по курсу
3 - по номеру зачетной книжки
4 - по фамилии*/
bool SearchElement(Student a, Student b, __int32 type_search)
{
	switch (type_search)
	{
		case 1:
		{
			return (a.getgroup() == b.getgroup());
		}
		case 2:
		{
			return (a.getcourse() == b.getcourse());
		}
		case 3:
		{
			return (a.getnumberRecordBook() == b.getnumberRecordBook());
		}
		case 4:
		{
			return (a.getsurname() == b.getsurname());
		}
		default:
		{
			return false;
		}
	}
}

/*Ввод критерия поиска в зависимости от выбранного типа
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
Student InputChangeTypeSearchStudent(__int32 type_search)
{
	Student result;

	switch (type_search)
	{
		case 1:
		{
			result.setgroup(InputInformation("Введите группу: "));
			return result;
		}
		case 2:
		{
			result.setcourse(InputNumber(1, 6, "Введите курс: "));
			return result;
		}
		case 3:
		{
			result.setnumberRecordBook(InputInformation("Введите номер зачётки: "));
			return result;
		}
		case 4:
		{
			result.setsurname(InputInformation("Введите фамилию: "));
			return result;
		}
		default:
		{
			return result;
		}
	}
}

/*Сравнение структур по выбранного полю
type_search - тип поиска:
1 - по номеру группы
2 - по номеру курса
3 - по номеру зачетки
4 - по фамилии*/
__int32 Sorte(Student a, Student b, __int32 type_search)
{
	switch (type_search)
	{
		case 1:
		{
			if (a.getgroup() > b.getgroup())
			{
				return 1;
			}
			else if (a.getgroup() < b.getgroup())
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
		case 2:
		{
			if (a.getcourse() > b.getcourse()) 
			{ 
				return 1; 
			}
			else if (a.getcourse() < b.getcourse())
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
		case 3:
		{
			if (a.getnumberRecordBook() > b.getnumberRecordBook())
			{
				return 1;
			}
			else if (a.getnumberRecordBook() < b.getnumberRecordBook())
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
		case 4:
		{
			if (a.getsurname() > b.getsurname())
			{
				return 1;
			}
			else if (a.getsurname() < b.getsurname())
			{
				return -1;
			}
			else
			{
				return 0;
			}
		}
		default:
		{
			return -2;
		}
	}
}
//подсчёт средней успеваемости
double AverageScope(Student st)
{
	double res = 0;
	__int32 count = 0;

	for (__int32 i = 0; i < st.getmarks().Size(); i++)
	{
		res += st.getmarks().GetVector()[i].mark;
		count++;
	}
	if (count == 0)
	{
		return 0;
	}
	else
	{
		return res / count;
	}
}



