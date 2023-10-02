// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the function definitions for the pokerDeck class, including the constructor and print(), as well as
//  pokerRank << overload and pokerRank ++ overload.

#include "poker.h"

using namespace std;

// print correct symbol for cards of rank type poker. Undefined ranks have ? symbol.
std::ostream &operator<<(std::ostream &write, const pokerRank &pRank)
{
	string rankSymbol = " ";
	switch (pRank)
	{
	case pokerRank::ace:
		rankSymbol = "A";
		break;
	case pokerRank::two:
		rankSymbol = "2";
		break;
	case pokerRank::three:
		rankSymbol = "3";
		break;
	case pokerRank::four:
		rankSymbol = "4";
		break;
	case pokerRank::five:
		rankSymbol = "5";
		break;
	case pokerRank::six:
		rankSymbol = "6";
		break;
	case pokerRank::seven:
		rankSymbol = "7";
		break;
	case pokerRank::eight:
		rankSymbol = "8";
		break;
	case pokerRank::nine:
		rankSymbol = "9";
		break;
	case pokerRank::ten:
		rankSymbol = "10";
		break;
	case pokerRank::jack:
		rankSymbol = "J";
		break;
	case pokerRank::queen:
		rankSymbol = "Q";
		break;
	case pokerRank::king:
		rankSymbol = "K";
		break;
	case pokerRank::undefined:
		rankSymbol = "?";
		break;
	}

	write << rankSymbol << " ";

	return write;
}

// increment rank according to poker rank rules.  If it is already the highest rank, then increment it into undefined.
pokerRank operator++(pokerRank &prank)
{
	// if the given rank is undefined, do not change the rank. Otherwise, increment the rank by one and return it.
	prank = (prank == pokerRank::undefined) ? prank : static_cast<pokerRank>(static_cast<int>(prank) + 1);
	return prank;
}

// initialize a pinochle deck by adding one card of each rank from each suit
pokerDeck::pokerDeck()
{

	Card<Suit, pokerRank> card(Suit::clubs, pokerRank::two);

	// starting from rank 2,
	// while the card suit and rank is not undefined,
	// add the card and then increment the card's rank.
	// When all ranks of a single suit have been added, proceed to the next suit and repeat.
	while (card.suit != Suit::undefined)
	{

		while (card.rank != pokerRank::undefined)
		{
			cards.push_back(card);
			++card.rank;
		}

		++card.suit;

		card.rank = pokerRank::two;
	}
}
