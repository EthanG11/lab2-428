// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the HoldEmGame class, which inherits the Game class, and the states of this type of poker game. 
// This class has its own specific deck, and notably, state of the game, and board.

#pragma once
#include "poker.h"
#include "Game.h"

//states of a Texas Hold Em game
enum class HoldEmState
{
    preflop,
    flop,
    turn,
    river,
    undefined
};

//class to create/play a game of Texas Hold Em. 
class HoldEmGame : public Game
{

public:
    HoldEmGame(int argc, const char *argv[]);
    virtual int play(); //a single round of Texas Hold Em
    void printPlayersCurrentHands();

protected:
    HoldEmState state;
    pokerDeck deck;
    std::vector<CardSet<Suit, pokerRank>> hands;
    CardSet<Suit, pokerRank> board; //the common board of cards that is shared by the players in the game
    virtual void deal();
    void printBoard(const char *input, int numCards);
};