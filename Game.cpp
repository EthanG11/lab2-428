#include "Game.h"
#include <string>
// pass two less args into here for both params
Game::Game(int argc, const char *argv[])
{

    for (int i = 0; i < argc; i++)
    {
        players.push_back((argv[i + 2]));
    }
}

// move to Game class
bool Game::promptEndGame()
{
    std::string response;
    std::cout << "would you like to end the game? yes or no: " << std::endl;
    std::cin >> response;

    return (response.compare("yes") == 0) ? true : false;
}
