// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the main function for this deck printing program, as well as the usage statement and exit codes for the program.

#include "pinochle.h"
#include "poker.h"
#include "PinochleGame.h"
#include "HoldEmGame.h"
#include <memory>

using namespace std;

const int minExpectedArgs = 4;
const int SUCCESS = 0;
const int USAGE_ERROR = 1;
const int GAME_NAME = 1;
const int MIN_POKER_PLAYERS = 2;
const int MAX_POKER_PLAYERS = 9;
const int NUM_PINOCHLE_PLAYERS = 4;
const string pin = "Pinochle";
const string poker = "Holdem";

shared_ptr<Game> create(int argc, const char *argv[])
{
    shared_ptr<Game> p;

    const int num_players = (argc - 2);

    string input = argv[GAME_NAME];

    if (input.compare(pin) == 0)
    {

        p = make_shared<PinochleGame>(num_players, argv);
    }

    else if (input.compare(poker) == 0)
    {
        p = make_shared<HoldEmGame>(num_players, argv);
    }

    return p;
}

// usage statement
// ouputted for improper attempts to call the program, such as invalid command line arguments
int usage()
{
    cout << "Usage: ./lab1 GAMENAME Player1 Player2 Player3 ... PlayerN" << endl;

    cout << "HoldEm: 2-9 players" << endl;
    cout << "Pinochle: 4 players" << endl;
    return USAGE_ERROR;
}

int main(int argc, const char *argv[])
{
    // if the user gives any command line arguments with the program name, give the usage statement
    const int num_players = (argc - 2);
    string input = argv[GAME_NAME];

    if (input.compare(pin) == 0)
    {
        if (num_players != NUM_PINOCHLE_PLAYERS)
        {

            return usage();
        }
    }

    else if (input.compare(poker) == 0)
    {
        if (num_players <= MIN_POKER_PLAYERS || num_players >= MAX_POKER_PLAYERS)
        {
            return usage();
        }
    }

    shared_ptr<Game> p = create(argc, argv);
    // pointer non null
    if (p)
    {
        (*p).play();
    }
    // pointer is null
    else
    {
        cout << "Game not successfuly created." << endl;
        return USAGE_ERROR;
    }

    return SUCCESS;
}
