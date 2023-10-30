// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations of the HoldEmGame class's member functions.

#include "HoldEmGame.h"

// create a hand for each player in the game
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop)
{
    // push back a hand for every player in the game
    for (int i = 0; i < argc; i++)
    {
        CardSet<Suit, pokerRank> current;
        hands.push_back(current);
    }
}

// distribute the next card(s) according to the current state of the game.
void HoldEmGame::deal()
{
    // if the state is preflop, then deal two cards to each player and then increment state
    if (state == HoldEmState::preflop)
    {

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck >> hands.at(i);
        }
        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck >> hands.at(i);
        }

        state = HoldEmState::flop;
    }
    // if the state is flop, then deal three cards to the board and increment state
    else if (state == HoldEmState::flop)
    {

        for (int i = 0; i < 3; i++)
        {
            deck >> board;
        }
        state = HoldEmState::turn;
    }
    // if the state is turn, then deal three cards to the board and increment state
    else if (state == HoldEmState::turn)
    {
        deck >> board;
        state = HoldEmState::river;
    }
    // if the state is river, then deal three cards to the board and increment state
    else if (state == HoldEmState::river)
    {
        deck >> board;
        state = HoldEmState::undefined;
    }
}

// a single play in a Texas Hold Em game consists of these steps in the following order:
// 1. shuffle the deck
// 2. set the state to preflop
// 3. deal two cards to each hand and proceed to flop
// 4. print each player's cards
// 5. deal three cards to the board and proceed to turn
// 6. print all cards on the board
// 7. deal one more card to the board and proceed to river
// 8. print all cards on the board
// 9. deal one more card to the board
// 10. print all cards on the board
// 11. collect all players' cards and return them to deck
// 12. collect all board cards and return them to deck
// 13/14. ask to play another round and await input
int HoldEmGame::play()
{
    int NUM_FLOP_CARDS = 3;
    int NUM_TURN_CARDS = 4;
    int NUM_RIVER_CARDS = 5;

    bool end_game_flag = false;
    while (!end_game_flag)
    {
        deck.shuffle();
        state = HoldEmState::preflop;
        deal();
        printPlayersCurrentHands();
        deal();
        printBoard("flop", NUM_FLOP_CARDS);
        deal();
        printBoard("turn", NUM_TURN_CARDS);
        deal();
        printBoard("river", NUM_RIVER_CARDS);

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck.collect(hands.at(i));
        }
        deck.collect(board);
        end_game_flag = promptEndGame();
    }
    return SUCCESS;
}

// print every card on the board
void HoldEmGame::printBoard(const char *segment, int numCards)
{
    std::cout << "BOARD(" << segment << "):";
    board.print(std::cout, numCards);
}

// print every card in each of the players hands
void HoldEmGame::printPlayersCurrentHands()
{
    int counter = 0;
    int cards_in_hand = 2;
    std::vector<CardSet<Suit, pokerRank>>::iterator j = hands.begin();
    for (std::vector<std::string>::iterator i = players.begin(); i != players.end(); i++)
    {
        std::cout << *i << ": ";
        (*j).print(std::cout, cards_in_hand);
        std::cout << std::endl;
        counter++;
        j++;
    }
}

