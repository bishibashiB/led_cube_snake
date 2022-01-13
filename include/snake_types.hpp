
#ifndef SNAKE_TYPES_HPP
#define SNAKE_TYPES_HPP

#include <Arduino.h>
#include "config.h"

////////////////
// World base types
////////////////

typedef uint16_t Position_type;
struct Position
{
    Position_type x;
    Position_type y;
};

////////////////
// Snake types
////////////////
enum class State : uint8_t
{
    Free = 0u,
    Food,
    PlayerHead,
    PlayerBody
};
enum class Direction : uint8_t
{
    dirLeft = 0u,
    dirRight,
    dirDown,
    dirUp
};
struct MovePos
{
    Direction dir;
    Position pos;
};

////////////////
// World / LedPanel types
////////////////

// fwd declaration
struct PanelCfg;

enum class PanelSides : uint8_t
{
    // counted clockwise starting from (0,0)-position
    Side1 = 1,
    Side2,
    Side3,
    Side4
};
struct PanelSide
{
    const PanelCfg *neighbor; // 1..(TileNum_X+TileNum_Y)
    PanelSides panelSide;     // 1..4
};

// this is 4 sides of a square panel
struct NeighborsTable
{
    PanelSide fromSide1;
    PanelSide fromSide2;
    PanelSide fromSide3;
    PanelSide fromSide4;
};

// this is a helping struct to define a 2d-pixel address range matching to one of the used panels
struct PanelRange
{
    Position topLeft;
    Position bottomRight;
};

struct PanelCfg
{
    NeighborsTable tbl;
    PanelRange range;
};

////////////////
// Serial com types
////////////////

enum class SerialCmd : uint8_t
{
    ADD_PLAYER = 1,     // "1Byte number / ID,  2x3Byte color head / body "
    REMOVE_PLAYER = 2,  // "1Byte number/ID"
    ITERATE_STEP = 3,   // "0Byte, ... all players"
    DIR_CMD_PLAYER = 4, // "1Byte number/ID, 1Byte NEW rel. direction ('r', 'l')"
};

#endif // SNAKE_TYPES_HPP