#pragma once
#include "pinochle.h"
#include <vector>
#include "Game.h"
#include "CardSet_T.h"
#include "Suits.h"
#include <iostream>

class PinochleGame : public Game
{

public:
    PinochleGame(int argc, const char *argv[]);
    virtual int play();
    void collectHands();
    void printPlayersCurrentHands();

protected:
    pinochleDeck deck;
    std::vector<CardSet<Suit, pinRank>> hands;
    virtual void deal();
};