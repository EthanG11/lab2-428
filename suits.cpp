// Sarah Wilkinson,  s.z.wilkinson@wustl.edu
// Ethan Gray, ethan.gray@wustl.edu
// This file contains the implementations of the Suits enum's overloaded operators << and ++.

#include "Suits.h"

using namespace std;

// print the symbol corresponding to the given suit. Undefined suits have ? symbol.
ostream &operator<<(ostream &write, const Suit &suit)
{
    char suitSymbol = ' ';
    switch (suit)
    {
    case Suit::clubs:
        suitSymbol = 'C';
        break;
    case Suit::diamonds:
        suitSymbol = 'D';
        break;
    case Suit::hearts:
        suitSymbol = 'H';
        break;
    case Suit::spades:
        suitSymbol = 'S';
        break;
    case Suit::undefined:
        suitSymbol = '?';
        break;
    }

    write << suitSymbol << " ";

    return write;
}

// increment the suit to the next highest suit. If it is already the highest suit, then increment it into undefined.
Suit operator++(Suit &suit)
{
    // if the given suit is undefined, do not change the suit. Otherwise, increment the suit by one and return it.
    suit = (suit == Suit::undefined) ? suit : static_cast<Suit>(static_cast<int>(suit) + 1);
    return suit;
}