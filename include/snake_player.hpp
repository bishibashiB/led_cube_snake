
#ifndef SNAKE_PLAYER_HPP
#define SNAKE_PLAYER_HPP

#include <stdint.h>
#include <list>

#include "snake_types.hpp"

class SnakePlayer
{
public:
    SnakePlayer(uint8_t id) : id(id){};

    void MoveSnake();

    std::list<Position> GetSnake();

private:
    uint8_t id;
    std::list<Position> snake;
    Direction dir;
};

#endif // SNAKE_PLAYER_HPP
