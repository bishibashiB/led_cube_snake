
#include "snake_world.hpp"



template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIsEdgeOfPanel(const Position p)
{
    return (((p.x % Matrix_X) == 0) ||
            ((p.x % Matrix_X) == (Matrix_X - 1)) ||
            ((p.y % Matrix_Y) == 0) ||
            ((p.y % Matrix_Y) == (Matrix_Y - 1)));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge1(const MovePos f)
{
    return ((f.pos.y % Matrix_Y) == 0);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge2(const MovePos f)
{
    return ((f.pos.x % Matrix_X) == (Matrix_X - 1));
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge3(const MovePos f)
{
    return ((f.pos.y % Matrix_Y) == (Matrix_Y - 1));
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge4(const MovePos f)
{
    return ((f.pos.x % Matrix_X) == 0);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge1_AndLeaving(const MovePos f)
{
    return (posIs_Edge1(f) && f.dir == Direction::Up);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge2_AndLeaving(const MovePos f)
{
    return (posIs_Edge2(f) && f.dir == Direction::Right);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge3_AndLeaving(const MovePos f)
{
    return (posIs_Edge3(f) && f.dir == Direction::Down);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIs_Edge4_AndLeaving(const MovePos f)
{
    return (posIs_Edge4(f) && f.dir == Direction::Left);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIsEdgeOfPanelAndLeaving(const MovePos f)
{
    return posIs_Edge1_AndLeaving(f) ||
           posIs_Edge2_AndLeaving(f) ||
           posIs_Edge3_AndLeaving(f) ||
           posIs_Edge4_AndLeaving(f);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIsCornerOfPanel(const Position p)
{
    return ((((p.x % Matrix_X) == 0) && ((p.y % Matrix_Y) == 0)) ||
            (((p.x % Matrix_X) == 0) && ((p.y % Matrix_Y) == (Matrix_Y - 1))) ||
            (((p.x % Matrix_X) == (Matrix_X - 1)) && ((p.y % Matrix_Y) == 0)) ||
            (((p.x % Matrix_X) == (Matrix_X - 1)) && ((p.y % Matrix_Y) == (Matrix_Y - 1))));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::posIsCornerOfPanelAndLeaving(const MovePos f)
{
    return ((((f.pos.x % Matrix_X) == 0) && ((f.pos.y % Matrix_Y) == 0) && (f.dir == Direction::Up || f.dir == Direction::Left)) ||
            (((f.pos.x % Matrix_X) == 0) && ((f.pos.y % Matrix_Y) == (Matrix_Y - 1)) && (f.dir == Direction::Up || f.dir == Direction::Right)) ||
            (((f.pos.x % Matrix_X) == (Matrix_X - 1)) && ((f.pos.y % Matrix_Y) == 0) && (f.dir == Direction::Down || f.dir == Direction::Left)) ||
            (((f.pos.x % Matrix_X) == (Matrix_X - 1)) && ((f.pos.y % Matrix_Y) == (Matrix_Y - 1)) && (f.dir == Direction::Down || f.dir == Direction::Right)));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const PanelCfg & SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::getPanelFromPosition(const Position p)
{
    //either do a look-up through PanelArray.Position (slow, TODO) or calc idx from x-Position
    if (TileNum_Y == 1)
    {
        return cfg[p.x / Matrix_X];
    }
    else if (TileNum_X == 1)
    {
        return PanelArray[p.y / Matrix_Y];
    }
    else
    {
        Serial.print("Error getPanelFromPosition() implement me!");
        return PanelArray[0];
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const Position SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::getPosOnCurPanel(const Position p)
{
    return {p.x % Matrix_X, p.y % Matrix_Y};
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
PanelSides whichPanelSide(const MovePos f)
{
    if (posIs_Edge1_AndLeaving(f))
        return PanelSides::Side1;
    else if (posIs_Edge2_AndLeaving(f))
        return PanelSides::Side2;
    else if (posIs_Edge3_AndLeaving(f))
        return PanelSides::Side3;
    else if (posIs_Edge4_AndLeaving(f))
        return PanelSides::Side4;
    else
    {
        Serial.print("Error whichPanelSide() !");
        return PanelSides::Side4;
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
PanelSides SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::getNeigborPanelSide(const PanelSides s, const PanelCfg thisPanel)
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
        Serial.print("Error getNeigborPanelSide() !");
        return PanelSides::Side4;
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const PanelCfg * SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::getNeigborPanel(const PanelSides s, const PanelCfg thisPanel)
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
        Serial.print("Error getNeigborPanel() !");
        return &PanelArray[0];
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
MovePos SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::getNeigborPosition(const MovePos f)
{
    // prerequisite: position is 'on an edge' ... anyway
    if (!posIsEdgeOfPanelAndLeaving(f))
    {
        Serial.print("Error in getNeigborPosition() with invalid coordinates!");
        return {Direction::Down, 0, 0};
    }

    const PanelCfg &panelRef = getPanelFromPosition({f.pos.x, f.pos.y});
    const Position curPos = getPosOnCurPanel({f.pos.x, f.pos.y});
    PanelSides neighborPanelSide;
    Position_type edgeCountingPos;
    MovePos ret{f};
    const PanelCfg *neighborPanel = getNeigborPanel(whichPanelSide(f), panelRef);

    neighborPanelSide = getNeigborPanelSide(whichPanelSide(f), panelRef);

    if (PanelSides::Side1 == neighborPanelSide)
    {
        ret.dir = Direction::Down;
        // y coordinate stays '0'
        ret.y = neighborPanel->range.topLeft.y;
    }
    else if (PanelSides::Side2 == neighborPanelSide)
    {
        ret.dir = Direction::Left;
        // x coordinate stays '15'
        ret.x = neighborPanel->range.bottomRight.x;
    }
    else if (PanelSides::Side3 == neighborPanelSide)
    {
        ret.dir = Direction::Up;
        // y coordinate stays 15
        ret.y = neighborPanel->range.bottomRight.y;
    }
    else if (PanelSides::Side4 == neighborPanelSide)
    {
        ret.dir = Direction::Right;
        // x coordinate stays 0
        ret.x = neighborPanel->range.topLeft.x;
    }

    if (posIs_Edge1_AndLeaving(f) || posIs_Edge3_AndLeaving(f))
    {
        edgeCountingPos = curPos.x;
    }
    else
    {
        edgeCountingPos = curPos.y;
    }

    if (posIs_Edge1_AndLeaving(f) || posIs_Edge2_AndLeaving(f))
    {
        if (PanelSides::Side1 == neighborPanelSide)
        {
            // x row counts inverted
            ret.x = neighborPanel->range.bottomRight.x - edgeCountingPos;
        }
        if (PanelSides::Side2 == neighborPanelSide)
        {
            // counts inverted to x
            ret.y = neighborPanel->range.bottomRight.y - edgeCountingPos;
        }
        if (PanelSides::Side3 == neighborPanelSide)
        {
            // x counts with x
            ret.x = neighborPanel->range.topLeft.x + edgeCountingPos;
        }
        if (PanelSides::Side4 == neighborPanelSide)
        {
            //
            ret.y = neighborPanel->range.topLeft.y + edgeCountingPos;
        }
    }

    if (posIs_Edge3_AndLeaving(f) || posIs_Edge4_AndLeaving(f))
    {
        if (PanelSides::Side1 == neighborPanelSide)
        {
            // x row counts inverted
            ret.x = neighborPanel->range.topLeft.x + edgeCountingPos;
        }
        if (PanelSides::Side2 == neighborPanelSide)
        {
            // counts inverted to x
            ret.y = neighborPanel->range.topLeft.y + edgeCountingPos;
        }
        if (PanelSides::Side3 == neighborPanelSide)
        {
            // x counts with x
            ret.x = neighborPanel->range.bottomRight.x - edgeCountingPos;
        }
        if (PanelSides::Side4 == neighborPanelSide)
        {
            //
            ret.y = neighborPanel->range.bottomRight.y - edgeCountingPos;
        }
    }

    return ret;
}



template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::movePixel(MovePos &mp)
{

    if (!posIsEdgeOfPanelAndLeaving(mp))
    {
        if (mp.dir == Direction::Down)
            mp.y++;
        else if (mp.dir == Direction::Left)
            mp.x--;
        else if (mp.dir == Direction::Right)
            mp.x++;
        else if (mp.dir == Direction::Up)
            mp.y--;
    }
    else
    {
        mp = getNeigborPosition(mp);
    }
}