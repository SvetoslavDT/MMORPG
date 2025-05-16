#pragma once
#include "Player.h"

class Mage : public Player
{
public:

	Mage(const char* name, unsigned health, unsigned atack, const Position& position, Weapon weapon, const char* ability, float multiplier);
	Mage(const Mage& other);
	Mage& operator=(const Mage& other);
	~Mage();

	float getAttackMultiplier() const;

	void setAbility(const char* ability);

	void swap(Mage& other);


private:

	char* ability = nullptr;
	float attackMultiplier;
};