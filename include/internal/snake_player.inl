

#include "snake_player.hpp"

SnakePlayer::SnakePlayer(uint8_t id, SnakeBase snake, Direction dir, Color headColor, Color bodyColor)
    : m_id(id)
    , m_snake(snake)
    , m_dir(dir)
    , m_headColor(headColor)
    , m_bodyColor(bodyColor)
{
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::MoveSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    // old head
    world.SetPosition(m_snake.body.front(), State::PlayerBody, m_bodyColor);

    // new head
    MovePos movedPixel{m_dir, m_snake.body.front()};
    world.MovePixel(movedPixel);
    if (world.GetPosition(movedPixel.pos) == State::Snack)
    {
        m_snake.length++;
        Position snackPos;
        do
        {
            snackPos = world.GetFreePosition();
        } while (snackPos.x == movedPixel.pos.x && snackPos.y == movedPixel.pos.y);
        world.SetPosition(snackPos, State::Snack, world.GetSnackColor());
    }
    m_snake.body.push_front(movedPixel.pos);
    world.SetPosition(m_snake.body.front(), State::PlayerHead, m_headColor);

    // old tail
    if (m_snake.body.size() > m_snake.length)
    {
        world.SetPosition(m_snake.body.back(), State::Free, world.GetFreeColor());
        m_snake.body.pop_back();
    }
}

uint8_t SnakePlayer::GetId()
{
    return m_id;
}

SnakeBase& SnakePlayer::GetSnake()
{
    return m_snake;
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::RemoveDisplay(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    for (Position& pos : m_snake.body)
    {
        world.SetPosition(pos, State::Free, world.GetFreeColor());
    }
}

void SnakePlayer::UpdateDirection(Direction turn)
{
    Direction retDir = m_dir;
    // only using left and right to alter RELATIVE direction of movement (up / down will just advance in 'relative
    // forward direction')
    if ((m_dir == Direction::Up) && (turn == Direction::Left))
    {
        retDir = Direction::Left;
    }
    else if ((m_dir == Direction::Up) && (turn == Direction::Right))
    {
        retDir = Direction::Right;
    }
    else if ((m_dir == Direction::Down) && (turn == Direction::Left))
    {
        retDir = Direction::Right;
    }
    else if ((m_dir == Direction::Down) && (turn == Direction::Right))
    {
        retDir = Direction::Left;
    }
    else if ((m_dir == Direction::Left) && (turn == Direction::Left))
    {
        retDir = Direction::Down;
    }
    else if ((m_dir == Direction::Left) && (turn == Direction::Right))
    {
        retDir = Direction::Up;
    }
    else if ((m_dir == Direction::Right) && (turn == Direction::Left))
    {
        retDir = Direction::Up;
    }
    else if ((m_dir == Direction::Right) && (turn == Direction::Right))
    {
        retDir = Direction::Down;
    }

    m_dir = retDir;
}