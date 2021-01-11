#define _CRT_SECURE_NO_WARNING
#include "beer.h"
#include "cognac.h"
#include "wine.h"
#include "milk.h"
#include "lemonade.h"
#include "mineralwater.h"
#include "Drinker.h"
#include <iostream>
#include <exception>
#include <vector>
#include <string>
#include <Windows.h>
#include <ctime>


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	Beer* budweiser;
	Cognac* hennessy;
	Wine* el_toro;
	Milk* nemoloko;
	Lemonade* buratino;
	MineralWater* bonaqua;
	setlocale(LC_ALL, "Rus");
	cout << "Добро пожаловать\n";
	try
	{
		budweiser = new Beer("Будвейзер", 0.5, 4.7, RawMaterial::Weed);
		hennessy = new Cognac("Хеннесси", 0.7, 40, Excerpt::GrandReserve);
		el_toro = new Wine("Эль торо", 0.5, 10, Type::Red, Sugary::Semisweet);
		nemoloko = new Milk("Немолоко", 0.4, Sugaric::None, 3.2);
		buratino = new Lemonade("Буратино", 0.33, Sugaric::Some, Taste::Coke);
		bonaqua = new MineralWater("Бонаква", 0.5, Sugaric::None, Carbonated::Sparkled);
	}
	catch (runtime_error & error)
	{
		cout << error.what() << endl;
		return 1;
	}
	vector <BottledDrinks*> drinks = { budweiser, hennessy, el_toro, nemoloko, buratino, bonaqua };
	vector <string> types = { "Пиво", "Коньяк", "Вино", "Молоко", "Лимонад", "Вода" };
	vector <Beer*> beers = { budweiser };
	vector <Cognac*> cognacs = { hennessy };
	vector <Wine*> wines = { el_toro };
	vector <Milk*> milks = { nemoloko };
	vector <Lemonade*> lemonades = { buratino };
	vector <MineralWater*> waters = { bonaqua };
	int choice;
	do
	{
		cout << " \n\n1. Зайти в бар \n2. Завершить программу\n\nПожалуйста, введите номер действия: ";
		string the_choice = "0", type;
		cin >> type;
		the_choice += type;
		choice = stoi(the_choice);
		switch (choice)
		{
		case 1:
		{
			Drinker* drinker;
			cout << "\nВведите возраст посетителя: ";
			int drinker_age;
			cin >> drinker_age;


			try
			{
				drinker = new Drinker(drinker_age);
			}
			catch (runtime_error & error)
			{
				cout << error.what() << endl;
				break;
			}

			int choice_way;
			do
			{
				cout << endl << "Что Вы хотите сделать?\n\n1. Заказать напиток\n2. Выйти\nПожалуйста, введите номер действия: ";
				string the_choice_way = "0", type_way;
				cin >> type_way;
				the_choice_way += type_way;
				choice_way = stoi(the_choice_way);
				switch (choice_way)
				{
				case 1:
				{
					int choice_way_way;
					do
					{

						cout << "Что Вы хотите сделать?\n\n1.  Взглянуть на имеющиеся напитки\n2.  Узнать информацию о напитках\n3.  Вернуться в изначальное меню\n\nПожалуйста, введите номер действия: ";
						string the_choice_way_way = "0", type_way_way;
						cin >> type_way_way;
						the_choice_way_way += type_way_way;
						choice_way_way = stoi(the_choice_way_way);

						switch (choice_way_way)
						{
						case 1:
						{
							cout << "\nВыберите тип напитка, который хотите выпить:\n\n";
							for (int i = 0; i < types.size(); i++)
							{
								cout << types[i] << " -- " << i << endl;
							}
							cout << "\nВведите номер типа напитка, который хотите выпить: ";
							int type_choice;
							cin >> type_choice;
							if (((type_choice == 0) || (type_choice == 1) || (type_choice == 2)) && (drinker->GetAge() < 18))
							{
								cout << "\nВы ещё не доросли до этого напитка!\n\n";

								break;
							}

							switch (type_choice)
							{

							case 0:
							{
								for (int i = 0; i < beers.size(); i++)
								{
									cout << beers[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: " << endl;
								int drink_choice;
								cin >> drink_choice;
								cout << "Напиток выпит!\n" << endl;
								try
								{
									drinker->Drink(beers[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							case 1:
							{
								for (int i = 0; i < cognacs.size(); i++)
								{
									cout << cognacs[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								cout << "Напиток выпит!\n" << endl;
								try
								{
									drinker->Drink(cognacs[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							case 2:
							{
								for (int i = 0; i < wines.size(); i++)
								{
									cout << wines[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								cout << "Напиток выпит!\n" << endl;
								try
								{
									drinker->Drink(wines[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							case 3:
							{
								for (int i = 0; i < milks.size(); i++)
								{
									cout << milks[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								cout << "Напиток выпит!\n" << endl;
								try
								{
									drinker->Drink(milks[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							case 4:
							{
								for (int i = 0; i < lemonades.size(); i++)
								{
									cout << lemonades[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								cout << "Напиток выпит!\n" << endl;
								try
								{
									drinker->Drink(lemonades[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							case 5:
							{
								for (int i = 0; i < waters.size(); i++)
								{
									cout << waters[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								cout << "Напиток выпит!\n" << endl;
								try
								{
									drinker->Drink(waters[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							}
							break;
						}
						case 2:
						{
							cout << "\nВыберите тип напитка, который хотите выпить:\n\n";
							for (int i = 0; i < types.size(); i++)
							{
								cout << types[i] << " -- " << i << endl;
							}
							cout << "\nВведите номер типа напитка, который хотите выпить: ";
							int type_choice;
							cin >> type_choice;

							switch (type_choice)
							{

							case 0:
							{
								for (int i = 0; i < beers.size(); i++)
								{
									cout << beers[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;

								beers[drink_choice]->GetInfo();
								break;
							}
							case 1:
							{
								for (int i = 0; i < cognacs.size(); i++)
								{
									cout << cognacs[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								cognacs[drink_choice]->GetInfo();
								break;
							}
							case 2:
							{
								for (int i = 0; i < wines.size(); i++)
								{
									cout << wines[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								try
								{
									drinker->Drink(wines[drink_choice]);
								}
								catch (runtime_error & error)
								{
									cout << error.what() << endl;
								}
								break;
							}
							case 3:
							{
								for (int i = 0; i < milks.size(); i++)
								{
									cout << milks[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								milks[drink_choice]->GetInfo();
								break;
							}
							case 4:
							{
								for (int i = 0; i < lemonades.size(); i++)
								{
									cout << lemonades[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								lemonades[drink_choice]->GetInfo();
								break;
							}
							case 5:
							{
								for (int i = 0; i < waters.size(); i++)
								{
									cout << waters[i]->GetName() << " -- " << i << endl;
								}
								cout << "\nВведите номер напитка: ";
								int drink_choice;
								cin >> drink_choice;
								waters[drink_choice]->GetInfo();
								break;
							}
							}
							break;
						}
						case 3:
						{

							break;
						}
						}
					} while (choice_way_way != 3);
					break;
				}
				}
			} while (choice_way != 3);
			break;
		}

		case 2:
		{
			cout << "Вы вышли из бара\n\n";
			return 0;
		}
		default:
		{
			cout << "Такого действия не существует\n";
			break;
		}
		}
	} while (choice != 2);
	return 0;
}