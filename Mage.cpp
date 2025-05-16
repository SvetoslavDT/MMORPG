#include "Mage.h"
#include <string>
#pragma warning(disable : 4996)

Mage::Mage(const char* name, unsigned health, unsigned atack, const Position& pos, Weapon weapon, const char* ability, float multiplier)
	: Player(name, health, atack, pos, weapon, PlayerType::Warrior), ability(nullptr), attackMultiplier(multiplier) 
{
	if (multiplier >= 1 || multiplier <= 0) {
		throw std::logic_error("Mage multiplier must be in (0, 1)");
	}

	setAbility(ability);
}

Mage::Mage(const Mage& other) : Player(other), attackMultiplier(other.attackMultiplier)
{
	setAbility(other.ability);
}

Mage& Mage::operator=(const Mage& other)
{
	if (this != &other)
	{
		Mage copy(other);
		swap(copy);
	}
	return *this;
}

Mage::~Mage()
{
	delete[] ability;
}

float Mage::getAttackMultiplier() const
{
	return attackMultiplier;
}

void Mage::setAbility(const char* ability)
{
	if(!ability)
		throw std::logic_error("Empty Player Ability");

	char* newAbility = new char[strlen(ability) + 1];
	strcpy(newAbility, ability);

	delete[] this->ability;
	this->ability = newAbility;
}

void Mage::swap(Mage& other)
{
	Player::swap(other);
	std::swap(ability, other.ability);
	std::swap(attackMultiplier, other.attackMultiplier);
}