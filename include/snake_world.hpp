

#ifndef SNAKE_WORLD_HPP
#define SNAKE_WORLD_HPP

#include <stdint.h>
#include <array>

#include "snake_types.hpp"

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
class SnakeWorld
{
public:
    SnakeWorld(const std::array<PanelCfg, tileNumX * tileNumY> &cfg);

    bool isPositionFree(Position p);

    void setPosition(Position p);
    void resetPosition(Position p);

    bool posIsEdgeOfPanel(const Position p);

    inline bool posIs_Edge1(const MovePos f);
    inline bool posIs_Edge2(const MovePos f);
    inline bool posIs_Edge3(const MovePos f);
    inline bool posIs_Edge4(const MovePos f);

    inline bool posIs_Edge1_AndLeaving(const MovePos f);
    inline bool posIs_Edge2_AndLeaving(const MovePos f);
    inline bool posIs_Edge3_AndLeaving(const MovePos f);
    inline bool posIs_Edge4_AndLeaving(const MovePos f);
    inline bool posIsEdgeOfPanelAndLeaving(const MovePos f);
    bool posIsCornerOfPanel(const Position p);
    bool posIsCornerOfPanelAndLeaving(const MovePos f);
    const PanelCfg &getPanelFromPosition(const Position p);
    const Position getPosOnCurPanel(const Position p);
    PanelSides whichPanelSide(const MovePos f);
    PanelSides getNeigborPanelSide(const PanelSides s, const PanelCfg thisPanel);

    const PanelCfg *getNeigborPanel(const PanelSides s, const PanelCfg thisPanel);

    MovePos getNeigborPosition(const MovePos f);

    void movePixel(MovePos &mp);

private:
    std::array<PanelCfg, tileNumX * tileNumY> &cfg;
};

#endif // SNAKE_WORLD_HPP