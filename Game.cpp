// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations for the member functions of the Game class. 

#include "Game.h"
#include <string>

// add as many players as the number of players given to the game
Game::Game(int argc, const char *argv[])
{

    for (int i = 0; i < argc; i++)
    {
        players.push_back((argv[i + 2]));
    }
}

// ask the user if they would like to play another round of their game or to end the game.
// check if they say yes or no.
bool Game::promptEndGame()
{
    std::string response;
    std::cout << "would you like to end the game? yes or no: " << std::endl;
    std::cin >> response;

    return (response.compare("yes") == 0) ? true : false;
}
