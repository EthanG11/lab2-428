#include "PinochleGame.h"
int main()
{
    std::vector<Card<Suit, pinRank>> fourAcesCards;

    Card<Suit, pinRank> kingSpades(Suit::spades, pinRank::king);

    Card<Suit, pinRank> aceSpades(Suit::spades, pinRank::ace);
    Card<Suit, pinRank> aceHearts(Suit::hearts, pinRank::ace);
    Card<Suit, pinRank> aceDiamonds(Suit::diamonds, pinRank::ace);
    Card<Suit, pinRank> aceClubs(Suit::clubs, pinRank::ace);

    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);
    fourAcesCards.push_back(kingSpades);

    fourAcesCards.push_back(aceSpades);
    fourAcesCards.push_back(aceHearts);
    fourAcesCards.push_back(aceDiamonds);
    fourAcesCards.push_back(aceClubs);

    std::vector<PinochleMelds> melds1;

    pinRank card = pinRank::ace;

    checkEightAndFourMelds(fourAcesCards, card, melds1);

    if (melds1.size() == 1 && melds1.at(0) == PinochleMelds::hundredaces)
    {
        std::cout << "success hundredaces" << std::endl;
    }

    else
    {
        std::cout << melds1.size();
        std::cout << "FAIL";
    }

    std::vector<Card<Suit, pinRank>> eightAcesCards;
    std::vector<PinochleMelds> melds2;
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(kingSpades);
    eightAcesCards.push_back(aceClubs);
    eightAcesCards.push_back(aceDiamonds);
    eightAcesCards.push_back(aceHearts);
    eightAcesCards.push_back(aceSpades);
    eightAcesCards.push_back(aceClubs);
    eightAcesCards.push_back(aceDiamonds);
    eightAcesCards.push_back(aceHearts);
    eightAcesCards.push_back(aceSpades);

    checkEightAndFourMelds(eightAcesCards, card, melds2);

    if (melds2.size() == 1 && melds2.at(0) == PinochleMelds::thousandaces)
    {
        std::cout << "success thousandaces" << std::endl;
    }
    else
    {
        std::cout << "FAIL";
    }
    return 0;
}