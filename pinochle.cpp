// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the function definitions for the pinochleDeck class, including the constructor and print(), as well as
//  pinochleRank << overload and pinochleRank ++ overload.

#include "pinochle.h"

using namespace std;

// print correct symbol for cards of rank type pinochle. Undefined ranks have ? symbol.
std::ostream &operator<<(std::ostream &write, const pinRank &prank)
{
	string rankSymbol = " ";
	switch (prank)
	{
	case pinRank::ace:
		rankSymbol = "A";
		break;
	case pinRank::nine:
		rankSymbol = "9";
		break;
	case pinRank::ten:
		rankSymbol = "10";
		break;
	case pinRank::jack:
		rankSymbol = "J";
		break;
	case pinRank::queen:
		rankSymbol = "Q";
		break;
	case pinRank::king:
		rankSymbol = "K";
		break;
	case pinRank::undefined:
		rankSymbol = "?";
		break;
	}

	write << rankSymbol << " ";

	return write;
}

// increment rank according to poker rank rules. If it is already the highest rank, then increment it into undefined.
pinRank operator++(pinRank &prank)
{
	// if the given rank is undefined, do not change the rank. Otherwise, increment the rank by one and return it.
	prank = (prank == pinRank::undefined) ? prank : (pinRank)((int)prank + 1);

	return prank;
}

// initialize a pinochle deck by adding two cards of each rank from each suit
pinochleDeck::pinochleDeck()
{
	int const NUM_PIN_ITERATIONS = 2;
	// this process occurs twice:
	// while the card suit and rank is not undefined,
	// add the card and then increment the card's rank.
	// When all pinochle ranks of a single suit have been added, proceed to the next suit and repeat.
	for (int i = 0; i < NUM_PIN_ITERATIONS; i++)
	{
		Card<Suit, pinRank> card(Suit::clubs, pinRank::nine);

		while (card.suit != Suit::undefined)
		{

			while (card.rank != pinRank::undefined)
			{
				cards.push_back(card);
				++card.rank;
			}

			++card.suit;

			card.rank = pinRank::nine;
		}
	}
}
