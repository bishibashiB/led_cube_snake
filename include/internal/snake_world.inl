
#include <type_traits>

#include "snake_world.hpp"


template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::SnakeWorld(const std::array<PanelCfg, tileNumX * tileNumY>& cfg,
                                                             Adafruit_NeoMatrix& matrix)
    : m_cfg(cfg)
    , m_world{State::Free}
    , m_matrix(matrix)
{
    m_matrix.fillScreen(0);
    // how about having 3 snacks?
    Position snackPos = GetFreePosition();
    SetPosition(snackPos, State::Snack, GetSnackColor());
    snackPos = GetFreePosition();
    SetPosition(snackPos, State::Snack, GetSnackColor());
    snackPos = GetFreePosition();
    SetPosition(snackPos, State::Snack, GetSnackColor());
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
State SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetPosition(Position p)
{
    return m_world[p.x][p.y];
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::SetPosition(Position p, State state, Color c)
{
    m_world[p.x][p.y] = state;
    m_matrix.drawPixel(p.x, p.y, m_matrix.Color(c.r, c.g, c.b));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::Update()
{
    // try painting pixel in SetPosition function

    // for (Position_type i; i < (matrixX * tileNumX); i++)
    // {
    //     for (Position_type j; j < (matrixY * tileNumY); j++)
    //     {
    //         m_matrix.drawPixel(x, y, m_matrix.Color(p2_r, p2_g, p2_b));
    //     }
    // }
    m_matrix.show();
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
Position SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetFreePosition()
{
    uint16_t x, y;
    Position p;

    do
    {
        x = esp_random() % (matrixX * tileNumX);
        y = esp_random() % (matrixY * tileNumY);
        p = Position{x, y};
    } while (GetPosition(p) != State::Free);
    return {x, y};
}


template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
Color SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetSnackColor()
{
    return {150, 150, 150};
}


template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
Color SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetFreeColor()
{
    return {0, 0, 0};
}


// template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
// void SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::blendPixels(byte x, byte y, uint32_t p1, uint32_t p2, byte
// iter)
// {
//     // uint16_t px = getX(x, y);
//     // uint32_t p2Is = matrix.getPixelColor(px);
//     // TODO
//     // if (p2Is == p1)
//     // {
//     //     matrix.setPixelColor(px, p1);
//     //     return;
//     // }
//     uint8_t p1_r = (p1 & 0xFE0000) >> 16, p2_r = (p2 & 0xFE0000) >> 16;
//     uint8_t p1_g = (p1 & 0xFE00) >> 8, p2_g = (p2 & 0xFE00) >> 8;
//     uint8_t p1_b = (p1 & 0xFE), p2_b = (p2 & 0xFE);
//     m_matrix.drawPixel(x, y, m_matrix.Color(p2_r, p2_g, p2_b));

//     // uint32_t np = (blendColor(p1_r, p2_r, iter) << 16) | (blendColor(p1_g, p2_g, iter) << 8) | (blendColor(p1_b,
//     // p2_b, iter));

//     // matrix.setPixelColor(px, np);
// }

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIsEdgeOfPanel(const Position p)
{
    return (((p.x % matrixX) == 0) || ((p.x % matrixX) == (matrixX - 1)) || ((p.y % matrixY) == 0)
            || ((p.y % matrixY) == (matrixY - 1)));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge1(const MovePos f)
{
    return ((f.pos.y % matrixY) == 0);
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge2(const MovePos f)
{
    return ((f.pos.x % matrixX) == (matrixX - 1));
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge3(const MovePos f)
{
    return ((f.pos.y % matrixY) == (matrixY - 1));
}
template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIs_Edge4(const MovePos f)
{
    return ((f.pos.x % matrixX) == 0);
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
    return ((((p.x % matrixX) == 0) && ((p.y % matrixY) == 0))
            || (((p.x % matrixX) == 0) && ((p.y % matrixY) == (matrixY - 1)))
            || (((p.x % matrixX) == (matrixX - 1)) && ((p.y % matrixY) == 0))
            || (((p.x % matrixX) == (matrixX - 1)) && ((p.y % matrixY) == (matrixY - 1))));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
bool SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::PosIsCornerOfPanelAndLeaving(const MovePos f)
{
    return ((((f.pos.x % matrixX) == 0) && ((f.pos.y % matrixY) == 0)
             && (f.dir == Direction::Up || f.dir == Direction::Left))
            || (((f.pos.x % matrixX) == 0) && ((f.pos.y % matrixY) == (matrixY - 1))
                && (f.dir == Direction::Up || f.dir == Direction::Right))
            || (((f.pos.x % matrixX) == (matrixX - 1)) && ((f.pos.y % matrixY) == 0)
                && (f.dir == Direction::Down || f.dir == Direction::Left))
            || (((f.pos.x % matrixX) == (matrixX - 1)) && ((f.pos.y % matrixY) == (matrixY - 1))
                && (f.dir == Direction::Down || f.dir == Direction::Right)));
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const PanelCfg& SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetPanelFromPosition(const Position p)
{
    // either do a look-up through PanelArray.Position (slow, TODO) or calc idx from x-Position
    if (tileNumY == 1)
    {
        return m_cfg[p.x / matrixX];
    }
    else if (tileNumX == 1)
    {
        return m_cfg[p.y / matrixY];
    }
    else
    {
        Serial.print("Error GetPanelFromPosition() implement me!");
        return m_cfg[0];
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
const Position SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>::GetPosOnCurPanel(const Position p)
{
    return {(Position_type)(p.x % matrixX), (Position_type)(p.y % matrixY)};
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
        return &m_cfg[0];
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