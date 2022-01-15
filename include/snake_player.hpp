
#ifndef SNAKE_PLAYER_HPP
#define SNAKE_PLAYER_HPP

#include <stdint.h>
#include <list>

#include "snake_types.hpp"
#include "snake_world.hpp"

class SnakePlayer
{
  public:
    SnakePlayer(uint8_t id, SnakeBase snake, Direction m_dir, Color headColor, Color bodyColor);

    template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
    void MoveSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world);

    void UpdateDirection(Direction turn);

    uint8_t GetId();

    SnakeBase GetSnake();

  private:
    uint8_t id;
    SnakeBase snake;
    Direction m_dir;
    Color m_headColor;
    Color m_bodyColor;
};

#include "./internal/snake_player.inl"

#endif // SNAKE_PLAYER_HPP
