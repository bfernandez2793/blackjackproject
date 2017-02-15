
#include <string>
#include <iostream>
#ifndef CARDS_H
#define CARDS_H

class Card {
public:
	Card();
	void print();//print the information of the card
private:
	int rank;
	std::string suit;
};


#endif