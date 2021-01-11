#include <iostream>
#include <exception>
#include <string>
#include "Game.h"
#include "Magic.h"
#pragma warning (disable : 4996)

using namespace std;
int main() {
	try {
		Game Dmitriy("Dmitriy", Race::elf, Gender::man, State::normal, 17, 200, 0);
		cout << Dmitriy;
		Game Dmitriy2("Dmitriy", Race::elf, Gender::man, State::normal, 17, 200, 0);

		//Dmitriy.ChangeAgeTo(-12);

		Magic Dmitriy1("Dmitriy", Race::elf, Gender::man, State::normal, 17, 200, 0, -80);

		cout << Dmitriy.CompareSkill("=", Dmitriy1);
	}
	catch (GameException & ex) {
		cout << "Something is wrong:" << endl;
		cout << ex.what() << endl;
	}
	catch (MagicException & ex) {
		cout << "Something is wrong in magic:" << endl;
		cout << ex.what() << endl;
	}
	catch (exception & ex) {
		cout << "Something strange: " << endl;
		cout << ex.what();
	}


}