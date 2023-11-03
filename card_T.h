// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the template for the Card struct and the ability to print that card, compare that card according to rank or suit, 
// and check if two cards are equivalent.
//  The pinochle and poker classes require the ability to create cards with their respective
// game rank types, so a template is used to allow this to be possible.

#pragma once
#include <iostream>

// template for a card
// capable of handling any rank type. In this case, both pinochle and poker rank types.
template <typename S, typename R>
struct Card
{
	S suit;
	R rank;
	Card(){};
	Card(S s, R r) : suit(s), rank(r){};
	bool operator==(const Card<S, R>) const; //check if two cards are equivalent
};

template <typename S, typename R>
std::ostream &operator<<(std::ostream &write, const Card<S, R> &card); // print card's suit and rank

template <typename S, typename R>
bool compare_1(const Card<S, R> &card1, const Card<S, R> &card2); // compare cards by rank

template <typename S, typename R>
bool compare_2(const Card<S, R> &card1, const Card<S, R> &card2); // comopare cards by suit

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE
#include "card_T.cpp"
#endif