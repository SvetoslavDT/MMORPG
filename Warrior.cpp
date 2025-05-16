#include "Warrior.h"
#include "Mage.h"
#include "Necromancer.h"

Warrior::Warrior(const char* name, unsigned health, const Position& pos, Weapon weapon, unsigned damage, unsigned armor)
	: Player(name, health, damage, pos, weapon, PlayerType::Warrior), armor(armor) {}

void Warrior::handleAttack(Player& other)
{
	if ((this->position - other.getPosition()).abs() != Position{ 1, 1 })
		return;

    if (other.getType() == PlayerType::Mage)
        health *= static_cast<const Mage&>(other).getAttackMultiplier();

    unsigned attackPower = other.getAtackDamage();
    if (attackPower >= armor) {
        attackPower -= armor;
        armor = 0;
    }
    else {
        armor -= attackPower;
        return;
    }
    const bool isNecromancer = other.getType() == PlayerType::Necromancer;
    Necromancer* necro = isNecromancer ? static_cast<Necromancer*>(&other) : nullptr;

    if (attackPower >= health) {
        health = 0;
        if (necro) {
            necro->addPlayer(*this);
        }
        return;
    }
    else {
        health -= attackPower;
    }

    Player* otherAttacker = necro->getRandomDeadPlayer();
    if (otherAttacker) {
        handleAttack(*otherAttacker);
    }
}
