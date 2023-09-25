// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the poker class, which uses its own rank type and has its own rules about how to assemble its game deck.
// It also provides functions to increment and print this specific rank type.

#pragma once
#include "Deck_T.h"
#include "Suits.h"
#include <vector>

// ranks of cards that are only found in a poker deck
enum class pokerRank
{
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	queen,
	king,
	ace,
	undefined
};

// print the rank of a poker card
std::ostream &operator<<(std::ostream &write, const pokerRank &pRank);
// increment the rank of a pinochle card
pokerRank operator++(pokerRank &prank);

// a deck for playing poker. contains the cards specific to a poker game.
class pokerDeck : public Deck<Suit, pokerRank>
{

public:
	pokerDeck(); // initialize deck with proper cards
};
