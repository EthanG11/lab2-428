// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations of the HoldEmGame class's member functions, as well as functions to check for win states in HoldEm Game.

#include "HoldEmGame.h"

//descriptive int const values to indicate positions to grab cards from hand
int const FIRST_POS = 0;
int const SECOND_POS = 1;
int const THIRD_POS = 2;
int const FOURTH_POS = 3;
int const FIFTH_POS = 4;

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
    //descriptive int vars to indicate num of cards game is working with at a given point in the game
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

            for (int j = 0; j < NUM_FLOP_CARDS; j++)
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

        std::sort(vec.begin(), vec.end());

        for (auto it = vec.begin(); it != vec.end(); it++)
        {
            std::cout << "Player name: " << (*it).playerName << std::endl
                      << " cards: ";
            (*it).cards.print(std::cout, NUM_RIVER_CARDS);
            std::cout << " Hand rank: " << (*it).holdEmHandRank << std::endl;
        }

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

// output appropriate string to describe hand rank
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

// initiate checks for all hand rank types. call appropriate function to check and return corresponding hand rank enum.
HoldEmHandRank HoldEmGame::holdem_hand_evaluation(const CardSet<Suit, pokerRank> &hand, pokerRank &firstTieBreaker, pokerRank &secondTieBreaker, pokerRank &thirdTieBreaker, pokerRank &fourthTieBreaker, pokerRank &fifthTieBreaker)
{
    int const HAND_SIZE = 5;
    int const NUM_CARDS_PAIR = 2;
    int const NUM_CARDS_THREE = 3;
    int const NUM_CARDS_FOUR = 4;
    CardSet<Suit, pokerRank> localHand(hand);

    std::vector<Card<Suit, pokerRank>> CardSet<Suit, pokerRank>::*memberCards = CardSet<Suit, pokerRank>::access_cards();

    std::vector<Card<Suit, pokerRank>> cards = localHand.*memberCards;

    std::sort(cards.begin(), cards.end(), compare_2<Suit, pokerRank>);
    std::sort(cards.begin(), cards.end(), compare_1<Suit, pokerRank>);

    // check for undefined
    if (cards.size() != HAND_SIZE)
    {
        return HoldEmHandRank::undefined;
    }

    // check for straighflush

    if (checkForStraight(cards, firstTieBreaker) && checkForFlush(cards))
    {
        return HoldEmHandRank::straightflush;
    }

    // check for four of a kind
    if (findXofaKind(cards, NUM_CARDS_FOUR, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
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
        firstTieBreaker = cards.at(FIFTH_POS).rank;
        secondTieBreaker = cards.at(FOURTH_POS).rank;
        thirdTieBreaker = cards.at(THIRD_POS).rank;
        fourthTieBreaker = cards.at(SECOND_POS).rank;
        fifthTieBreaker = cards.at(FIRST_POS).rank;

        return HoldEmHandRank::flush;
    }

    // check for straight
    if (checkForStraight(cards, firstTieBreaker))
    {
        return HoldEmHandRank::straight;
    }

    // check for threeofakind
    if (findXofaKind(cards, NUM_CARDS_THREE, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::threeofakind;
    }
    // check for two pair

    if (((cards.at(FIRST_POS).rank == cards.at(SECOND_POS).rank) && (cards.at(THIRD_POS).rank == cards.at(FOURTH_POS).rank)) || ((cards.at(FIRST_POS).rank == cards.at(SECOND_POS).rank) && (cards.at(FOURTH_POS).rank == cards.at(FIFTH_POS).rank)) || ((cards.at(SECOND_POS).rank == cards.at(THIRD_POS).rank) && (cards.at(FOURTH_POS).rank == cards.at(FIFTH_POS).rank)))
    {

        pokerRank highPair = cards.at(FOURTH_POS).rank;

        pokerRank lowPair = cards.at(SECOND_POS).rank;
        pokerRank nonPair;

        if (cards.at(FIFTH_POS).rank != cards.at(FOURTH_POS).rank)
        {
            nonPair = cards.at(FIFTH_POS).rank;
        }
        else
        {
            if (cards.at(SECOND_POS).rank == cards.at(THIRD_POS).rank)
            {
                nonPair = cards.at(FIRST_POS).rank;
            }
            else
            {
                nonPair = cards.at(THIRD_POS).rank;
            }
        }

        firstTieBreaker = highPair;
        secondTieBreaker = lowPair;
        thirdTieBreaker = nonPair;

        return HoldEmHandRank::twopair;
    }

    // check for pair
    if (findXofaKind(cards, NUM_CARDS_PAIR, firstTieBreaker, secondTieBreaker, thirdTieBreaker, fourthTieBreaker))
    {
        return HoldEmHandRank::pair;
    }

    firstTieBreaker = cards.at(FIFTH_POS).rank;
    secondTieBreaker = cards.at(FOURTH_POS).rank;
    thirdTieBreaker = cards.at(THIRD_POS).rank;
    fourthTieBreaker = cards.at(SECOND_POS).rank;
    fifthTieBreaker = cards.at(FIRST_POS).rank;

    return HoldEmHandRank::xhigh;
}

// only called when findXofaKind's counter is 2
// check if the type of hand is a three of a kind or two pairs
bool checkFor3Kind(std::vector<Card<Suit, pokerRank>> &hand)
{
    // case 1
    if (hand.at(FIRST_POS).rank == hand.at(SECOND_POS).rank && hand.at(THIRD_POS).rank == hand.at(SECOND_POS).rank)
    {
        return true;
    }

    // case 2

    if (hand.at(SECOND_POS).rank == hand.at(THIRD_POS).rank && hand.at(THIRD_POS).rank == hand.at(FOURTH_POS).rank)
    {
        return true;
    }
    // case 3
    if (hand.at(THIRD_POS).rank == hand.at(FOURTH_POS).rank && hand.at(FIFTH_POS).rank == hand.at(FIFTH_POS).rank)
    {
        return true;
    }
    // if we have reached here, then no three pair was found, so it must be two pairs
    return false;
}

//return true if hand contains hand rank type full house
bool checkForFullHouse(std::vector<Card<Suit, pokerRank>> &cards, pokerRank &firstTieBreaker)
{
    // two cases: first three same and last two same
    // or first two same and last three same

    if ((cards.at(FIRST_POS).rank == cards.at(SECOND_POS).rank) && (cards.at(SECOND_POS).rank == cards.at(THIRD_POS).rank) && (cards.at(FOURTH_POS).rank == cards.at(FIFTH_POS).rank))
    {
        firstTieBreaker = cards.at(FIRST_POS).rank;

        return true;
    }

    if ((cards.at(THIRD_POS).rank == cards.at(FOURTH_POS).rank) && (cards.at(FOURTH_POS).rank == cards.at(FIFTH_POS).rank) && (cards.at(FIRST_POS).rank == cards.at(SECOND_POS).rank))
    {
        firstTieBreaker = cards.at(FIFTH_POS).rank;

        return true;
    }

    return false;
}

//return true if hand contains hand rank type straight
bool checkForStraight(std::vector<Card<Suit, pokerRank>> &hand, pokerRank &firstTieBreaker)
{

    pokerRank starting = hand.at(FIRST_POS).rank;

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

//check if hand contains hand rank type flush
bool checkForFlush(std::vector<Card<Suit, pokerRank>> &hand)
{
    //descriptive int const to indicate position from which to grab first card
    int const FIRST_CARD_POS = 0;

    Suit first = hand.at(FIRST_CARD_POS).suit;

    return (std::count_if(hand.begin() + 1, hand.end(), [&first](Card<Suit, pokerRank> card)
                          { return card.suit == first; }) == 4);
}

//check for pair, three of kind, and four of kind.
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

    int const PAIR_VALUE = 1;
    int const THREE_OF_A_KIND_VALUE = 2;
    int const FOUR_OF_A_KIND_VALUE = 3;
    if (counter == (x - 1))
    {
        // have a pair
        if (counter == PAIR_VALUE)
        {
            //descriptive int const vals to indicate what positions to always grab the highest value card for tiebreaker testing
            int const CONST_HIGH_POS_TWO_1 = 0;
            int const CONST_HIGH_POS_TWO_2 = 1;
            int const CONST_HIGH_POS_TWO_3 = 2;

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
            secondTieBreaker = tieBreakValues.at(CONST_HIGH_POS_TWO_1);
            thirdTieBreaker = tieBreakValues.at(CONST_HIGH_POS_TWO_2);
            fourthTieBreaker = tieBreakValues.at(CONST_HIGH_POS_TWO_3);
        }

        if (counter == THREE_OF_A_KIND_VALUE)
        {
            //descriptive int const val to indicate what position to always grab the highest value card for tiebreaker testing
            int const CONST_HIGH_POS_THREE = 2;

            pokerRank threeOfAKindRank = hand.at(CONST_HIGH_POS_THREE).rank;

            firstTieBreaker = threeOfAKindRank;
        }

        if (counter == FOUR_OF_A_KIND_VALUE)
        {
            //descriptive int const val to indicate what position to always grab the highest value card for tiebreaker testing
            int const CONST_HIGH_POS_FOUR = 3;

            firstTieBreaker = hand.at(CONST_HIGH_POS_FOUR).rank;
        }

        return true;
    }
    return false;
}

// overloaded < to compare nested hold struct, which is inside values struct, which is inside the HoldEmGame class
bool operator<(const HoldEmGame::values::hold &x, const HoldEmGame::values::hold &y)
{
    //descriptive int const vals to always grab the tiebreaker cards at specific position in hand
    int const TIEBREAK_POS1 = 0;
    int const TIEBREAK_POS2 = 1;
    int const TIEBREAK_POS3 = 2;
    int const TIEBREAK_POS4 = 3;
    int const TIEBREAK_POS5 = 4;

    int xFirstTieBreaker = static_cast<int>(x.tieBreakers.at(TIEBREAK_POS1));
    int xSecondTieBreaker = static_cast<int>(x.tieBreakers.at(TIEBREAK_POS2));
    int xThirdBreaker = static_cast<int>(x.tieBreakers.at(TIEBREAK_POS3));
    int xFourthTieBreaker = static_cast<int>(x.tieBreakers.at(TIEBREAK_POS4));
    int xFifthTieBreaker = static_cast<int>(x.tieBreakers.at(TIEBREAK_POS5));

    int yFirstTieBreaker = static_cast<int>(y.tieBreakers.at(TIEBREAK_POS1));
    int ySecondTieBreaker = static_cast<int>(y.tieBreakers.at(TIEBREAK_POS2));
    int yThirdTieBreaker = static_cast<int>(y.tieBreakers.at(TIEBREAK_POS3));
    int yFourthTieBreaker = static_cast<int>(y.tieBreakers.at(TIEBREAK_POS4));
    int yFifthTieBreaker = static_cast<int>(y.tieBreakers.at(TIEBREAK_POS5));

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
