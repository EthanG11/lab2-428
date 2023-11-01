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
    // if the state is turn, then deal a card to the board and increment state
    else if (state == HoldEmState::turn)
    {
        deck >> board;
        state = HoldEmState::river;
    }
    // if the state is river, then deal a cards to the board and increment state
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
    // int NUM_TURN_CARDS = 4;
    // int NUM_RIVER_CARDS = 5;

    bool end_game_flag = false;
    while (!end_game_flag)
    {
        deck.shuffle();
        state = HoldEmState::preflop;
        deal();
        printPlayersCurrentHands();
        deal();
        printBoard("flop", NUM_FLOP_CARDS);

        std::vector<values::hold> vec;

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            CardSet<Suit, pokerRank> hand;

            CardSet<Suit, pokerRank> localHand(hands.at(i));
            CardSet<Suit, pokerRank> localHand2(board);

            std::vector<Card<Suit, pokerRank>> CardSet<Suit, pokerRank>::*memberCards = CardSet<Suit, pokerRank>::access_cards();

            std::vector<Card<Suit, pokerRank>> cards = localHand.*memberCards;
            std::vector<Card<Suit, pokerRank>> cards2 = localHand2.*memberCards;

            localHand >> hand;
            localHand >> hand;

            for (int j = 0; j < 3; j++)
            {
                localHand2 >> hand;
            }

            pokerRank firstTieBreaker;
            pokerRank secondTieBreaker;
            pokerRank thirdTieBreaker;
            pokerRank fourthTieBreaker;
            pokerRank fifthTieBreaker;

            HoldEmHandRank holdEmHandRank = holdem_hand_evaluation(hand, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker, fifthTieBreaker);

            std::vector<pokerRank> tieBreakers;

            tieBreakers.push_back(firstTieBreaker);
            tieBreakers.push_back(secondTieBreaker);
            tieBreakers.push_back(thirdTieBreaker);
            tieBreakers.push_back(fourthTieBreaker);
            tieBreakers.push_back(fifthTieBreaker);

            values::hold x = values::hold(hand, players.at(i), holdEmHandRank, tieBreakers);
            vec.push_back(x);
        }

        // vec.at(0) < vec.at(1);

        std::sort(vec.begin(), vec.end());

        for (auto it = vec.begin(); it != vec.end(); it++)
        {
            std::cout << "Player name: " << (*it).playerName << std::endl
                      << " cards: ";
            (*it).cards.print(std::cout, 5);
            std::cout << " Hand rank: " << (*it).holdEmHandRank << std::endl;
        }
        /*
            deal();
            printBoard("turn", NUM_TURN_CARDS);
            deal();
            printBoard("river", NUM_RIVER_CARDS);
        */

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

HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<Suit, pokerRank> &hand, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker, pokerRank &fifthTieBreaker)
{
    CardSet<Suit, pokerRank> localHand(hand);

    std::vector<Card<Suit, pokerRank>> CardSet<Suit, pokerRank>::*memberCards = CardSet<Suit, pokerRank>::access_cards();

    std::vector<Card<Suit, pokerRank>> cards = localHand.*memberCards;

    std::sort(cards.begin(), cards.end(), compare_2<Suit, pokerRank>);
    std::sort(cards.begin(), cards.end(), compare_1<Suit, pokerRank>);

    // check for undefined
    if (cards.size() != 5)
    {
        return HoldEmHandRank::undefined;
    }

    // check for straighflush

    if (checkForStraight(cards, firstTieBreaker) && checkForFlush(cards))
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
        firstTieBreaker = cards.at(4).rank;
        secondTieBreaker = cards.at(3).rank;
        thirdTieBreaker = cards.at(2).rank;
        fourthTieBreaker = cards.at(1).rank;
        fifthTieBreaker = cards.at(0).rank;

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

    if (((cards.at(0).rank == cards.at(1).rank) && (cards.at(2).rank == cards.at(3).rank)) || ((cards.at(0).rank == cards.at(1).rank) && (cards.at(3).rank == cards.at(4).rank)) || ((cards.at(1).rank == cards.at(2).rank) && (cards.at(3).rank == cards.at(4).rank)))
    {

        pokerRank highPair = cards.at(3).rank;

        pokerRank lowPair = cards.at(1).rank;
        pokerRank nonPair;

        if (cards.at(4).rank != cards.at(3).rank)
        {
            nonPair = cards.at(4).rank;
        }
        else
        {
            if (cards.at(1).rank == cards.at(2).rank)
            {
                nonPair = cards.at(0).rank;
            }
            else
            {
                nonPair = cards.at(2).rank;
            }
        }

        firstTieBreaker = highPair;
        secondTieBreaker = lowPair;
        thirdTieBreaker = nonPair;

        return HoldEmHandRank::twopair;
    }

    // check for pair
    if (findXofaKind(cards, 2, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::pair;
    }

    firstTieBreaker = cards.at(4).rank;
    secondTieBreaker = cards.at(3).rank;
    thirdTieBreaker = cards.at(2).rank;
    fourthTieBreaker = cards.at(1).rank;
    fifthTieBreaker = cards.at(0).rank;

    return HoldEmHandRank::xhigh;
}

// only called when findXofaKind's counter is 2
// check if the type of hand is a three of a kind or two pairs
bool checkFor3Kind(std::vector<Card<Suit, pokerRank>> &hand)
{
    // case 1
    if (hand.at(0).rank == hand.at(1).rank && hand.at(2).rank == hand.at(1).rank)
    {
        return true;
    }

    // case 2

    if (hand.at(1).rank == hand.at(2).rank && hand.at(2).rank == hand.at(3).rank)
    {
        return true;
    }
    // case 3
    if (hand.at(2).rank == hand.at(3).rank && hand.at(4).rank == hand.at(4).rank)
    {
        return true;
    }
    // if we have reached here, then no three pair was found, so it must be two pairs
    return false;
}

bool checkForFullHouse(std::vector<Card<Suit, pokerRank>> &cards, pokerRank &firstTieBreaker)
{

    // two cases: first three same and last two same
    // or first two same and last three same

    if ((cards.at(0).rank == cards.at(1).rank) && (cards.at(1).rank == cards.at(2).rank) && (cards.at(3).rank == cards.at(4).rank))
    {
        firstTieBreaker = cards.at(0).rank;

        return true;
    }

    if ((cards.at(2).rank == cards.at(3).rank) && (cards.at(3).rank == cards.at(4).rank) && (cards.at(0).rank == cards.at(1).rank))
    {
        firstTieBreaker = cards.at(4).rank;

        return true;
    }

    return false;
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

    firstTieBreaker = (*next).rank;

    return true;
}
bool checkForFlush(std::vector<Card<Suit, pokerRank>> &hand)
{
    Suit first = hand.at(0).suit;

    return (std::count_if(hand.begin() + 1, hand.end(), [&first](Card<Suit, pokerRank> card)
                          { return card.suit == first; }) == 4);
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
    if (counter == (x - 1))
    {
        // have a pair
        if (counter == 1)
        {

            pokerRank pairValue;
            std::vector<Card<Suit, pokerRank>>::iterator it = hand.begin();
            std::vector<Card<Suit, pokerRank>>::iterator next = ++hand.begin();

            // find pair rank first
            for (; it != --hand.end(); it++)
            {
                if ((*it).rank == (*next).rank)
                {
                    pairValue = ((*it).rank);
                    break;
                }
                next++;
            }

            // set next highest card tiebreakers
            auto rt = hand.rbegin();

            std::vector<pokerRank> tieBreakValues;

            for (; rt != hand.rend(); ++rt)
            {
                if ((*rt).rank == pairValue)
                {
                    ++rt;
                }
                else
                {
                    tieBreakValues.push_back((*rt).rank);
                }
            }
            firstTieBreaker = pairValue;
            secondTieBreaker = tieBreakValues.at(0);
            thirdTieBreaker = tieBreakValues.at(1);
            fourthTieBreaker = tieBreakValues.at(2);
        }

        if (counter == 2)
        {

            pokerRank threeOfAKindRank = hand.at(2).rank;

            firstTieBreaker = threeOfAKindRank;
        }

        if (counter == 3)
        {
            firstTieBreaker = hand.at(3).rank;
        }

        return true;
    }
    return false;
}

bool operator<(const HoldEmGame::values::hold &x, const HoldEmGame::values::hold &y)
{

    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(0));
    int xSecondTieBreaker = static_cast<int>(x.tieBreakers.at(1));
    int xThirdBreaker = static_cast<int>(x.tieBreakers.at(2));
    int xFourthTieBreaker = static_cast<int>(x.tieBreakers.at(3));
    int xFifthTieBreaker = static_cast<int>(x.tieBreakers.at(4));

    int yFirstTieBreaker = static_cast<int>(y.tieBreakers.at(0));
    int ySecondTieBreaker = static_cast<int>(y.tieBreakers.at(1));
    int yThirdTieBreaker = static_cast<int>(y.tieBreakers.at(2));
    int yFourthTieBreaker = static_cast<int>(y.tieBreakers.at(3));
    int yFifthTieBreaker = static_cast<int>(y.tieBreakers.at(4));

    if (static_cast<int>(x.holdEmHandRank) < static_cast<int>(y.holdEmHandRank))
    {
        return true;
    }

    else if (static_cast<int>(x.holdEmHandRank) > static_cast<int>(y.holdEmHandRank))
    {
        return false;
    }

    else if (xFirstTieBreaker > yFirstTieBreaker)
    {
        return false;
    }
    else if (xFirstTieBreaker < yFirstTieBreaker)
    {
        return true;
    }

    else if (xSecondTieBreaker > ySecondTieBreaker)
    {
        return false;
    }
    else if (xSecondTieBreaker < ySecondTieBreaker)
    {
        return true;
    }
    else if (xThirdBreaker > yThirdTieBreaker)
    {
        return false;
    }
    else if (xThirdBreaker < yThirdTieBreaker)
    {
        return true;
    }
    else if (xFourthTieBreaker > yFourthTieBreaker)
    {
        return false;
    }
    else if (xFourthTieBreaker < yFourthTieBreaker)
    {
        return true;
    }

    else if (xFifthTieBreaker > yFifthTieBreaker)
    {
        return false;
    }
    else if (xFifthTieBreaker < yFifthTieBreaker)
    {
        return true;
    }

    return false;
}
