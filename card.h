
#include <string>
#include <iostream>
#include <vector>
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

class Hand: public Card {
public:
	Hand();
	void print();
	void update_hand();
private:
	std::vector<Card> hand;
};

class Player : public Hand {
public:
	Player(int i = 0);
	int& get_cash();
private:
	int cash;
};


#endif