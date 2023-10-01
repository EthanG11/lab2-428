// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations for the member functions of the deck template from Deck_T.h.
// the functions are shuffle() and collect().

#include "Deck_T.h"

//shuffle the deck
template <typename Suit, typename Rank>
void Deck<Suit, Rank>::shuffle()
{
    std::random_device randomDevice;
    std::mt19937 randomGen(randomDevice());

    std::shuffle(CardSet<Suit, Rank>::cards.begin(), CardSet<Suit, Rank>::cards.end(), randomGen);
}

//shift all of the cards out of the CardSet and into the Deck
template <typename Suit, typename Rank>
void Deck<Suit, Rank>::collect(CardSet<Suit, Rank> &set){
    while(!set.is_empty()){
      set >> *this;
    }
}