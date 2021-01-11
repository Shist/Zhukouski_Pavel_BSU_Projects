#include "Magic.h"

#pragma warning (disable : 4996)

using namespace std;

Magic::Magic(string aname, Race arace, Gender agender, State astate = State::normal,
	int anage = 0, int ahealth = 0, int askill = 0, int amana = 0)
	:Game(aname, arace, agender, astate, anage, ahealth, askill), mana(amana), MAX_mana(mana) {
	if (amana < 0)
		throw MagicException("We can't have mana < 0");
}

Magic::~Magic() {}




int Magic::GetMana() {
	return mana;
}