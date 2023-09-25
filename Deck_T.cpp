#include "Deck_T.h"

template <typename Suit, typename Rank>
void Deck<Suit, Rank>::shuffle()
{

    std::random_device randomDevice;
    std::mt19937 randomGen(randomDevice());

    std::shuffle(CardSet<Suit, Rank>::cards.begin(), CardSet<Suit, Rank>::cards.end(), randomGen);


}

template <typename Suit, typename Rank>
void Deck<Suit, Rank>::collect(CardSet<Suit, Rank> &set){
    while(!set.is_empty()){
      set >> *this;

    }
    
          

}
    



