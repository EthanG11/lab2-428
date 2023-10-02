// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the CardSet template class declaration. This class is inherited by the Deck template class.

#pragma once
#include "card_T.h"
#include <vector>
#include <iostream>
#include <istream>
#include <stdexcept>

//the set of cards that are only allowed in the deck for a given game type.
template <typename Suit, typename Rank>
class CardSet
{
public:
    void print(std::ostream &o, size_t size);
    CardSet<Suit, Rank> & operator>>(CardSet<Suit, Rank> &set); //use the >> operator to push an equivalent last card onto the set
    bool is_empty();

protected:
    std::vector<Card<Suit, Rank>> cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "CardSet_T.cpp"
#endif
