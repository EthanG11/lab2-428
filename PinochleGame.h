// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the PinochleGame class, which inherits the Game class. 
// This class has its own specific deck.

#pragma once
#include "pinochle.h"
#include <vector>
#include "Game.h"
#include "CardSet_T.h"
#include "Suits.h"
#include <iostream>

//a class to create/play a game of Pinochle
class PinochleGame : public Game
{
public:
    PinochleGame(int argc, const char *argv[]);
    virtual int play(); // a single round of Pinochle
    void collectHands();
    void printPlayersCurrentHands();

protected:
    pinochleDeck deck;
    std::vector<CardSet<Suit, pinRank>> hands;
    virtual void deal();
};