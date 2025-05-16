#pragma once
#include <iostream>

enum class Weapon : unsigned char
{
	Sword, Wand, Staff, Axe
};

enum class PlayerType : unsigned char
{
	Player, Mage, Warrior, Necromancer
};

struct Position
{
	int x;
	int y;

	bool operator==(const Position& pos) const;
	bool operator!=(const Position& pos) const;

	Position abs() const;
};

Position operator-(const Position& lhs, const Position& rhs);
std::ostream& operator<<(std::ostream& os, const Position& pos);

class Player
{
public:

	Player() = default;
	Player(const char* name, unsigned health, unsigned atack, const Position& position, Weapon weapon, PlayerType type);
	~Player();

	Player(const Player& other);
	Player& operator=(const Player& other);

	const char* getName() const;
	const unsigned getHealth() const;
	const unsigned getAtackDamage() const;
	const Position& getPosition() const;
	const Weapon getWeapon() const;
	const PlayerType getType() const;

	bool isDead() const;

	void setHealth(unsigned health);
	void setAtckDamage(unsigned atackDmg);
	void setPosition(const Position& pos);
	void setWeapon(const Weapon& weapon);
	void setType(const PlayerType& type);

	void move(const Position& pos);
	void handleAtack(const Player& player);
	void print() const;

	void swap(Player& other);
	Player* clone() const;
	void freeMem();

protected:

	PlayerType type;
	Weapon weapon;
	char* name = nullptr;
	unsigned health;
	unsigned atackDamage;
	Position position;

	void setName(const char* name);
};

std::ostream& operator<<(std::ostream& os, const Player& player);