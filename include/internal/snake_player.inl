

#include "snake_player.hpp"

SnakePlayer::SnakePlayer(uint8_t id, SnakeBase snake, Direction m_dir)
    : id(id)
    , snake(snake)
    , m_dir(m_dir)
{
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::MoveSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    // old head
    world.SetPosition(snake.body.front(), State::PlayerBody);

    // new head
    MovePos fromPos{m_dir, snake.body.front()};
    world.MovePixel(fromPos);
    if (world.GetPosition(snake.body.front()) == State::Snack)
    {
        snake.length++;
        world.SetPosition(world.GetFreePosition(), State::Snack);
    }
    snake.body.push_front(snake.body.front());
    world.SetPosition(snake.body.front(), State::PlayerHead);

    // old tail
    if (snake.body.size() >= snake.length)
    {
        world.SetPosition(snake.body.back(), State::Free);
        snake.body.pop_back();
    }
}

uint8_t SnakePlayer::GetId()
{
    return id;
}

SnakeBase SnakePlayer::GetSnake()
{
    return snake;
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