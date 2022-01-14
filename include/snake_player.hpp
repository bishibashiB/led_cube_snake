
#ifndef SNAKE_PLAYER_HPP
#define SNAKE_PLAYER_HPP

#include <stdint.h>
#include <list>

#include "snake_types.hpp"
#include "snake_world.hpp"

class SnakePlayer
{
  public:
    SnakePlayer(uint8_t id, SnakeBase snake, Direction dir);

    template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
    void MoveSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world);

    void UpdateDirection(Direction turn);

  private:
    uint8_t id;
    SnakeBase snake;
    Direction dir;
};

#endif // SNAKE_PLAYER_HPP
