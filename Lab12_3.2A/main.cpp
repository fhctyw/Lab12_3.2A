#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;

#pragma region "Прізвища студентів"
string surnames[] =
{
	"Бурачинський",
	"Кваша",
	"Попенко",
	"Жученко",
	"Пероганич",
	"Карпінський",
	"Дроб\'язко",
	"Боровий",
	"Приступа",
	"Костюк",

	"Гайдук",
	"Грицина",
	"Балога",
	"Величковська",
	"Марченко",
	"Бершеда",
	"Лимаренко",
	"Кравченко",
	"Ластівка",
	"Бельська",
};
#pragma endregion

enum class Spec { PZ, IT, KN, AT };
string strSpec[] = { "Програмне забезпечення", "Інформаційні технології", "Компютерні науки", "Автомобільний транспорт" };

struct Student
{
	string surname;
	int course;
	Spec spec;
	double mark_physic;
	double mark_math;
	double mark_informatic;
};

void Generate(Student* s, size_t cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		s[i].surname = surnames[rand() % 20];
		s[i].course = 1 + rand() % 6;
		s[i].spec = Spec(rand() % 4);

		s[i].mark_informatic = (30 + rand() % 21) / 10.0;
		s[i].mark_physic = (30 + rand() % 21) / 10.0;
		s[i].mark_math = (30 + rand() % 21) / 10.0;
	}
}

double avgMark(Student s)
{
	return round(((s.mark_informatic + s.mark_math + s.mark_physic) / 3.0) * 100) / 100;
}

void Display(Student* s, size_t cnt, bool avg = false)
{
	cout << "---------------------------------------------------------------------------------------------";
	if (avg)
		cout << "------";
	cout << endl;
	cout << "|  №  | курс |    прізвище    |       спеціальність     | фізика | математика | інформатика |";
	if (avg)
		cout << " avg |";
	cout << endl;
	cout << "---------------------------------------------------------------------------------------------";
	if (avg)
		cout << "------";
	cout << endl;

	cout << left;
	for (size_t i = 0; i < cnt; i++)
	{
		cout << "|" << setw(5) << i+1 << "|"
			<< setw(6) << s[i].course << "|"
			<< setw(16) << s[i].surname << "|"
			<< setw(25) << strSpec[int(s[i].spec)] << "|"
			<< setw(8) << s[i].mark_physic << "|"
			<< setw(12) << s[i].mark_math << "|"
			<< setw(13) << s[i].mark_informatic << "|";
		if (avg)
			cout << setw(5) << avgMark(s[i]) << "|";
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------------";
	if (avg)
		cout << "------";
	cout << endl;
}

void Display(Student* s, size_t cnt, int* I,  bool avg = false)
{
	cout << "---------------------------------------------------------------------------------------------";
	if (avg)
		cout << "------";
	cout << endl;
	cout << "|  №  | курс |    прізвище    |       спеціальність     | фізика | математика | інформатика |";
	if (avg)
		cout << " avg |";
	cout << endl;
	cout << "---------------------------------------------------------------------------------------------";
	if (avg)
		cout << "------";
	cout << endl;

	cout << left;
	for (size_t i = 0; i < cnt; i++)
	{
		cout << "|" << setw(5) << i+1 << "|"
			<< setw(6) << s[I[i]].course << "|"
			<< setw(16) << s[I[i]].surname << "|"
			<< setw(25) << strSpec[int(s[I[i]].spec)] << "|"
			<< setw(8) << s[I[i]].mark_physic << "|"
			<< setw(12) << s[I[i]].mark_math << "|"
			<< setw(13) << s[I[i]].mark_informatic << "|";
		if (avg)
			cout << setw(5) << avgMark(s[I[i]]) << "|";
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------------------";
	if (avg)
		cout << "------";
	cout << endl;
}

void RealSort(Student* s, size_t cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		for (size_t j = 0; j < cnt-i-1; j++)
		{
			double j0 = avgMark(s[j]);
			double j1 = avgMark(s[j + 1]);
			if (j0 < j1 || j0 == j1 && s[j].mark_informatic < s[j+1].mark_informatic
				|| j0 == j1 && s[j].mark_informatic == s[j + 1].mark_informatic && s[j].surname < s[j + 1].surname)
				swap(s[j], s[j + 1]);
		}
	}
}

int* IndexSort(Student* s, size_t cnt)
{
	int* I = new int[cnt];
	for (size_t i = 0; i < cnt; i++)
		I[i] = i;

	int i, j, value;
	for (size_t i = 1; i < cnt; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && (avgMark(s[I[j]]) < avgMark(s[value]) || 
				avgMark(s[I[j]]) == avgMark(s[value]) && s[j].mark_informatic < s[j + 1].mark_informatic || 
				avgMark(s[I[j]]) == avgMark(s[value]) && s[j].mark_informatic == s[j + 1].mark_informatic && s[j].surname < s[j + 1].surname);
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}

int BinSearch(Student* s, size_t cnt, string surname, double avg, double last_mark)
{
	int l = 0, r = cnt - 1, m;
	do
	{
		m = (l + r) / 2;
		if (s[m].surname == surname && avgMark(s[m]) == avg && s[m].mark_informatic == last_mark)
			return m;
		double a = avgMark(s[m]);
		if (a > avg || a == avg && s[m].mark_informatic > last_mark || a == avg && s[m].mark_informatic == last_mark && s[m].surname > surname)
			l = m + 1;
		else
			r = m - 1;
	} while (l < r);
	return -1;
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	size_t cnt;
	cout << "Введіть кількість студентів у масиві: "; cin >> cnt;
	Student* s = new Student[cnt];
	Generate(s, cnt);
	int choice;
	do {

		cout << "1 - Відобразити масив" << endl;
		cout << "2 - Фізичне впорядкування" << endl;
		cout << "3 - Індексне впорядкування" << endl;
		cout << "4 - Бінарний пошук" << endl;
		cout << "0 - Вихід" << endl;
		cout << "choice: ";

		cin.sync();
		cin.get();

		cin >> choice;

		if (choice == 1)
			Display(s, cnt);
		else if (choice == 2)
			RealSort(s, cnt);
		else if (choice == 3)
			Display(s, cnt, IndexSort(s, cnt));
		else if (choice == 4)
		{
			string surname;
			double avg, last;
			cout << "прізвище: "; cin >> surname;
			cout << "середню оцінку: "; cin >> avg;
			cout << "оцінку з інформатики: "; cin >> last;
			int index = BinSearch(s, cnt, surname, avg, last);
			if (index == -1)
				cout << "Нема" << endl;
			else
				cout << "Є " << endl;
		}
	} while (choice != 0);

	delete[] s;

	return 0;
}