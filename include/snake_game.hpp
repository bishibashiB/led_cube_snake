

#ifndef SNAKE_GAME_HPP
#define SNAKE_GAME_HPP

#include <vector>

#include "snake_player.hpp"

class SnakeGame
{
    SnakeGame();

    void addPlayer(uint8_t id);
    void removePlayer(uint8_t id);

    void changePlayerDirection();

    // 1) Player::moveSnake
    // 2) build new world Player::getSnake
    // 3) check collision (self / inter-players)
    // 4) deconstruct game-over players (remove from vector)
    void iterateWorld();

private:
    // also directly removes game-over player
    void checkCollision();

    std::vector<SnakePlayer> m_players;
    // World image class
}

#endif
