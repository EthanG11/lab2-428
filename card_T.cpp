//Sarah Wilkinson,  s.z.wilkinson@wustl.edu
//Ethan Gray, ethan.gray@wustl.edu
//This file contains the implementation of the overloaded operator << for the Card template.

#include "card_T.h"

//to print a card, print its suit and rank
template<typename S, typename R>
std::ostream& operator<< (std::ostream& write, const Card<S, R>& card) {
	write << card.suit <<  card.rank;

	return write;
}