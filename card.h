
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
private:
	int rank;
	std::string suit;
};

class Hand{
public:

	Hand(int i = 1);
	Hand(const Hand& h);
	Hand& operator=(Hand h);
	virtual ~Hand();
	void swap(Hand& h);
	//void push_back(const Card& h);
	void print();
	//void update_hand();
private:
	Card *theHand;
	size_t size;
};

class Player : public Hand {
public:
	Player(int i = 0);
	int& get_cash();
private:
	int cash;
};


#endif