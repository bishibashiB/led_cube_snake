
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
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::AddPlayer(uint8_t id, Color headColor, Color bodyColor)
{
    // generate random snake head to world for display
    std::random_device r;
    std::default_random_engine e1(r());
    std::uniform_int_distribution<Position_type> uniform_distx(0, matrixX - 1); // spawn on same panel
    Position_type x = uniform_distx(e1);
    std::uniform_int_distribution<Position_type> uniform_disty(0, matrixY - 1); // spawn on same panel
    Position_type y = uniform_disty(e1);

    // std::uniform_int_distribution<typename std::underlying_type<Direction>::type> uniform_distDir(0, 3);
    std::uniform_int_distribution<uint16_t> uniform_distDir(0, 3);
    Direction dir = (Direction)uniform_distDir(e1);

    SnakeBase snake;
    snake.body.push_front({x, y});
    snake.length = 5; // TODO make variable
    m_players.emplace_back(id, snake, dir, headColor, bodyColor);
    m_world.SetPosition(snake.body.front(), State::PlayerHead, headColor);
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::RemovePlayer(uint8_t id)
{
    auto ids_match = [&id](SnakePlayer& p) { return p.GetId() == id; };

    // remove player from player container
    auto it = std::remove_if(m_players.begin(), m_players.end(), ids_match);
    if (it == m_players.end())
    {
        Serial.write("RemovePlayer player unknown ");
        Serial.write(id);
    }
}

template <uint8_t matrixX, uint8_t matrixY, uint8_t tileNumX, uint8_t tileNumY>
void SnakeGame<matrixX, matrixY, tileNumX, tileNumY>::ChangePlayerDirection(uint8_t id, Direction d)
{
    auto ids_match = [&id](SnakePlayer p) { return p.GetId() == id; };

    auto it = std::find_if(m_players.begin(), m_players.end(), ids_match);

    if (it != m_players.end())
    {
        it->UpdateDirection(d);
    }
    else
    {
        Serial.write("ChangePlayerDirection player unknown ");
        Serial.write(id);
    }
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
    for (auto iter1 = m_players.begin(); iter1 != m_players.end(); iter1++)
    {
        bool breakIter2Loop = false;
        for (auto iter2 = iter1; !breakIter2Loop && iter2 != m_players.end(); iter2++)
        {
            SnakeBase& iter2Snake{iter2->GetSnake()};
            Position iter1Head = iter1->GetSnake().body.front();
            for (auto posIter2 = iter2Snake.body.begin(); posIter2 != iter2Snake.body.end(); posIter2++)
            {
                // check for overlay of a head of a snake with any element of any snake (*including same snake body)
                if (iter1Head == *posIter2)
                {
                    if ((iter1->GetId() == iter2->GetId()) && (posIter2 == iter2Snake.body.begin()))
                    {
                        // however avoid comparing current head against itself head
                        continue;
                    }

                    Serial.write(iter1->GetId() + 0x30);
                    SnakePlayer* playerRef = &(*iter1);
                    playerWithCollisions.push_back(playerRef);

                    // stop looping for current iter1, continue to check for next iter1
                    breakIter2Loop = true;
                    break;
                }
            }
        }
    }

    // remove player from player container
    while (!playerWithCollisions.empty())
    {
        Serial.write(" Player ");
        Serial.write(playerWithCollisions.back()->GetId() + 0x30);
        Serial.write(" lost!! ");
        SnakePlayer* p = playerWithCollisions.back();

        // remove snake from world display
        p->RemoveDisplay(m_world);

        auto ids_match = [p](SnakePlayer& oneOfPlayersList) { return oneOfPlayersList.GetId() == p->GetId(); };
        auto it = std::remove_if(m_players.begin(), m_players.end(), ids_match);
        if (it == m_players.end())
        {
            Serial.write("CheckCollision player unknown " + playerWithCollisions.back()->GetId());
        }
        else
        {
            m_players.erase(it);
        }
        playerWithCollisions.pop_back();
    }
}