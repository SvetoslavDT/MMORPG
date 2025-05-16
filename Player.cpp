#include "Player.h"
#include <cstring>
#include "Mage.h"
#include "Necromancer.h"
#include "Warrior.h"
#pragma warning(disable : 4996)

bool Position::operator==(const Position& pos) const
{
	return (x == pos.x) && (y == pos.y);
}

bool Position::operator!=(const Position& pos) const
{
	return !(*this == pos);
}

Position Position::abs() const
{
	return Position{std::abs(x), std::abs(y)};
}

Player::Player(const char* name, unsigned health, unsigned atack, const Position& position, Weapon weapon, PlayerType type)
	: name(nullptr), health(health), atackDamage(atack), position(position), weapon(weapon), type(type)
{
	setName(name);
}

Player::~Player()
{
	delete[] name;
}

Player::Player(const Player& other) : health(other.health), atackDamage(other.atackDamage),
									  position(other.position), weapon(other.weapon), type(other.type)
{
	setName(other.name);
}

Player& Player::operator=(const Player& other)
{
	if (this != &other)
	{
		setName(other.name);
		health = other.health;
		atackDamage = other.atackDamage;
		position = other.position;
		weapon = other.weapon;
		type = other.type;
	}
	return *this;
}

const char* Player::getName() const
{
	return name;
}

const unsigned Player::getHealth() const
{
	return health;
}

const unsigned Player::getAtackDamage() const
{
	return atackDamage;
}

const Position& Player::getPosition() const
{
	return position;
}

const Weapon Player::getWeapon() const
{
	return weapon;
}

const PlayerType Player::getType() const
{
	return type;
}

bool Player::isDead() const
{
	return health == 0;
}

void Player::setName(const char* name)
{
	if (!name)
		throw std::logic_error("Empty Player name!");

	char* newName = new char[strlen(name) + 1];
	strcpy(newName, name);

	delete[] this->name;
	this->name = newName;
}

void Player::setHealth(unsigned health)
{
	this->health = health;
}

void Player::setAtckDamage(unsigned atackDmg)
{
	this->atackDamage = atackDmg;
}

void Player::setPosition(const Position& pos)
{
	this->position = pos;
}

void Player::setWeapon(const Weapon& weapon)
{
	this->weapon = weapon;
}

void Player::setType(const PlayerType& type)
{
	this->type = type;
}

void Player::move(const Position& pos)
{
	position = pos;
}

void Player::handleAtack(const Player& other)
{
	if ((this->position - other.position).abs() != Position{1, 1})
		return;

	if (other.type == PlayerType::Mage) {
		health *= static_cast<const Mage&>(other).getAttackMultiplier();
	}

	if (other.atackDamage >= health) {
		health = 0;
	}
	else {
		health -= other.atackDamage;
	}

	const bool isNecromancer = other.getType() == PlayerType::Necromancer;
	
	Necromancer* necro = isNecromancer ? static_cast<Necromancer*>(const_cast<Player*>(&other)) : nullptr;
	//?? Not sure if this is ok

	if (other.getAtackDamage() >= health) {
		health = 0;
		if (necro) {
			necro->addPlayer(*this);
		}
		return;
	}
	else {
		health -= other.getAtackDamage();
	}

	Player* otherAttacker = necro->getRandomDeadPlayer();
	if (otherAttacker) {
		if (type == PlayerType::Warrior) {
			static_cast<Warrior*>(this)->handleAttack(*otherAttacker);
		}
		else {
			handleAtack(*otherAttacker);
		}
	}
}

void Player::print() const
{
	std::cout << *this;
}

void Player::swap(Player& other)
{
	std::swap(type, other.type);
	std::swap(name, other.name);
	std::swap(health, other.health);
	std::swap(position, other.position);
	std::swap(weapon, other.weapon);
	std::swap(atackDamage, other.atackDamage);
}

Player* Player::clone() const
{
	switch (type) {
	case PlayerType::Mage:
		return new Mage(static_cast<const Mage&>(*this));
	case PlayerType::Warrior:
		return new Warrior(static_cast<const Warrior&>(*this));
	case PlayerType::Necromancer:
		return new Necromancer(static_cast<const Necromancer&>(*this));
	}
}

void Player::freeMem() {
	switch (type) {
	case PlayerType::Player:
		delete static_cast<Player*>(this);
		break;
	case PlayerType::Necromancer:
		delete static_cast<Necromancer*>(this);
		break;
	case PlayerType::Mage:
		delete static_cast<Mage*>(this);
		break;
	case PlayerType::Warrior:
		delete static_cast<Warrior*>(this);
		break;
	}
}

Position operator-(const Position& lhs, const Position& rhs)
{
	return Position{ lhs.x - rhs.x, lhs.y - rhs.y };
}

std::ostream& operator<<(std::ostream& os, const Position& pos)
{
	return os << pos.x << " " << pos.y;
}

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << player.getName() << " " << player.getHealth() << " " <<
		player.getAtackDamage() << " " << player.getPosition();
}