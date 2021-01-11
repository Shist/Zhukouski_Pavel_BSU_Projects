#include <iostream> // Для вывода исключений
#include <fstream> // Для работы с файлом input.txt
#include <exception> // Для выбрасывания исключений
#include <string> // Для работы со строками (именами животных и их владельцев)
#include <vector> // Для создания контейнера, в котором мы будем хранить наши структуры "животное"
#include <algorithm> // Для функции transform
#include <iterator> // Понадобится во время реализации функции ToLower
#include <tuple> // Для запросов
#include <set> // Для запросов
#include <map> // Для запросов
using namespace std;

struct Pet // Создаем структуру "животное"
{
	string OwnerName; // Имя владельца
	string Species; // Вид животного
	string PetName; // Кличка животного (если есть)
	int Age; // Возраст животного
	Pet(string newOwnerName, string NewSpecies, string newName, int newAge) : // Конструктор
		OwnerName(newOwnerName), Species(NewSpecies), PetName(newName), Age(newAge) // Список инициализации
	{
		if (OwnerName.empty()) // Проверка на пустоту имени хозяина
			throw exception("Can't have an empty owner!");
		if (Species.empty()) // Приверка на пустоту вида животного
			throw exception("Can't have an emty species!");
		if (Age < 0) // Проверка на отрицательное значение возраста
			throw exception("Age can't be negative");
	}
};

string LowerCase(const string& str)
{ // Функция, меняющая название вида животного таким образом, чтобы все буквы были маленькими, ведь в нём регистр не важен
	string temp;
	transform(str.begin(), str.end(), back_inserter(temp), tolower);
	return temp;
}

Pet* petParse(string str) // Метод Parse для структуры "животное"
{
	string Attributes[4]; // Создадим массив string-ов для наших 4-ех элементов структуры "животное"
	string temp = "";
	size_t p = 0; // Начало слова
	size_t g; // Конец слова
	size_t k = 0;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == ',')
		{
			g = i;
			for (size_t j = p; j < g; j++)
			{
				temp.push_back(str[j]);
			}
			Attributes[k] = temp;
			k++;
			temp = "";
			g = 0;
			if (i + 1 < str.size() && str[i + 1] == ',') // Если следующий символ после запятой тоже является запятой
			{
				Attributes[k] = "";
				k++;
				i += 3;
				p = i;
			}
			if (i + 1 < str.size() && str[i + 1] == ' ') // Если следующий символ после запятой является пробелом
			{
				i += 2;
				p = i;
			}
		}
	}
	for (size_t j = p; j < str.size(); j++) // Обрабатываем последнюю штуку (возраст животного)
	{
		temp.push_back(str[j]);
	}
	Attributes[k] = temp;
	return new Pet(Attributes[0],
		LowerCase(Attributes[1]),
		Attributes[2],
		stoi(Attributes[3])); // Для последнего элемента воспользуемся методом stoi(...) из класса String
}

istream& operator >> (istream& str, Pet*& pet) // Ввод
{
	string temp;
	if (getline(str, temp))
		pet = petParse(temp);
	return str;
}

ostream& operator << (ostream& str, const Pet& pet) // Вывод в поток информации о животном
{
	str << "Pet's name: " << (pet.PetName.empty() ? "<empty>" : pet.PetName) << endl;
	str << "Pet's species: " << pet.Species << ";" << endl;
	str << "Pet's age: " << pet.Age << ";" << endl;
	str << "Owner's name: " << pet.OwnerName << ";" << endl;
	return str;
}

