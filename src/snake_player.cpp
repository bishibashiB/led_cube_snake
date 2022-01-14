

#include "snake_player.hpp"

SnakePlayer::SnakePlayer(uint8_t id, SnakeBase snake, Direction dir)
    : id(id)
    , snake(snake)
    , dir(dir)
{
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakePlayer::MoveSnake(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
{
    // old head
    world.SetPosition(snake.body.begin(), State::PlayerBody);

    // new head
    Position newPos = world.movePixel({dir, snake.body.front()});
    if (world.GetPosition(newPos) == State::Snack)
    {
        snake.length++;
        world.SetPosition(world.GetFreePosition(), State::Snack);
    }
    snake.body.push_front(snake.body.front());
    world.SetPosition(snake.body.begin(), State::PlayerHead);

    // old tail
    if (snake.body.size() >= snake.length)
    {
        world.SetPosition(snake.body.back(), State::Free);
        snake.body.pop_back();
    }
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