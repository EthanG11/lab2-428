// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the pinochleDeck class, which inherits the Deck template class. 
// This class uses its own rank type and has its own rules about how to assemble its game deck.
// It also provides functions to increment and print this specific rank type.

#pragma once
#include "Deck_T.h"

#include <vector>

// ranks of cards that are only found in a pinochle deck
enum class pinRank
{
	nine,
	jack,
	queen,
	king,
	ten,
	ace,
	undefined
};

// print the rank of a pinochle card
std::ostream &operator<<(std::ostream &write, const pinRank &prank);
// increment the rank of a pinochle card
pinRank operator++(pinRank &prank);

// a deck for playing pinochle. contains the cards specific to a pinochle game.
class pinochleDeck : public Deck<Suit, pinRank>
{

public:
	pinochleDeck(); // initialize deck with proper cards
};