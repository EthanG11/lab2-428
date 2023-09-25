#pragma once
#include "card_T.h"
#include <vector>
#include <iostream>
#include <istream>
#include <stdexcept>

template <typename Suit, typename Rank>
class CardSet
{

public:
    void print(std::ostream &o, size_t size);
    CardSet<Suit, Rank> & operator>>(CardSet<Suit, Rank> &set);
    bool is_empty();

protected:
    std::vector<Card<Suit, Rank>> cards;
};

#ifdef TEMPLATE_HEADERS_INCLUDE_SOURCE /* test whether guard symbol is defined */
#include "CardSet_T.cpp"
#endif
