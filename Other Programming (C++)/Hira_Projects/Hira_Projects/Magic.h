#pragma once
#include "Game.h"
class Magic :
	public Game
{
private:
	int mana;
	int MAX_mana;
public:
	Magic(string, Race, Gender, State, int, int, int, int);
	virtual ~Magic();

	int GetMana();
};
class MagicException
	: public GameException {
public:
	MagicException(const char* message)
		: GameException(message) {}
};
