// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the HoldEmGame class, which inherits the Game class, and the states of this type of poker game.
// This class has its own specific deck, and notably, state of the game, and board.

#pragma once
#include "poker.h"
#include "Game.h"
#include <iostream>

// states of a Texas Hold Em game
enum class HoldEmState
{
    preflop,
    flop,
    turn,
    river,
    undefined
};

enum class HoldEmHandRank
{
    xhigh,
    pair,
    twopair,
    threeofakind,
    straight,
    flush,
    fullhouse,
    fourofakind,
    straightflush,
    undefined
};

// class to create/play a game of Texas Hold Em.
class HoldEmGame : public Game
{

public:
    HoldEmGame(int argc, const char *argv[]);
    virtual int play(); // a single round of Texas Hold Em
    void printPlayersCurrentHands();

    struct values
    {
        struct hold
        {
            CardSet<Suit, pokerRank> cards;
            std::string playerName;
            HoldEmHandRank holdEmHandRank;

            std::vector<pokerRank> tieBreakers;

            hold(CardSet<Suit, pokerRank> cards, std::string playerName, HoldEmHandRank holdEmHandRank, std::vector<pokerRank> tieBreakers) : cards(cards), playerName(playerName), holdEmHandRank(holdEmHandRank), tieBreakers(tieBreakers){};
        };
    };

protected:
    HoldEmState state;
    pokerDeck deck;
    std::vector<CardSet<Suit, pokerRank>> hands;
    CardSet<Suit, pokerRank> board; // the common board of cards that is shared by the players in the game
    virtual void deal();
    void printBoard(const char *input, int numCards);

private:
    HoldEmHandRank holdem_hand_evaluation(const CardSet<Suit, pokerRank> &hand, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker, pokerRank &fifthTieBreaker);
};

std::ostream &operator<<(std::ostream &, const HoldEmHandRank &);
bool operator<(const HoldEmGame::values::hold &x, const HoldEmGame::values::hold &y);

bool findXofaKind(std::vector<Card<Suit, pokerRank>> &hand, int x, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker);
bool checkForStraight(std::vector<Card<Suit, pokerRank>> &hand, pokerRank &firstTieBreaker);
bool checkForFlush(std::vector<Card<Suit, pokerRank>> &hand);
bool checkForTwoPair(std::vector<Card<Suit, pokerRank>> &cards, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker);
bool checkForFullHouse(std::vector<Card<Suit, pokerRank>> &cards, pokerRank &firstTieBreaker);
