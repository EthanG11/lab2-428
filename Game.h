#pragma once
#include <vector>
#include <string>
#include <iostream>

class Game
{

public:
    Game(int argc, const char *argv[]);
    virtual int play() = 0;
    bool promptEndGame();
    int SUCCESS = 0;

protected:
    std::vector<std::string> players;
};