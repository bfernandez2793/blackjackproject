
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#ifndef CARDS_H
#define CARDS_H
/****************************
Card Class
*****************************/
class Card {
public:
	Card();
	friend std::ostream& operator<<(std::ostream&, const Card&);//print the information of the card
	int get_rank();//return rank
private:
	int rank;
	std::string suit;
};
/****************************
Hand Class(Base Class)
*****************************/
class Hand{
protected:
	Hand();//protected to prevent an instance of this class
	int size();//size of hand
	int Hard_hand();//compute hard value of hand
	int Soft_hand();//compute soft value of hand
	void update_hand();//get another card
public:
	friend std::ostream& operator<<(std::ostream&, const Hand&);//print card in hand
	int value_of_hand() ;//value of the players hand
	bool bust();//did player bust
	virtual double& money() = 0;
	virtual int& bet() = 0;
	virtual bool blackjack() = 0;
private:
	std::vector<Card> hand;
	int hard_val_hand;
	int soft_val_hand;
};
/****************************
Player Class(Derived Class)
*****************************/
class Player : public Hand {
public:
	Player(int i = 0);
	bool blackjack();//did player get blackjack
	double& money();//player cash
	int& bet();
	bool double_down();
	void play();
private:
	double mcash;
	int mbet;
};
/****************************
Dealer Class(Derived Class)
*****************************/
class Dealer : public Hand {
public:
	Dealer();
	void play(bool);
	double& money();
	int& bet();
	bool blackjack();

private:
};
/****************************
Random Player Class(Derived Class)
*****************************/
class RandomPlayer : public Hand {
public:	
	RandomPlayer(int i = 0);
	void play();
	int& bet();
	double& money();
	bool blackjack();
private:
	double mcash;
	int mbet;
};
/****************************
Non-Member Functions
*****************************/
#endif
