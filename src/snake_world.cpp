

#include "snake_world.hpp"


template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::SnakeWorld(const std::array<PanelCfg, tileNumX * tileNumY>& cfg)
    : cfg(cfg)
{
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
State SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetPosition(Position p)
{
    return m_world[p.x][p.y];
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::SetPosition(Position p, State state)
{
    m_world[p.x][p.y] = state;
}


template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIsEdgeOfPanel(const Position p)
{
    return (((p.x % Matrix_X) == 0) || ((p.x % Matrix_X) == (Matrix_X - 1)) || ((p.y % Matrix_Y) == 0)
            || ((p.y % Matrix_Y) == (Matrix_Y - 1)));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge1(const MovePos f)
{
    return ((f.pos.y % Matrix_Y) == 0);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge2(const MovePos f)
{
    return ((f.pos.x % Matrix_X) == (Matrix_X - 1));
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge3(const MovePos f)
{
    return ((f.pos.y % Matrix_Y) == (Matrix_Y - 1));
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge4(const MovePos f)
{
    return ((f.pos.x % Matrix_X) == 0);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge1_AndLeaving(const MovePos f)
{
    return (PosIs_Edge1(f) && f.dir == Direction::Up);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge2_AndLeaving(const MovePos f)
{
    return (PosIs_Edge2(f) && f.dir == Direction::Right);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge3_AndLeaving(const MovePos f)
{
    return (PosIs_Edge3(f) && f.dir == Direction::Down);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge4_AndLeaving(const MovePos f)
{
    return (PosIs_Edge4(f) && f.dir == Direction::Left);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIsEdgeOfPanelAndLeaving(const MovePos f)
{
    return PosIs_Edge1_AndLeaving(f) || PosIs_Edge2_AndLeaving(f) || PosIs_Edge3_AndLeaving(f)
           || PosIs_Edge4_AndLeaving(f);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIsCornerOfPanel(const Position p)
{
    return ((((p.x % Matrix_X) == 0) && ((p.y % Matrix_Y) == 0))
            || (((p.x % Matrix_X) == 0) && ((p.y % Matrix_Y) == (Matrix_Y - 1)))
            || (((p.x % Matrix_X) == (Matrix_X - 1)) && ((p.y % Matrix_Y) == 0))
            || (((p.x % Matrix_X) == (Matrix_X - 1)) && ((p.y % Matrix_Y) == (Matrix_Y - 1))));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIsCornerOfPanelAndLeaving(const MovePos f)
{
    return ((((f.pos.x % Matrix_X) == 0) && ((f.pos.y % Matrix_Y) == 0)
             && (f.dir == Direction::Up || f.dir == Direction::Left))
            || (((f.pos.x % Matrix_X) == 0) && ((f.pos.y % Matrix_Y) == (Matrix_Y - 1))
                && (f.dir == Direction::Up || f.dir == Direction::Right))
            || (((f.pos.x % Matrix_X) == (Matrix_X - 1)) && ((f.pos.y % Matrix_Y) == 0)
                && (f.dir == Direction::Down || f.dir == Direction::Left))
            || (((f.pos.x % Matrix_X) == (Matrix_X - 1)) && ((f.pos.y % Matrix_Y) == (Matrix_Y - 1))
                && (f.dir == Direction::Down || f.dir == Direction::Right)));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const PanelCfg& SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetPanelFromPosition(const Position p)
{
    // either do a look-up through PanelArray.Position (slow, TODO) or calc idx from x-Position
    if (TileNum_Y == 1)
    {
        return cfg[p.x / Matrix_X];
    }
    else if (TileNum_X == 1)
    {
        return cfg[p.y / Matrix_Y];
    }
    else
    {
        Serial.print("Error GetPanelFromPosition() implement me!");
        return cfg[0];
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const Position SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetPosOnCurPanel(const Position p)
{
    return {p.x % Matrix_X, p.y % Matrix_Y};
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
PanelSides SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::WhichPanelSide(const MovePos f)
{
    if (PosIs_Edge1_AndLeaving(f))
        return PanelSides::Side1;
    else if (PosIs_Edge2_AndLeaving(f))
        return PanelSides::Side2;
    else if (PosIs_Edge3_AndLeaving(f))
        return PanelSides::Side3;
    else if (PosIs_Edge4_AndLeaving(f))
        return PanelSides::Side4;
    else
    {
        Serial.print("Error WhichPanelSide() !");
        return PanelSides::Side4;
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
PanelSides SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetNeigborPanelSide(const PanelSides s,
                                                                                 const PanelCfg thisPanel)
{
    if (s == PanelSides::Side1)
        return thisPanel.tbl.fromSide1.panelSide;
    if (s == PanelSides::Side2)
        return thisPanel.tbl.fromSide2.panelSide;
    if (s == PanelSides::Side3)
        return thisPanel.tbl.fromSide3.panelSide;
    if (s == PanelSides::Side4)
        return thisPanel.tbl.fromSide4.panelSide;
    else
    {
        Serial.print("Error GetNeigborPanelSide() !");
        return PanelSides::Side4;
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const PanelCfg* SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetNeigborPanel(const PanelSides s,
                                                                                  const PanelCfg thisPanel)
{
    if (s == PanelSides::Side1)
        return thisPanel.tbl.fromSide1.neighbor;
    if (s == PanelSides::Side2)
        return thisPanel.tbl.fromSide2.neighbor;
    if (s == PanelSides::Side3)
        return thisPanel.tbl.fromSide3.neighbor;
    if (s == PanelSides::Side4)
        return thisPanel.tbl.fromSide4.neighbor;
    else
    {
        Serial.print("Error GetNeigborPanel() !");
        return &cfg[0];
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
MovePos SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetNeigborPosition(const MovePos f)
{
    // prerequisite: position is 'on an edge' ... anyway
    if (!PosIsEdgeOfPanelAndLeaving(f))
    {
        Serial.print("Error in GetNeigborPosition() with invalid coordinates!");
        return {Direction::Down, 0, 0};
    }

    const PanelCfg& panelRef = GetPanelFromPosition({f.pos.x, f.pos.y});
    const Position curPos = GetPosOnCurPanel({f.pos.x, f.pos.y});
    PanelSides neighborPanelSide;
    Position_type edgeCountingPos;
    MovePos ret{f};
    const PanelCfg* neighborPanel = GetNeigborPanel(WhichPanelSide(f), panelRef);

    neighborPanelSide = GetNeigborPanelSide(WhichPanelSide(f), panelRef);

    if (PanelSides::Side1 == neighborPanelSide)
    {
        ret.dir = Direction::Down;
        // y coordinate stays '0'
        ret.pos.y = neighborPanel->range.topLeft.y;
    }
    else if (PanelSides::Side2 == neighborPanelSide)
    {
        ret.dir = Direction::Left;
        // x coordinate stays '15'
        ret.pos.x = neighborPanel->range.bottomRight.x;
    }
    else if (PanelSides::Side3 == neighborPanelSide)
    {
        ret.dir = Direction::Up;
        // y coordinate stays 15
        ret.pos.y = neighborPanel->range.bottomRight.y;
    }
    else if (PanelSides::Side4 == neighborPanelSide)
    {
        ret.dir = Direction::Right;
        // x coordinate stays 0
        ret.pos.x = neighborPanel->range.topLeft.x;
    }

    if (PosIs_Edge1_AndLeaving(f) || PosIs_Edge3_AndLeaving(f))
    {
        edgeCountingPos = curPos.x;
    }
    else
    {
        edgeCountingPos = curPos.y;
    }

    if (PosIs_Edge1_AndLeaving(f) || PosIs_Edge2_AndLeaving(f))
    {
        if (PanelSides::Side1 == neighborPanelSide)
        {
            // x row counts inverted
            ret.pos.x = neighborPanel->range.bottomRight.x - edgeCountingPos;
        }
        if (PanelSides::Side2 == neighborPanelSide)
        {
            // counts inverted to x
            ret.pos.y = neighborPanel->range.bottomRight.y - edgeCountingPos;
        }
        if (PanelSides::Side3 == neighborPanelSide)
        {
            // x counts with x
            ret.pos.x = neighborPanel->range.topLeft.x + edgeCountingPos;
        }
        if (PanelSides::Side4 == neighborPanelSide)
        {
            //
            ret.pos.y = neighborPanel->range.topLeft.y + edgeCountingPos;
        }
    }

    if (PosIs_Edge3_AndLeaving(f) || PosIs_Edge4_AndLeaving(f))
    {
        if (PanelSides::Side1 == neighborPanelSide)
        {
            // x row counts inverted
            ret.pos.x = neighborPanel->range.topLeft.x + edgeCountingPos;
        }
        if (PanelSides::Side2 == neighborPanelSide)
        {
            // counts inverted to x
            ret.pos.y = neighborPanel->range.topLeft.y + edgeCountingPos;
        }
        if (PanelSides::Side3 == neighborPanelSide)
        {
            // x counts with x
            ret.pos.x = neighborPanel->range.bottomRight.x - edgeCountingPos;
        }
        if (PanelSides::Side4 == neighborPanelSide)
        {
            //
            ret.pos.y = neighborPanel->range.bottomRight.y - edgeCountingPos;
        }
    }

    return ret;
}


template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::MovePixel(MovePos& mp)
{
    if (!PosIsEdgeOfPanelAndLeaving(mp))
    {
        if (mp.dir == Direction::Down)
            mp.pos.y++;
        else if (mp.dir == Direction::Left)
            mp.pos.x--;
        else if (mp.dir == Direction::Right)
            mp.pos.x++;
        else if (mp.dir == Direction::Up)
            mp.pos.y--;
    }
    else
    {
        mp = GetNeigborPosition(mp);
    }
}