int main()
{
	ifstream fin("input.txt");
	if (!fin.is_open()) // Проверка на открытие файла
	{
		cerr << "Input file did not open!";
		return -1;
	}
	vector<Pet*> pets; // Создаем вектор, куда и будем считывать данные с файла input.txt
	Pet* pet;
	try
	{
		while (fin >> pet) // Вводим данные
			pets.push_back(pet); // И пихаем их в вектор
	}
	catch (exception& ex)
	{ // Ловим исключения
		cerr << "Something fucked up: " << ex.what() << endl;
		for (Pet *pet : pets)
			delete pet; // Если у нас что-то пошло не так, удаляем то, что создали
		fin.close(); // И закрываем входной файл
		return -2;
	}
	fin.close(); // Закрываем файл input.txt, так мы из него уже вычитали всю инфомрацию
	for (Pet* pet : pets) // Выводим информацию о каждом животном
		cout << *pet << endl;
	map <string, tuple <set <string>, set <string>, pair <Pet*, Pet*>>> infoBySpecies; // Для запросов 2) и 4)
	map <string, set <string>> speciesByOwner; // Для запросов 1)
	map <string, set <string>> speciesByName; // Для запросов 3)
	for (Pet* pet : pets)
	{ // Пройдем по всем имеющимся животным циклом и заполним наши контейнеры STL нужной информацией...
		speciesByOwner[pet->OwnerName].insert(pet->Species); // 1-ый запрос (количество различных видов животных у каждого владельца)
		speciesByName[pet->PetName].insert(pet->Species); // 3-ий запрос (сколько видов животных носит определённую кличку)
		auto& Info = infoBySpecies[pet->Species]; // 2-ой и 4-ой запросы
		get<0>(Info).insert(pet->OwnerName);
		get<1>(Info).insert(pet->PetName);
		if (get <2>(Info).first == nullptr ||
			pet->Age < get<2>(Info).first->Age)
		{
			get<2>(Info).first = pet;
		}
		if (get <2>(Info).second == nullptr ||
			pet->Age > get<2>(Info).second->Age)
		{
			get<2>(Info).second = pet;
		}
	}
	bool exit = false; // Введем флажок для работы с запросами
	int option; // Также нам понадобится int-овая переменная, чтобы пользователь мог выбрать номер запроса
	while (!exit)
	{ // Пишем меню-шку для пользователя
		cout << "Please, select the query to process a number in the range 1-4 or 0 to exit:" << endl;
		cout << "1. Calculate the number of different types of animals for each owner." << endl;
		cout << "2. For a specific type of animal (entered by the user) to bring all its owners and nicknames." << endl;
		cout << "3. Determine how many species of animals bears a certain nickname (the nickname is entered by the user)." << endl;
		cout << "4. To display information about the age of the oldest and the youngest animal of each species." << endl;
		if (!(cin >> option))
		{ // Если пользователь не вводит номер, то просим его ввести заново
			cout << "Please type or number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (option < 0 || option > 4)
		{ // Если же пользователь вводит номер, но не тот, что нужно, то опять-таки просим его ввести заново
			cout << "Please, type the correct number" << endl;
			continue;
		}
		string species; // Для запросов по виду
		string PetName; // Для запросов по кличке
		tuple <set <string>, set <string>, pair <Pet*, Pet*>> answer; // Создаем элемент tuple для работы с map для запросов 2) и 4)
		pair <Pet*, Pet*> petsPair; // В этом элементе будем хранить пару самого молодого и самого старого животных
		switch (option)
		{
		case 1: // Запрос 1)
			if (speciesByOwner.empty())
			{
				cout << "There are no owners in the collection" << endl;
				break;
			}
			for (auto Owner : speciesByOwner)
			{
				cout << "The owner - " << Owner.first << " - has " << Owner.second.size() << " different species of pets" << endl;
			}
			break;
		case 2: // Запрос 2)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please type the species for which you want to get your info: ";
			getline(cin, species);
			species = LowerCase(species); // Приведем к нижнему регистру
			if (infoBySpecies.find(species) == infoBySpecies.end())
			{
				cout << "Can't find that exotic species in our collection!" << endl;
				break;
			}
			answer = infoBySpecies[species];
			cout << "Pets of the species - " << species << " - have the following owners:" << endl;
			for (string owner : get<0>(answer))
			{
				cout << owner << endl;
			}
			cout << "And that pets have the following names:" << endl;
			for (string name : get<1>(answer))
			{
				cout << (name.empty() ? "<empty>" : name) << endl;
			}
			break;
		case 3: // Запрос 3)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Type the name for which you want to obtain your info: ";
			getline(cin, PetName);
			if (speciesByName.find(PetName) == speciesByName.end())
			{
				cout << "Can't find that name in our collection!" << endl;
				break;
			}
			cout << "As many as " << speciesByName[PetName].size() << " species of pets share this name." << endl;
			break;
		case 4: // Запрос 4)
			cout << "<<<The youngest pets>>>" << endl << endl;
			for (auto speciesPair : infoBySpecies)
			{
				species = speciesPair.first;
				petsPair = get<2>(speciesPair.second);
				cout << "Here is the youngest pet from the species: " << species << endl;
				cout << *petsPair.first << endl;
			}
			cout << "<<<The oldest pets>>>" << endl << endl;
			for (auto speciesPair : infoBySpecies)
			{
				species = speciesPair.first;
				petsPair = get<2>(speciesPair.second);
				cout << "Here is the oldest pet from the species: " << species << endl;
				cout << *petsPair.second << endl;
			}
			break;
		case 0: // Если пользователь введет нолик, то мы выходим из цикла
			exit = true;
			break;
		}
	}
	for (Pet* pet : pets)
		delete pet; // Чистим память от созданных структур
	return 0;
}