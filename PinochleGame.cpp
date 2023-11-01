// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations for the PinochleGame class's member functions.

#include "PinochleGame.h"

// create hands for all players in a pinochle game
PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv)
{

    // push back a hand for every player in the game
    for (int i = 0; i < argc; i++)
    {
        CardSet<Suit, pinRank> current;
        hands.push_back(current);
    }
}

// repeatedly shift three cards (called a "packet") from the deck to the hand of each player in turn
// until all cards in the deck have been distributed
void PinochleGame::deal()
{

    int current_player_num = 0;

    while (!deck.is_empty())
    {
        // deals 3 cards into current players hand and removes the 3 cards from the deck
        for (int j = 0; j < 3; j++)
        {
            deck >> hands.at(current_player_num);
        }
        current_player_num++;
        if (current_player_num >= static_cast<int>(players.size()))
        {
            current_player_num = 0;
        }
    }
}

// a single round of Pinochle consists of these steps in the following order:
// 1. shuffle deck
// 2. deal to players
// 3. print all cards in players' hands
// 4. return all player cards to deck
// 5/6. ask to play another round and await input
int PinochleGame::play()
{
    bool end_game_flag = false;

    while (!end_game_flag)
    {
        deck.shuffle();
        deal();
        printPlayersCurrentHands();

        collectHands();
        end_game_flag = promptEndGame();
    }

    return SUCCESS;
}

// return all cards in player hands to deck
void PinochleGame::collectHands()
{
    for (std::vector<CardSet<Suit, pinRank>>::iterator i = hands.begin(); i != hands.end(); i++)
    {
        deck.collect(*i);
    }
}
std::ostream &operator<<(std::ostream &x, const PinochleMelds &y)
{
    std::string names[15] = {
        "dix",
        "offsuitmarriage",
        "fortyjacks",
        "pinochle",
        "insuitmarriage",
        "sixtyqueens",
        "eightykings",
        "hundredaces",
        "insuitrun",
        "doublepinochle",
        "fourhundredjacks",
        "sixhundredqueens",
        "eighthundredkings",
        "thousandaces",
        "insuitdoublerun"};

    x << "name: " << names[static_cast<std::underlying_type<PinochleMelds>::type>(y)] << " points: " << PinochleGame::values[static_cast<std::underlying_type<PinochleMelds>::type>(y)] << std::endl;
    return x;
};

// print every card in every player's hand
void PinochleGame::printPlayersCurrentHands()
{
    int counter = 0;
    int cards_printed_per_line = 12;
    std::vector<CardSet<Suit, pinRank>>::iterator j = hands.begin();
    for (std::vector<std::string>::iterator i = players.begin(); i != players.end(); i++)
    {
        std::cout << *i << ": ";
        (*j).print(std::cout, cards_printed_per_line);
        std::cout << std::endl;

        std::vector<PinochleMelds> melds;

        suit_independent_evaluation(*j, melds);
        auto m = melds.begin();
        for (; m != melds.end(); m++)
        {
            std::cout << "MELD: " << *m << std::endl;
        }
        melds.clear();

        counter++;
        j++;
    }
}

std::pair<std::vector<Card<Suit, pinRank>>::iterator, std::vector<Card<Suit, pinRank>>::iterator> const getCardRange(std::vector<Card<Suit, pinRank>> &cards, pinRank card)
{
    std::vector<Card<Suit, pinRank>>::iterator it = std::find_if(
        cards.begin(), cards.end(), [&card](Card<Suit, pinRank> current)
        { return current.rank == card; });

    std::vector<Card<Suit, pinRank>>::reverse_iterator end = std::find_if(cards.rbegin(), cards.rend(), [&card](Card<Suit, pinRank> current)
                                                                          { return current.rank == card; });
    end = end++;

    return std::pair<std::vector<Card<Suit, pinRank>>::iterator, std::vector<Card<Suit, pinRank>>::iterator>(it, end.base());
}

void checkAllEightCards(std::vector<Card<Suit, pinRank>> &cards, pinRank card, std::vector<PinochleMelds> &vec)
{
    // check for 8
    int counter = 0;

    auto iteratorPair = getCardRange(cards, card);

    auto it = iteratorPair.first;
    auto end = iteratorPair.second;

    while ((*(it)).rank == card && counter < 8)
    {
        counter++;
        it++;
    }

    if (counter == 8)
    {
        if (card == pinRank::ace)
        {
            vec.push_back(PinochleMelds::thousandaces);
        }
        else if (card == pinRank::king)
        {
            vec.push_back(PinochleMelds::eighthundredkings);
        }
        else if (card == pinRank::queen)
        {
            vec.push_back(PinochleMelds::sixhundredqueens);
        }
        else if (card == pinRank::jack)
        {
            vec.push_back(PinochleMelds::fourhundredjacks);
        }
    }

    // check for 4
    else if (counter >= 4)
    {
        for (; it != end; it++)
        {
            if (std::find(it, end, Card<Suit, pinRank>(Suit::clubs, card)) != end &&
                std::find(it, end, Card<Suit, pinRank>(Suit::diamonds, card)) != end &&
                std::find(it, end, Card<Suit, pinRank>(Suit::hearts, card)) != end &&
                std::find(it, end, Card<Suit, pinRank>(Suit::spades, card)) != end)
            {
                if (card == pinRank::ace)
                {
                    vec.push_back(PinochleMelds::hundredaces);
                }
                else if (card == pinRank::king)
                {
                    vec.push_back(PinochleMelds::eightykings);
                }
                else if (card == pinRank::queen)
                {
                    vec.push_back(PinochleMelds::sixtyqueens);
                }
                else if (card == pinRank::jack)
                {
                    vec.push_back(PinochleMelds::fortyjacks);
                }
            }
        }
    }
};

void PinochleGame::suit_independent_evaluation(const CardSet<Suit, pinRank> &hand, std::vector<PinochleMelds> &vec)
{

    CardSet<Suit, pinRank> localHand(hand);

    std::vector<Card<Suit, pinRank>> CardSet<Suit, pinRank>::*memberCards = CardSet<Suit, pinRank>::access_cards();

    std::vector<Card<Suit, pinRank>> cards = localHand.*memberCards;

    std::sort(cards.begin(), cards.end(), compare_2<Suit, pinRank>);
    std::sort(cards.begin(), cards.end(), compare_1<Suit, pinRank>);

    checkAllEightCards(cards, pinRank::ace, vec);
    checkAllEightCards(cards, pinRank::king, vec);
    checkAllEightCards(cards, pinRank::queen, vec);
    checkAllEightCards(cards, pinRank::jack, vec);

    Card<Suit, pinRank> jackDiamond(Suit::diamonds, pinRank::jack);
    Card<Suit, pinRank> queenSpade(Suit::spades, pinRank::queen);
    auto jackTest = std::find_if(
        cards.begin(), cards.end(), [jackDiamond, queenSpade](Card<Suit, pinRank> current)
        { return current == jackDiamond; });

    auto queenTest = std::find_if(
        cards.begin(), cards.end(), [jackDiamond, queenSpade](Card<Suit, pinRank> current)
        { return current == queenSpade; });

    // have a pinochle
    if (jackTest != cards.end() && queenTest != cards.end())
    {

        // test for doublepinochle
        if (*(++jackTest) == jackDiamond && *(++queenTest) == queenSpade)
        {

            vec.push_back(PinochleMelds::doublepinochle);
        }
        else
        {
            vec.push_back(PinochleMelds::pinochle);
        }
    }
};
