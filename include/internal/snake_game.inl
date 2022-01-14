
#include <random>
// #include <type_traits>

#include "snake_types.hpp"
#include "snake_game.hpp"

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::SnakeGame(SnakeWorld<matrixX, matrixY, tileNumX, tileNumY>& world)
    : m_world(world)
{
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::AddPlayer(uint8_t id)
{
    // generate random snake head to world for display
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<Position_type> uniform_distx(0, matrixX - 1); // spawn on same panel
    Position_type x = uniform_distx(e1);
    std::uniform_int_distribution<Position_type> uniform_disty(0, matrixY - 1); // spawn on same panel
    Position_type y = uniform_disty(e1);

    // std::uniform_int_distribution<typename std::underlying_type<Direction>::type> uniform_distDir(0, 3);
    std::uniform_int_distribution<uint8_t> uniform_distDir(0, 3);
    Direction dir = (Direction)uniform_disty(e1);

    SnakeBase snake;
    snake.body.push_front({x, y});
    snake.length = 2; // TODO make variable
    SnakePlayer sp{id, snake, dir};
    m_players.emplace(m_players.end(), sp);
    m_world.SetPosition(snake.body.front(), State::PlayerHead);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::RemovePlayer(uint8_t id)
{
    auto ids_match = [&id](SnakePlayer& p) { return p.GetId() == id; };

    // remove player from player container
    auto it = std::remove_if(m_players.begin(), m_players.end(), ids_match);
    if (it == m_players.end())
    {
        // print error
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::ChangePlayerDirection(uint8_t id, Direction d)
{
    auto ids_match = [&id](SnakePlayer p) { return p.GetId() == id; };

    auto it = std::find_if(m_players.begin(), m_players.end(), ids_match);
    it->UpdateDirection(d);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::IterateWorld()
{
    for (auto& p : m_players)
    {
        p.MoveSnake(m_world);
    }

    CheckCollision();
    m_world.Update();
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::CheckCollision()
{
    std::vector<SnakePlayer*> playerWithCollisions;
    // check all players head against all other playes snakes
    for (auto& p : m_players)
    {
        for (auto& otherP : m_players)
        {
            for (auto pos : otherP.GetSnake().body)
            {
                if (p.GetSnake().body.front().x == pos.x && p.GetSnake().body.front().y == pos.y)
                {
                    playerWithCollisions.push_back(&p);
                }
            }
        }
    }

    // remove player from player container
    while (!playerWithCollisions.empty())
    {
        SnakePlayer* p = playerWithCollisions.back();
        auto ids_match = [p](SnakePlayer& oneOfPlayersList) { return oneOfPlayersList.GetId() == p->GetId(); };
        std::remove_if(m_players.begin(), m_players.end(), ids_match);
    }
}