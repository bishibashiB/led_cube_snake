

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <stdint.h>
#include <vector>

#include "snake_world.hpp"
#include "snake_player.hpp"

class SnakeGame
{
public:
    template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
    SnakeGame(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY> &world);

    void addPlayer(uint8_t id);
    void removePlayer(uint8_t id);

    void changePlayerDirection(Direction d);

    // 1) Player::moveSnake
    // 2) build new world Player::getSnake
    // 3) check collision (self / inter-players)
    // 4) deconstruct game-over players (remove from vector)
    void iterateWorld();

private:
    // (self / inter-players), also directly removes game-over player
    void checkCollision();
    std::vector<SnakePlayer> m_players;
    // World image class
    template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
    SnakeWorld<matrixX, matrixY, tileNumX, tileNumY> &m_world;
};

#endif
