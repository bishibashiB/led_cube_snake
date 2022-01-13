

#ifndef SNAKE_PLAYER_HPP
#define SNAKE_PLAYER_HPP

#include <stdint.h>

#include "snake_types.hpp"

class SnakeWorld
{

    SnakeWorld(someConfig);

    bool isPositionFree(Pos p);

    void setPosition(Pos p);
    void resetPosition(Pos p);
}

#endif