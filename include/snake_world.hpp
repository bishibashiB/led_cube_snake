

#ifndef SNAKE_WORLD_HPP
#define SNAKE_WORLD_HPP

#include <stdint.h>

#include "snake_types.hpp"

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
class SnakeWorld
{
public:
    SnakeWorld(std::array<PanelCfg, tileNumX * tileNumY> cfg);

    bool isPositionFree(Pos p);

    void setPosition(Pos p);
    void resetPosition(Pos p);
};

#endif // SNAKE_WORLD_HPP