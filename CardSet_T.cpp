// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations for the member functions of the CardSet_T template class.
// print(), operator>>(), is_empty(), and access_cards()

#include "CardSet_T.h"

// print every card in the set
template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::print(std::ostream &o, size_t cardsPerLine)
{

    size_t counter = 0;

    for (typename std::vector<Card<Suit, Rank>>::iterator i = cards.begin(); i != cards.end(); i++)
    {

        o << (*i).rank << (*i).suit << " ";
        counter++;

        if (counter == cardsPerLine)
        {
            o << std::endl;
            counter = 0; // reset the counter because card limit per line has been reached
        }
    }
}

// use the >> operator to push an equivalent last card onto the set
template <typename Suit, typename Rank>
CardSet<Suit, Rank> &CardSet<Suit, Rank>::operator>>(CardSet<Suit, Rank> &set)
{
    // is empty
    try
    {
        if (cards.empty())
        {
            throw std::runtime_error("fail");
        }
    }
    catch (...)
    {
        std::cout << "ERROR CAUGHT: cards is empty";
    }

    Card<Suit, Rank> lastCard = Card(this->cards.back().suit, this->cards.back().rank);
    // pushes equivalent last card
    set.cards.push_back(lastCard);

    this->cards.pop_back();

    return *this;
}

// check if the set has no cards
template <typename Suit, typename Rank>
bool CardSet<Suit, Rank>::is_empty()
{
    if (cards.empty())
    {
        return true;
    }
    return false;
}

// return a ref to cards vector to allow singular violation of encapsulation
template <typename Suit, typename Rank>
std::vector<Card<Suit, Rank>> CardSet<Suit, Rank>::*CardSet<Suit, Rank>::access_cards()
{
    return &CardSet<Suit, Rank>::cards;
}
