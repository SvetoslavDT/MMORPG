#pragma once
#include "Player.h"

class PlayerCollection : public Player
{
public :

	PlayerCollection() = default;
	explicit PlayerCollection(size_t capacity);
	~PlayerCollection();

	PlayerCollection(const PlayerCollection& other);
	PlayerCollection& operator=(const PlayerCollection& other) = delete;
	
	const Player& operator[](size_t idx) const;
	const Player& operator[](int index);

	const size_t getSize() const;

	void addPlayer(const Player& other);
	void removePlayer(const char* name);

private:

	Player** players = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};