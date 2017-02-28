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
    std::string get_string();
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
    size_t size();//size of hand
    int Hard_hand();//compute hard value of hand
    int Soft_hand();//compute soft value of hand

public:
    void update_hand();//get another card
    friend std::ostream& operator<<(std::ostream&, const Hand&);//print card in hand
    int value_of_hand() ;//value of the players hand
    bool bust();//did player bust
    virtual double& money() = 0;
    virtual int& bet() = 0;
    virtual bool blackjack() = 0;
    virtual ~Hand();
private:
    std::vector<Card> hand;
    int hard_val_hand;
    int soft_val_hand;
};
/****************************
Dealer Class(Derived Class)
*****************************/
class Dealer : public Hand {
public:
    Dealer();
    void play(bool);
private:
    double& money();
    int& bet();
    bool blackjack();
    double mcash;
    int mbet;
};

/****************************
Random Player Class(Derived Class)
*****************************/
class RandomPlayer : public Hand {
public:
    RandomPlayer(int i = 0);
    void play();
    double& money();//player cash
    int& bet();//player bet
    bool blackjack();//did player get blackjack
private:
    double mcash;
    int mbet;
};


#endif // CARD_H