std::ostream &operator<<(std::ostream &stream, const HoldEmHandRank &rank)
{

    switch (rank)
    {

    case (HoldEmHandRank::xhigh):
        stream << "X High";
        break;

    case (HoldEmHandRank::pair):
        stream << "Pair";
        break;

    case (HoldEmHandRank::twopair):
        stream << "Two Pair";
        break;
    case (HoldEmHandRank::threeofakind):
        stream << "Three of a kind";
        break;
    case (HoldEmHandRank::straight):
        stream << "Straight";
        break;

    case (HoldEmHandRank::flush):
        stream << "Flush";
        break;

    case (HoldEmHandRank::fullhouse):
        stream << "Full House";
        break;
    case (HoldEmHandRank::fourofakind):
        stream << "Four of a kind";
        break;
    case (HoldEmHandRank::straightflush):
        stream << "Straight flush";
        break;
    case (HoldEmHandRank::undefined):
        stream << "Undefined hand";
        break;
    }
    return stream;
}

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<Suit, pokerRank> &hand, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker)
{
    pokerRank xValueReturn = pokerRank::undefined;
    CardSet<Suit, pokerRank> localHand(hand);

    std::vector<Card<Suit, pokerRank>> CardSet<Suit, pokerRank>::*memberCards = CardSet<Suit, pokerRank>::access_cards();

    std::vector<Card<Suit, pokerRank>> cards = localHand.*memberCards;

    std::sort(cards.begin(), cards.end(), compare_2<Suit, pokerRank>);
    std::sort(cards.begin(), cards.end(), compare_1<Suit, pokerRank>);

    std::cout << "Sorted: ";

    for (std::vector<Card<Suit, pokerRank>>::iterator it = cards.begin(); it != cards.end(); it++)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    // check for undefined
    if (cards.size() != 5)
    {
        return HoldEmHandRank::undefined;
    }

    // check for straighflush

    if (checkForStraight(cards, firstTieBreaker) && checkForFlush(cards, firstTieBreaker))
    {
        return HoldEmHandRank::straightflush;
    }

    // check for four of a kind
    if (findXofaKind(cards, 4, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::fourofakind;
    }

    // check for fullhouse
    if (checkForFullHouse(cards, firstTieBreaker))
    {
        return HoldEmHandRank::fullhouse;
    }

    // check for flush
    if (checkForFlush(cards))
    {

        return HoldEmHandRank::flush;
    }

    // check for straight
    if (checkForStraight(cards, firstTieBreaker))
    {
        return HoldEmHandRank::straight;
    }

    // check for threeofakind
    if (findXofaKind(cards, 3, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::threeofakind;
    }
    // check for two pair

    if (checkForTwoPair(cards, firstTieBreaker, secondTieBreaker, thirdTieBreaker))
    {
        return HoldEmHandRank::twopair;
    }

    // check for pair
    if (findXofaKind(cards, 2, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::pair;
    }

    return HoldEmHandRank::xhigh;
}

bool checkForTwoPair(std::vector<Card<Suit, pokerRank>> &cards, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker)
{
}

bool checkForFullHouse(std::vector<Card<Suit, pokerRank>> &cards, pokerRank &firstTieBreaker)
{

    // two cases: first three same and last two same
    // or first two same and last three same

    std::vector<Card<Suit, pokerRank>>::iterator fh = cards.begin();
    pokerRank first = cards.at(0).rank;
    bool fullHouse = false;

    bool case1 = true;

    // case 1

    for (; fh != cards.end() - 2; fh++)
    {
        if ((*fh).rank != first)
        {
            case1 = false;
            break;
        }
    }
    firstTieBreaker = (*(--fh)).rank;

    if (case1 && (*fh).rank == (*(++fh)).rank)
    {

        return true;
    }

    // case 2

    fh = cards.begin();

    if ((*fh).rank != (*(++fh)).rank)
    {

        return false;
    }
    ++fh;

    pokerRank third = (*fh).rank;
    fh++;

    for (; fh != cards.end(); fh++)
    {
        if ((*fh).rank != third)
        {
            return false;
            break;
        }
    }

    firstTieBreaker = third;

    return true;
}

bool checkForStraight(std::vector<Card<Suit, pokerRank>> &hand, pokerRank &firstTieBreaker)
{

    pokerRank starting = hand.at(0).rank;

    if (starting >= pokerRank::jack)
    {
        return false;
    }

    std::vector<Card<Suit, pokerRank>>::iterator next = ++hand.begin();

    for (std::vector<Card<Suit, pokerRank>>::iterator it = hand.begin(); it != --hand.end(); it++)
    {
        if ((*next).rank != static_cast<pokerRank>((static_cast<int>((*it).rank)) + 1))
        {
            return false;
        }
        next++;
    }

    return true;
}
bool checkForFlush(std::vector<Card<Suit, pokerRank>> &hand)
{
    pokerRank first = hand.at(0).rank;

    return (std::count_if(hand.begin() + 1, hand.end(), [&first](Card<Suit, pokerRank> card)
                          { return card.rank == first; }) == 4);
}
bool findXofaKind(std::vector<Card<Suit, pokerRank>> &hand, int x, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker)
{

    std::vector<Card<Suit, pokerRank>>::iterator pnt1 = hand.begin();
    std::vector<Card<Suit, pokerRank>>::iterator pnt2 = ++hand.begin();

    int counter = 0;
    while (pnt2 != hand.end() && counter < (x - 1))
    {

        if ((*pnt1).rank != (*pnt2).rank)
        {
            pnt1++;
            counter = 0;
        }
        else
        {
            counter++;
        }
        pnt2++;
    }
    // 1 for pair
    // 2 for threeofakind
    // 3 for fourofakind
    if (counter >= (x - 1))
    {
        return true;
    }
    return false;
}

bool operator<(const HoldEmGame::values::hold &x, const HoldEmGame::values::hold &y)
{

    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));

    int yFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int yFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int yFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int yFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));

    if (x.holdEmHandRank < y.holdEmHandRank)
    {
        return true;
    }

    if (x.tieBreakers.at(0) < y.tieBreakers.at(0))
    {
        return true;
    }
    else if (x.tieBreakers.at(1) < y.tieBreakers.at(1))
    {
        return true;
    }
    else if (x.tieBreakers.at(2) < y.tieBreakers.at(2))
    {
        return true;
    }
    else if (x.tieBreakers.at(3) < y.tieBreakers.at(3))
    {
        return true;
    }
    return false;
}
