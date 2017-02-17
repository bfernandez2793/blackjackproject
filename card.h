
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#ifndef CARDS_H
#define CARDS_H

class Card {
public:
	Card();
	friend std::ostream& operator<<(std::ostream&, const Card&);//print the information of the card
	int get_rank();//return rank
private:
	int rank;
	std::string suit;
};

class Hand{
protected:
	Hand();//protected to prevent an instance of this class
public:
	friend std::ostream& operator<<(std::ostream&, const Hand&);//print card in hand
	void update_hand();//get another card
	int Hard_hand();//compute hard value of hand
	int Soft_hand();//compute soft value of hand
private:
	std::vector<Card> hand;
	int hard_val_hand;
	int soft_val_hand;
};

class Player : public Hand {
public:
	Player(int i = 0);
	int value_of_hand();//value of the players hand
	bool bust();//did player bust
	int& money();
private:
	int cash;
};



#endif