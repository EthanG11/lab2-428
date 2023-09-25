#include "CardSet_T.h"

template <typename Suit, typename Rank>
void CardSet<Suit, Rank>::print(std::ostream &o, size_t cardsPerLine)
{

    ;

    size_t counter = 0;

    for (typename std::vector<Card<Suit, Rank>>::iterator i = cards.begin(); i != cards.end(); i++)
    {

        o << (*i).rank << " ";
        counter++;

        if (counter == cardsPerLine)
        {
            o << std::endl;
            counter = 0;
        }
    }
}

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
        std::cout << "cards is empty";
    }

    Card<Suit, Rank> lastCard = Card(this->cards.back().suit, this->cards.back().rank);
    // pushes equivalent last card
    set.cards.push_back(lastCard);

    this->cards.pop_back();

    return *this;
}

template <typename Suit, typename Rank>
bool CardSet<Suit, Rank>::is_empty()
{
    if (cards.empty())
    {
        return true;
    }
    return false;
}