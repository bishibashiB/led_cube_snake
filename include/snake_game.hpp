

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <stdint.h>
#include <vector>

#include "snake_world.hpp"
#include "snake_player.hpp"

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
class SnakeGame
{
  public:
    SnakeGame(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world);

    void AddPlayer(uint8_t id);
    void RemovePlayer(uint8_t id);

    void ChangePlayerDirection(uint8_t id, Direction d);

    // 1) Player::moveSnake
    // 2) build new world Player::getSnake
    // 3) check collision (self / inter-players)
    // 4) deconstruct game-over players (remove from vector)
    void IterateWorld();

  private:
    // (self / inter-players), also directly removes game-over player
    void CheckCollision();
    std::vector<SnakePlayer> m_players;
    // World image class
    SnakeWorld<matrixX, matrixY, tileNumX, tileNumY> m_world;
};

#endif
