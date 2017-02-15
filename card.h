
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#ifndef CARDS_H
#define CARDS_H

class Card {
public:
	Card();
	void print();//print the information of the card
	int get_rank();//return rank
private:
	int rank;
	std::string suit;
};

class Hand: public Card {
public:
	Hand();
	void print();//print card in hand
	void update_hand();//get another card
	int Hard_hand();//compute hard value of hand
	int Soft_hand();//compute soft value of hand
private:
	std::vector<Card> hand;
	int value_of_hand;
	int soft_val_hand;
};

class Player : public Hand {
public:
	Player(int i = 0);
	int& get_cash();
private:
	int cash;
};


#endif