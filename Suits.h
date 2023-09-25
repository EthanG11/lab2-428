//Sarah Wilkinson,  s.z.wilkinson@wustl.edu
//Ethan Gray, ethan.gray@wustl.edu
//This file contains the declaration of the Suit enum, which contains the types of suits that cards may have.
//It also declares overloads to the ++ and << operators for the Suit enum.

#pragma once
#include <iostream>

//all possible card suits
enum class Suit {
	clubs,
	diamonds,
	hearts,
	spades,
	undefined
};

//increment the suit of a card
Suit operator++ (Suit& suit);
//print a character respresenting the suit
std::ostream& operator << (std::ostream& write, const Suit& suit);