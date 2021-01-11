#include <iostream> // ��� ������ ����������
#include <fstream> // ��� ������ � ������ input.txt
#include <exception> // ��� ������������ ����������
#include <string> // ��� ������ �� �������� (������� �������� � �� ����������)
#include <vector> // ��� �������� ����������, � ������� �� ����� ������� ���� ��������� "��������"
#include <algorithm> // ��� ������� transform
#include <iterator> // ����������� �� ����� ���������� ������� ToLower
#include <tuple> // ��� ��������
#include <set> // ��� ��������
#include <map> // ��� ��������
using namespace std;

struct Pet // ������� ��������� "��������"
{
	string OwnerName; // ��� ���������
	string Species; // ��� ���������
	string PetName; // ������ ��������� (���� ����)
	int Age; // ������� ���������
	Pet(string newOwnerName, string NewSpecies, string newName, int newAge) : // �����������
		OwnerName(newOwnerName), Species(NewSpecies), PetName(newName), Age(newAge) // ������ �������������
	{
		if (OwnerName.empty()) // �������� �� ������� ����� �������
			throw exception("Can't have an empty owner!");
		if (Species.empty()) // �������� �� ������� ���� ���������
			throw exception("Can't have an emty species!");
		if (Age < 0) // �������� �� ������������� �������� ��������
			throw exception("Age can't be negative");
	}
};

string LowerCase(const string& str)
{ // �������, �������� �������� ���� ��������� ����� �������, ����� ��� ����� ���� ����������, ���� � �� ������� �� �����
	string temp;
	transform(str.begin(), str.end(), back_inserter(temp), tolower);
	return temp;
}

Pet* petParse(string str) // ����� Parse ��� ��������� "��������"
{
	string Attributes[4]; // �������� ������ string-�� ��� ����� 4-�� ��������� ��������� "��������"
	string temp = "";
	size_t p = 0; // ������ �����
	size_t g; // ����� �����
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
			if (i + 1 < str.size() && str[i + 1] == ',') // ���� ��������� ������ ����� ������� ���� �������� �������
			{
				Attributes[k] = "";
				k++;
				i += 3;
				p = i;
			}
			if (i + 1 < str.size() && str[i + 1] == ' ') // ���� ��������� ������ ����� ������� �������� ��������
			{
				i += 2;
				p = i;
			}
		}
	}
	for (size_t j = p; j < str.size(); j++) // ������������ ��������� ����� (������� ���������)
	{
		temp.push_back(str[j]);
	}
	Attributes[k] = temp;
	return new Pet(Attributes[0],
		LowerCase(Attributes[1]),
		Attributes[2],
		stoi(Attributes[3])); // ��� ���������� �������� ������������� ������� stoi(...) �� ������ String
}

istream& operator >> (istream& str, Pet*& pet) // ����
{
	string temp;
	if (getline(str, temp))
		pet = petParse(temp);
	return str;
}

ostream& operator << (ostream& str, const Pet& pet) // ����� � ����� ���������� � ��������
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
	if (!fin.is_open()) // �������� �� �������� �����
	{
		cerr << "Input file did not open!";
		return -1;
	}
	vector<Pet*> pets; // ������� ������, ���� � ����� ��������� ������ � ����� input.txt
	Pet* pet;
	try
	{
		while (fin >> pet) // ������ ������
			pets.push_back(pet); // � ������ �� � ������
	}
	catch (exception& ex)
	{ // ����� ����������
		cerr << "Something fucked up: " << ex.what() << endl;
		for (Pet *pet : pets)
			delete pet; // ���� � ��� ���-�� ����� �� ���, ������� ��, ��� �������
		fin.close(); // � ��������� ������� ����
		return -2;
	}
	fin.close(); // ��������� ���� input.txt, ��� �� �� ���� ��� �������� ��� ����������
	for (Pet* pet : pets) // ������� ���������� � ������ ��������
		cout << *pet << endl;
	map <string, tuple <set <string>, set <string>, pair <Pet*, Pet*>>> infoBySpecies; // ��� �������� 2) � 4)
	map <string, set <string>> speciesByOwner; // ��� �������� 1)
	map <string, set <string>> speciesByName; // ��� �������� 3)
	for (Pet* pet : pets)
	{ // ������� �� ���� ��������� �������� ������ � �������� ���� ���������� STL ������ �����������...
		speciesByOwner[pet->OwnerName].insert(pet->Species); // 1-�� ������ (���������� ��������� ����� �������� � ������� ���������)
		speciesByName[pet->PetName].insert(pet->Species); // 3-�� ������ (������� ����� �������� ����� ����������� ������)
		auto& Info = infoBySpecies[pet->Species]; // 2-�� � 4-�� �������
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
	bool exit = false; // ������ ������ ��� ������ � ���������
	int option; // ����� ��� ����������� int-���� ����������, ����� ������������ ��� ������� ����� �������
	while (!exit)
	{ // ����� ����-��� ��� ������������
		cout << "Please, select the query to process a number in the range 1-4 or 0 to exit:" << endl;
		cout << "1. Calculate the number of different types of animals for each owner." << endl;
		cout << "2. For a specific type of animal (entered by the user) to bring all its owners and nicknames." << endl;
		cout << "3. Determine how many species of animals bears a certain nickname (the nickname is entered by the user)." << endl;
		cout << "4. To display information about the age of the oldest and the youngest animal of each species." << endl;
		if (!(cin >> option))
		{ // ���� ������������ �� ������ �����, �� ������ ��� ������ ������
			cout << "Please type or number:" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (option < 0 || option > 4)
		{ // ���� �� ������������ ������ �����, �� �� ���, ��� �����, �� �����-���� ������ ��� ������ ������
			cout << "Please, type the correct number" << endl;
			continue;
		}
		string species; // ��� �������� �� ����
		string PetName; // ��� �������� �� ������
		tuple <set <string>, set <string>, pair <Pet*, Pet*>> answer; // ������� ������� tuple ��� ������ � map ��� �������� 2) � 4)
		pair <Pet*, Pet*> petsPair; // � ���� �������� ����� ������� ���� ������ �������� � ������ ������� ��������
		switch (option)
		{
		case 1: // ������ 1)
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
		case 2: // ������ 2)
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please type the species for which you want to get your info: ";
			getline(cin, species);
			species = LowerCase(species); // �������� � ������� ��������
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
		case 3: // ������ 3)
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
		case 4: // ������ 4)
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
		case 0: // ���� ������������ ������ �����, �� �� ������� �� �����
			exit = true;
			break;
		}
	}
	for (Pet* pet : pets)
		delete pet; // ������ ������ �� ��������� ��������
	return 0;
}