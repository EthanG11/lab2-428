// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the deck template which is required for assembling a given game's proper deck.

#pragma once
#include "card_T.h"
#include "Suits.h"
#include "CardSet_T.h"
#include <random>
#include <algorithm>

template <typename Suit, typename Rank>
class Deck : public CardSet<Suit, Rank>
{
public:
       void shuffle();
       void collect(CardSet<Suit, Rank> &set); //shift all of the cards out of the CardSet and into the Deck
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "Deck_T.cpp"
#endif