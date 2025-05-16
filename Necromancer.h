#pragma once
#include "Player.h"
#include "PlayerCollection.h"
#include "Mage.h"

class Necromancer : public Mage
{
public:

	Necromancer(const char* name, unsigned health, const Position& pos, Weapon weapon, unsigned damage, const char* ability, float multiplier);

	void addPlayer(const Player& deadPlayer);
	Player* getRandomDeadPlayer() const;

private:

	PlayerCollection deadCopies;

};