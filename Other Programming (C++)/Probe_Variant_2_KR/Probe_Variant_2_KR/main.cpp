#include "Footballer.h"
#include "Leased_Footballer.h"
using namespace std;

int main()
{
	try {
		Footballer** arr = new Footballer*[10];
		//string need_mag = "";
		//double mana_percent = 0.0;
		//arr[0] = new Leased_Footballer("Mag_1", Race::man, Gender::man, State::normal, 19, 100, 250, 100);
		//((Leased_Footballer*)arr[0])->SpendSomeMana(25);
		//arr[1] = new Leased_Footballer("Mag_2", Race::elf, Gender::man, State::normal, 26, 100, 350, 100);
		//((Leased_Footballer*)arr[1])->SpendSomeMana(52);
		//arr[2] = new Footballer("Ch_1", Race::gnome, Gender::woman, State::ill, 45, 100, 435);
		//arr[3] = new Leased_Footballer("Mag_3", Race::other, Gender::man, State::normal, 16, 100, 524, 100);
		//((Leased_Footballer*)arr[3])->SpendSomeMana(78);
		//arr[4] = new Leased_Footballer("Mag_4", Race::man, Gender::woman, State::normal, 35, 100, 754, 100);
		//((Leased_Footballer*)arr[4])->SpendSomeMana(92);
		//arr[5] = new Leased_Footballer("Mag_5", Race::elf, Gender::woman, State::ill, 37, 100, 364, 100);
		//((Leased_Footballer*)arr[5])->SpendSomeMana(86);
		//arr[6] = new Leased_Footballer("Mag_6", Race::gnome, Gender::man, State::normal, 27, 100, 835, 100);
		//((Leased_Footballer*)arr[6])->SpendSomeMana(11);
		//arr[7] = new Footballer("Ch_2", Race::other, Gender::man, State::normal, 22, 100, 836);
		//arr[8] = new Leased_Footballer("Mag_7", Race::elf, Gender::woman, State::poisoned, 19, 100, 839, 100);
		//((Leased_Footballer*)arr[8])->SpendSomeMana(49);
		//arr[9] = new Footballer("Ch_3", Race::man, Gender::woman, State::normal, 24, 100, 459);
		//for (int i = 0; i < 10; i++)
		//{
		//	if (typeid(*arr[i]) == typeid(Footballer))
		//		continue; // ÏÐÎÏÓÑÊÀÅÌ ÂÑÅÕ ÒÅÕ, ÊÒÎ ÍÅ ßÂËßÅÒÑß ÌÀÃÎÌ
		//	double temp = (double)((Leased_Footballer*)arr[i])->GetMana() / ((Leased_Footballer*)arr[i])->GetMax_Mana();
		//	if (temp > mana_percent)
		//	{
		//		mana_percent = temp;
		//		need_mag = arr[i]->GetName();
		//	}
		//}
		//cout << "The name of the magician with the biggest percent of mana: " << need_mag << endl;
		//cout << "He has " << mana_percent * 100 << "% of mana";
		delete[] arr;
	}
	catch (Leased_FootballerException & ex) {
		cout << "Some problem in class Leased_Footballer:" << endl;
		cout << ex.what() << endl;
	}
	catch (FootballerException & ex) {
		cout << "Some problem in classes Footballer:" << endl;
		cout << ex.what() << endl;
	}
	catch (exception & ex) {
		cout << "Some unknown problem:" << endl;
		cout << ex.what();
	}
	return 0;
}