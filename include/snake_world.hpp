

#ifndef SNAKE_WORLD_HPP
#define SNAKE_WORLD_HPP

#include <stdint.h>
#include <array>

#include "snake_types.hpp"

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
class SnakeWorld
{
  public:
    SnakeWorld(const std::array<PanelCfg, tileNumX * tileNumY>& cfg);

    State GetPosition(Position p);

    void SetPosition(Position p, State state);

    bool PosIsEdgeOfPanel(const Position p);

    inline bool PosIs_Edge1(const MovePos f);
    inline bool PosIs_Edge2(const MovePos f);
    inline bool PosIs_Edge3(const MovePos f);
    inline bool PosIs_Edge4(const MovePos f);

    inline bool PosIs_Edge1_AndLeaving(const MovePos f);
    inline bool PosIs_Edge2_AndLeaving(const MovePos f);
    inline bool PosIs_Edge3_AndLeaving(const MovePos f);
    inline bool PosIs_Edge4_AndLeaving(const MovePos f);
    inline bool PosIsEdgeOfPanelAndLeaving(const MovePos f);
    bool PosIsCornerOfPanel(const Position p);
    bool PosIsCornerOfPanelAndLeaving(const MovePos f);
    const PanelCfg& GetPanelFromPosition(const Position p);
    const Position GetPosOnCurPanel(const Position p);
    PanelSides WhichPanelSide(const MovePos f);
    PanelSides GetNeigborPanelSide(const PanelSides s, const PanelCfg thisPanel);

    const PanelCfg* GetNeigborPanel(const PanelSides s, const PanelCfg thisPanel);

    MovePos GetNeigborPosition(const MovePos f);

    void MovePixel(MovePos& mp);

  private:
    std::array<PanelCfg, tileNumX * tileNumY>& cfg;
    State m_world[matrixX * tileNumX][matrixY * tileNumY];
    State m_newWorld[matrixX * tileNumX][matrixY * tileNumY];
};

#endif // SNAKE_WORLD_HPP