#pragma once
#include "Player.h"

class Warrior : public Player
{
public:

	Warrior(const char* name, unsigned health, const Position& pos, Weapon weapon, unsigned damage, unsigned armor);

	void handleAttack(Player& other);

private:

	unsigned armor;
};