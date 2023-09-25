#include "HoldEmGame.h"


HoldEmGame::HoldEmGame(int argc, const char *argv[]) : Game(argc, argv), state(HoldEmState::preflop)
{
    // push back a hand for every player in the game
    for (int i = 0; i < argc; i++)
    {
        CardSet<Suit, pokerRank> current;
        hands.push_back(current);
    }
}

void HoldEmGame::deal()
{

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
    if (state == HoldEmState::flop)
    {

        for (int i = 0; i < 3; i++)
        {
            deck >> board;
        }
        state = HoldEmState::turn;
    }
    if (state == HoldEmState::turn)
    {
        deck >> board;
        state = HoldEmState::river;
    }

    if (state == HoldEmState::river)
    {
        deck >> board;
        state = HoldEmState::undefined;
    }
}

int HoldEmGame::play()
{
    bool end_game_flag = false;
    while (!end_game_flag)
    {
        deck.shuffle();
        state = HoldEmState::preflop;
        deal();
        printPlayersCurrentHands();
        deal();
        printBoard("flop");
        deal();
        printBoard("turn");
        deal();
        printBoard("river");

        for (int i = 0; i < static_cast<int>(players.size()); i++)
        {
            deck.collect(hands.at(i));
        }
        deck.collect(board);
        end_game_flag = promptEndGame();
    }
    return SUCCESS;
}

void HoldEmGame::printBoard(const char *segment)
{
    int BOARD_SIZE = 5;
    std::cout << "BOARD(" << segment << "):";
    board.print(std::cout, BOARD_SIZE);
}

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
