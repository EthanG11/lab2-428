// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementation of the overloaded operator << for the Card template.

#include "card_T.h"

// to print a card, print its suit and rank
template <typename S, typename R>
std::ostream &operator<<(std::ostream &write, const Card<S, R> &card)
{
	write << card.suit << card.rank;

	return write;
}

template <typename S, typename R>
bool compare_1(const Card<S, R> &card1, const Card<S, R> &card2)
{
	if (card1.rank < card2.rank)
	{
		return true;
	}
	else if (card1.rank == card2.rank)
	{
		return card1.suit < card2.suit;
	}
	return false;
}

template <typename S, typename R>
bool compare_2(const Card<S, R> &card1, const Card<S, R> &card2)
{
	if (card1.suit < card2.suit)
	{
		return true;
	}
	else if (card1.suit == card2.suit)
	{
		return card1.rank < card2.rank;
	}
	return false;
}