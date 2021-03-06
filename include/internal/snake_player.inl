
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
        world.SetPosition(snackPos, State::Snack, SNACK_COLOR);
    }

    m_snake.body.push_front(movedPixel.pos);
    m_dir = movedPixel.dir;
    world.SetPosition(m_snake.body.front(), State::PlayerHead, m_headColor);


    // old tail
    if (m_snake.body.size() > m_snake.length)
    {
        // already other head moved there (legal free space)
        if (world.GetPosition(m_snake.body.back()) != State::PlayerHead)
        {
            world.SetPosition(m_snake.body.back(), State::Free, FREE_COLOR);
        }
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
void SnakePlayer::RedrawSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    world.SetPosition(m_snake.body.front(), State::PlayerHead, m_headColor);
    for (auto iter = m_snake.body.begin()++; iter != m_snake.body.end(); iter++)
    {
        world.SetPosition(*iter, State::PlayerBody, m_bodyColor);
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::RemoveDisplay(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    for (Position& pos : m_snake.body)
    {
        world.SetPosition(pos, State::Free, FREE_COLOR);
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::RemoveDisplayWithoutHead(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    // in case of snake2body collision do not make a whole in the other snake
    for (Position& pos : m_snake.body)
    {
        if (pos == m_snake.body.front())
            continue;
        world.SetPosition(pos, State::Free, FREE_COLOR);
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