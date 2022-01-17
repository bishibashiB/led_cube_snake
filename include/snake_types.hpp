
#ifndef SNAKE_TYPES_HPP
#define SNAKE_TYPES_HPP

#include <Arduino.h>
#include <list>

#include "config.h"

////////////////
// World base types
////////////////

typedef uint16_t Position_type;
struct Position
{
    Position_type x;
    Position_type y;

    bool operator==(Position rhs)
    {
        return (rhs.x == x && rhs.y == y);
    }

    const bool operator==(Position rhs) const
    {
        return (rhs.x == x && rhs.y == y);
    }
};

struct SnakeBase
{
    std::list<Position> body;
    Position_type length;
};

////////////////
// Snake types
////////////////
enum class State : uint8_t
{
    Free = 0u,
    Snack,
    PlayerHead,
    PlayerBody
};
enum class Direction : uint8_t
{
    Left = 0u,
    Right,
    Down,
    Up
};

// std::string dirAsStrings[4] = {
//     "Left",
//     "Right",
//     "Down",
//     "Up"};

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
    const PanelCfg* neighbor; // 1..(TileNum_X+TileNum_Y)
    PanelSides panelSide;     // 1..4
};

// this is 4 sides of a square panel
struct NeighborsLookUp
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
    NeighborsLookUp tbl;
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

////////////////
// Adafruit Color Extension types
////////////////
struct Color
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// while player colors are received via serial interface (currently) snack and Free color are fixed
constexpr Color SNACK_COLOR = {150, 150, 150};
constexpr Color FREE_COLOR = {0, 0, 0};

#endif // SNAKE_TYPES_HPP