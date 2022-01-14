

#include "snake_player.hpp"

SnakePlayer::SnakePlayer(uint8_t id)
    : id(id)
{
    // set random start position ... which is unused
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::MoveSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    snake.pop_back();
    MovePos mp{dir, snake.front()};
    Position newPos = world.movePixel(mp);
    snake.push_front(snake.front());
}

std::list<Position> SnakePlayer::GetSnake()
{
    return snake;
}

void SnakePlayer::UpdateDirection(Direction turn)
{
    Direction retDir = dir;
    // only using left and right to alter RELATIVE direction of movement (up / down will just advance in 'relative
    // forward direction')
    if ((dir == Direction::Up) && (turn == Direction::Left))
    {
        retDir = Direction::Left;
    }
    else if ((dir == Direction::Up) && (turn == Direction::Right))
    {
        retDir = Direction::Right;
    }
    else if ((dir == Direction::Down) && (turn == Direction::Left))
    {
        retDir = Direction::Right;
    }
    else if ((dir == Direction::Down) && (turn == Direction::Right))
    {
        retDir = Direction::Left;
    }
    else if ((dir == Direction::Left) && (turn == Direction::Left))
    {
        retDir = Direction::Down;
    }
    else if ((dir == Direction::Left) && (turn == Direction::Right))
    {
        retDir = Direction::Up;
    }
    else if ((dir == Direction::Right) && (turn == Direction::Left))
    {
        retDir = Direction::Up;
    }
    else if ((dir == Direction::Right) && (turn == Direction::Right))
    {
        retDir = Direction::Down;
    }

    dir = retDir;
}