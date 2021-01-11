#include <iostream>
#include <Windows.h>
#include <random>
#include <string>
using namespace std;

int main()
{
	system("color 0B");

	setlocale(LC_ALL, "Rus");

	random_device generator;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));

	int crime_points = 0;

	cout << "Здравствуйте, вас приветствует система Сивилла." << endl;
	Sleep(500);
	cout << "Вам потребуется ответить на несколько вопросов для определения значения вашего психо-паспорта." << endl;
	Sleep(500);
	cout << "В зависимости от ваших ответов будет рассчитан ваш коэффициент преступности, а также положение в обществе." << endl;
	Sleep(500);
	cout << "Для того, чтобы продолжить, представьтесь, введите ваше настоящее имя: ";

	string Name = "Name";
	cin >> Name;

	uniform_int_distribution<unsigned short int> distribution_name_coefficient(3, 7);
	crime_points += distribution_name_coefficient(generator)*Name.size();

	cout << "Здравствуйте, " << Name << ", для продолжения, ответьте, пожалуйста, ещё на несколько вопросов." << endl;
	Sleep(500);
	cout << "Предположим, вы работаете в бюро общественной безопасности и вам вместе с вашим коллегой поручили догнать " << endl;
	Sleep(500);
	cout << "опасного преступника." << endl;
	cout << "Однако, в процессе задания ваш коллега попал в беду, а преступник начал убегать." << endl;
	Sleep(500);
	cout << "Как вы поступите в данной ситуации?" << endl;
	cout << "Введите \"1\", если вы бы продолжили погоню за преступником." << endl;
	cout << "Введите \"2\", если вы бы бросили погоню и оказали помощь вашему коллеге." << endl;

	string temp = "";
	int choice_num = 0;
	cin >> temp;
	choice_num = atoi(temp.c_str());

	bool first_flag = true;

	while (first_flag)
	{
		switch (choice_num)
		{
		case 1:
			first_flag = false;
			break;
		case 2:
			first_flag = false;
			crime_points += 141;
			break;
		default:
			crime_points += 25;
			cout << "Извините, вы ввели некорректную цифру для ответа, попробуйте ещё раз." << endl;
			cout << "Введите \"1\", если вы бы продолжили погоню за преступником." << endl;
			cout << "Введите \"2\", если вы бы бросили погоню и оказали помощь вашему коллеге." << endl;
			temp = "";
			cin >> temp;
			choice_num = atoi(temp.c_str());
		}
	}

	cout << "Переход к следующему вопросу..." << endl;
	Sleep(1500);
	cout << "Предположим, вы снова нашли преступника, однако ваш доминатор показывает вам, что " << endl;
	Sleep(500);
	cout << "коэффициент преступности у преступника не является критическим, ваш спуск на доминаторе заблокирован." << endl;
	Sleep(500);
	cout << "Однако, так получилось, что рядом вас лежит револьвер с патронами, с помощью которого можно убить преступника." << endl;
	Sleep(500);
	cout << "Станете ли вы убивать преступника с помощью револьвера или будете действовать согласно команде доминатора?" << endl;
	cout << "Введите \"1\", если вы бы убили преступника с помощью револьвера." << endl;
	cout << "Введите \"2\", если вы бы не убивали преступника, тем самым действуя согласно данным доминатора." << endl;

	string temp_2 = "";
	int choice_num_2 = 0;
	cin >> temp_2;
	choice_num_2 = atoi(temp_2.c_str());

	bool second_flag = true;

	while (second_flag)
	{
		switch (choice_num_2)
		{
		case 1:
			second_flag = false;
			crime_points += 213;
			break;
		case 2:
			second_flag = false;
			break;
		default:
			crime_points += 25;
			cout << "Извините, вы ввели некорректную цифру для ответа, попробуйте ещё раз." << endl;
			cout << "Введите \"1\", если вы бы убили преступника с помощью револьвера." << endl;
			cout << "Введите \"2\", если вы бы не убивали преступника, тем самым действуя согласно данным доминатора." << endl;
			temp_2 = "";
			cin >> temp_2;
			choice_num_2 = atoi(temp_2.c_str());
		}
	}

	cout << "Благодарим вас за предоставленные ответы, собранных данных достаточно для " << endl;
	Sleep(500);
	cout << "определения вашего коэффициента преступности и оттенка психо-паспорта." << endl;
	Sleep(500);
	cout << "Оценка психо-паспорта..." << endl;
	Sleep(2700);

	uniform_int_distribution<unsigned short int> distribution(0, crime_points);

	unsigned short int crime_coefficient = distribution(generator);

	int psycho_group = 0;

	if (crime_coefficient > 0 && crime_coefficient <= 50) psycho_group = 1;
	else if (crime_coefficient > 50 && crime_coefficient <= 100) psycho_group = 2;
	else if (crime_coefficient > 100 && crime_coefficient <= 150) psycho_group = 3;
	else if (crime_coefficient > 150 && crime_coefficient <= 200) psycho_group = 4;
	else if (crime_coefficient > 200 && crime_coefficient <= 250) psycho_group = 5;
	else if (crime_coefficient > 250 && crime_coefficient <= 300) psycho_group = 6;
	else if (crime_coefficient > 300) psycho_group = 7;

	cout << "Коэффициент преступности: ";

	switch (psycho_group)
	{
	case 1:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << crime_coefficient;
		cout << "." << endl;
		cout << "Ваш психо-паспорт в отличном состоянии. Вам рекомендована работа в любом министерстве или бюро." << endl;
		cout << "Выстрел из доминатора в любом из режимов запрещён, спуск заблокирован." << endl;
		break;
	case 2:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Ваш психо-паспорт в ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 10));
		cout << "хорошем";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " состоянии. Вам позволительно работать на большинстве офисных работ." << endl;
		cout << "Выстрел из доминатора в любом из режимов запрещён, спуск заблокирован." << endl;
		break;
	case 3:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Ваш психо-паспорт в ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << "приемлимом";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " состоянии. Некоторые возможности ограничены. Рекомендован ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
		cout << "визит к психологу";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Выстрел из доминатора в любом из режимов запрещён, спуск заблокирован." << endl;
		break;
	case 4:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Ваш психо-паспорт на ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		cout << "предельно допустимом уровне";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ". Многие возможности ограничены. Вы обязаны пройти ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 14));
		cout << "психо-реабилитацию";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Выстрел из доминатора в любом из режимов запрещён, спуск заблокирован." << endl;
		break;
	case 5:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Ваш психо-паспорт в ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "плохом";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " состоянии. Вас можно рассматривать в качестве ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "потенциального преступника";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "В связи с обстоятельствами вас направят на ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "курс реабилитации";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " в ближайшее время." << endl;
		cout << "На усмотрение обладателя разрешен выстрел из доминатора, режим: ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 6));
		cout << "\"Парализатор\"";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		break;
	case 6:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Ваш психо-паспорт в ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "очень плохом";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " состоянии. Вас можно рассматривать в качестве ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "опасного потенциального преступника";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Для вас будет ещё приемлимым попытаться пройти ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "курс реабилитации";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ". Бюро безопасности прибудет за вами в ближайшее время." << endl;
		cout << "На усмотрение обладателя разрешен выстрел из доминатора, режим: ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 12));
		cout << "\"Парализатор\"";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		break;
	case 7:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Ваш психо-паспорт в ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "критическом состоянии";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ". Вы - ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "угроза для общества";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		cout << "В связи с вышеуказанным вы ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "не подлежите никакой реабилитации";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << " и ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "должны подвергнуться немедленному уничтожению";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		cout << "Разрешен выстрел из доминатора, режим: ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 4));
		cout << "\"Уничтожитель\"";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "!" << endl;
		break;
	default:
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << crime_coefficient;
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Природа психо-паспорта ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "до конца не изучена";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << ", коэффициент преступности равен ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "нестандартному значению";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Предположительно, вы связаны с ";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "преступной симптоматикой";
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
		cout << "." << endl;
		cout << "Выстрел из доминатора в любом из режимов запрещён, спуск заблокирован." << endl;
		break;
	}

	SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 11));
	cout << "Система Сивилла. Сделаем общество лучше вместе!" << endl;
	system("pause");
	return 0;
}