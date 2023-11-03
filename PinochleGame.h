// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the PinochleGame class, which inherits the Game class.
// This class has its own specific deck.
// This file also contains the functions necessary for checking win states of a pinochle game.

#pragma once
#include "pinochle.h"
#include <vector>
#include "Game.h"
#include "Suits.h"
#include <iostream>
#include <list>

// possible melds, or specific combinations of cards, in pinochle.
enum class PinochleMelds
{
    dix,
    offsuitmarriage,
    fortyjacks,
    pinochle,
    insuitmarriage,
    sixtyqueens,
    eightykings,
    hundredaces,
    insuitrun,
    doublepinochle,
    fourhundredjacks,
    sixhundredqueens,
    eighthundredkings,
    thousandaces,
    insuitdoublerun
};
int const NUMBER_OF_MELDS = 15;

// a class to create/play a game of Pinochle
class PinochleGame : public Game
{
public:
    PinochleGame(int argc, const char *argv[]);
    virtual int play(); // a single round of Pinochle
    void collectHands();
    void printPlayersCurrentHands();
    friend std::ostream &operator<<(std::ostream &x, const PinochleMelds &y);

    static constexpr unsigned int values[NUMBER_OF_MELDS] = {10, 20, 40, 40, 40, 60, 80, 100, 150, 300, 400, 600, 800, 1000, 1500};

protected:
    pinochleDeck deck;
    std::vector<CardSet<Suit, pinRank>> hands;
    virtual void deal();

private:
    void suit_independent_evaluation(const CardSet<Suit, pinRank> &x, std::vector<PinochleMelds> &vec);
};

// check hand for melds
void checkEightAndFourMelds(std::vector<Card<Suit, pinRank>> &cards, pinRank card, std::vector<PinochleMelds> &vec);
