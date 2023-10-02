// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations of the HoldEmGame class's member functions.

#include "HoldEmGame.h"

//create a hand for each player in the game
HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop)
{
    // push back a hand for every player in the game
    for (int i = 0; i < argc; i++)
    {
        CardSet<Suit, pokerRank> current;
        hands.push_back(current);
    }
}

//distribute the next card(s) according to the current state of the game.
void HoldEmGame::deal()
{
    //if the state is preflop, then deal two cards to each player and then increment state
    if (state == HoldEmState::preflop)
    {

        for (int i = 0; i <static_cast<int>(players.size()); i++)
        {
            deck >> hands.at(i);
        }
        for (int i = 0; i <static_cast<int>(players.size()); i++)
        {
            deck >> hands.at(i);
        }

        state = HoldEmState::flop;
    }
    //if the state is flop, then deal three cards to the board and increment state
    else if (state == HoldEmState::flop)
    {

        for (int i = 0; i < 3; i++)
        {
            deck >> board;
        }
        state = HoldEmState::turn;
    }
    //if the state is turn, then deal three cards to the board and increment state
   else if (state == HoldEmState::turn)
    {
        deck >> board;
        state = HoldEmState::river;
    }
    //if the state is river, then deal three cards to the board and increment state
   else if (state == HoldEmState::river)
    {
        deck >> board;
        state = HoldEmState::undefined;
    }
}

//a single play in a Texas Hold Em game consists of these steps in the following order:
//1. shuffle the deck
//2. set the state to preflop
//3. deal two cards to each hand and proceed to flop
//4. print each player's cards
//5. deal three cards to the board and proceed to turn
//6. print all cards on the board
//7. deal one more card to the board and proceed to river
//8. print all cards on the board
//9. deal one more card to the board 
//10. print all cards on the board
//11. collect all players' cards and return them to deck
//12. collect all board cards and return them to deck
//13/14. ask to play another round and await input
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
        printBoard("flop",NUM_FLOP_CARDS );
        deal();
        printBoard("turn",NUM_TURN_CARDS);
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

//print every card on the board
void HoldEmGame::printBoard(const char *segment, int numCards)
{
    std::cout << "BOARD(" << segment << "):";
    board.print(std::cout, numCards);
}

//print every card in each of the players hands
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
