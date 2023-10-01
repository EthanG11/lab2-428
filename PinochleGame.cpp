// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations for the PinochleGame class's member functions. 

#include "PinochleGame.h"

//create hands for all players in a pinochle game
PinochleGame::PinochleGame(int argc, const char *argv[]) : Game(argc, argv)
{

    // push back a hand for every player in the game
    for (int i = 0; i < argc; i++)
    {
        CardSet<Suit, pinRank> current;
        hands.push_back(current);
    }
}

//repeatedly shift three cards (called a "packet") from the deck to the hand of each player in turn 
//until all cards in the deck have been distributed
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

//a single round of Pinochle consists of these steps in the following order:
//1. shuffle deck
//2. deal to players
//3. print all cards in players' hands
//4. return all player cards to deck
//5/6. ask to play another round and await input
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

//return all cards in player hands to deck
void PinochleGame::collectHands()
{
    for (std::vector<CardSet<Suit, pinRank>>::iterator i = hands.begin(); i != hands.end(); i++)
    {
        deck.collect(*i);
    }
}

//print every card in every player's hand
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
        counter++;
        j++;
    }
}
