#pragma once
#include "poker.h"
#include "Game.h"

enum class HoldEmState
{
    preflop,
    flop,
    turn,
    river,
    undefined
};

class HoldEmGame : public Game
{

public:
    HoldEmGame(int argc, const char *argv[]);
    virtual int play();
    void printPlayersCurrentHands();

protected:
    HoldEmState state;
    pokerDeck deck;
    std::vector<CardSet<Suit, pokerRank>> hands;
    CardSet<Suit, pokerRank> board;
    virtual void deal();
    void printBoard(const char *input);
};