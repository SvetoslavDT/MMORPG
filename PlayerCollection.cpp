#include "PlayerCollection.h"

PlayerCollection::PlayerCollection(size_t capacity) : size(0), capacity(capacity)
{
    players = new Player * [capacity];
}

PlayerCollection::~PlayerCollection()
{
    for (size_t i = 0; i < size; ++i)
        players[i]->freeMem();

    delete[] players;
}

PlayerCollection::PlayerCollection(const PlayerCollection& other) : size(other.size), capacity(other.capacity)
{
    players = new Player * [capacity];

    for (size_t i = 0; i < size; ++i)
    {
        try
        {
            players[i] = other.players[i]->clone();
        }
        catch (const std::exception& ex)
        {
            for (size_t j = 0; j < i; ++j)
                players[j]->freeMem();
            
            delete players;
            throw;
        }
    }
}

const Player& PlayerCollection::operator[](size_t idx) const
{
    return *players[idx];
}

const Player& PlayerCollection::operator[](int index)
{
    return *players[index];
}

const size_t PlayerCollection::getSize() const
{
    return size;
}

void PlayerCollection::addPlayer(const Player& other)
{
    if (size >= capacity) {
        const int newCap = capacity == 0 ? 8 : capacity * 1.66;
        Player** newArr = new Player * [newCap];
        capacity = newCap;
        for (int c = 0; c < size; c++) {
            newArr[c] = players[c];
        }

        delete[] players;
        players = newArr;
    }

    players[size++] = other.clone();
}

void PlayerCollection::removePlayer(const char* name) {
    for (int c = 0; c < size; c++) {
        if (strcmp(name, players[c]->getName()) == 0) {
            players[c]->freeMem();
            for (int r = c + 1; r < size; r++, c++) {
                players[c] = players[r];
            }
            --size;
        }
    }
}
