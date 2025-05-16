#include "Necromancer.h"

Necromancer::Necromancer(const char* name, unsigned health, const Position& pos, Weapon weapon, unsigned damage, const char* ability, float multiplier)
	: Mage(name, health, damage, pos, weapon, ability, multiplier) {}

void Necromancer::addPlayer(const Player& deadPlayer)
{
	deadCopies.addPlayer(deadPlayer);
}

Player* Necromancer::getRandomDeadPlayer() const
{
    return const_cast<Player*>(
        deadCopies.getSize() == 0
        ? nullptr
        : &deadCopies[rand() % deadCopies.getSize()]
        );
}
