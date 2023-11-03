// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementation of the overloaded operators << and == for the Card template, as well as member functions compare_1 and compare_2.

#include "card_T.h"

// to print a card, print its suit and rank
template <typename S, typename R>
std::ostream &operator<<(std::ostream &write, const Card<S, R> &card)
{
	write << card.rank << card.suit;

	return write;
}

// compare the ranks of two cards
// if the first rank is less than the second rank, then return true.
// if the cards have the same rank, then check suit. 
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

// compare the suits of two cards
// if the first suit is less than the second suit, return true.
// if the suits are the same, then check rank.
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

// check if two cards are the same card
// return true if they match in both suit and rank
template <typename S, typename R>
bool Card<S, R>::operator==(const Card<S, R> other) const
{
	if (this->rank == other.rank && this->suit == other.suit)
	{
		return true;
	}
	return false;
}