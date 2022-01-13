
#ifndef SNAKE_PLAYER_HPP
#define SNAKE_PLAYER_HPP

#include <stdint.h>
#include <vector>

#include "snake_types.hpp"

class SnakePlayer
{
public:
    SnakePlayer(uint8_t id) : id(id){};

    void moveSnake();

    std::vector<pos_t> getSnake();

private:
    uint8_t id;
    std::vector<pos_t> snake;
    direction_e dir;
}

#endif
