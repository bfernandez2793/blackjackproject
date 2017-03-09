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
    int get_rank();//return rank
    std::string get_card_name();
private:
    int mrank;
    std::string msuit;
    std::string mrank_name;
};
/****************************
Hand Class(Base Class)
*****************************/
class Hand{
protected:
    Hand();//protected to prevent an instance of this class
public:
    size_t size();//size of hand
    void update_hand();//get another card
    int value_of_hand() ;//value of the hand
    void reset();//reset hand
    bool bust();//is this a bust hand
    int Hard_hand();//compute hard value of hand
    int Soft_hand();//compute soft value of hand
    std::string get_card_name();
    virtual double& money() = 0;
    virtual int& bet() = 0;
    virtual bool blackjack() = 0;
    virtual ~Hand();
private:
    std::vector<Card> mhand;
    int mhard_val_hand;
    int msoft_val_hand;
    std::string mcard_name;
};
/****************************
Dealer Class(Derived Class)
*****************************/
class Dealer : public Hand {
public:
    Dealer();
    bool blackjack();
private:
    void play();
    double& money();
    int& bet();
    double mcash;
    int mbet;
};

/****************************
Random Player Class(Derived Class)
*****************************/
class RandomPlayer : public Hand {
public:
    RandomPlayer(int i = 0);
    void start();
    void play();
    double& money();//player cash
    int& bet();//player bet
    bool blackjack();//did player get blackjack
private:
    double mcash;
    int mbet;
};


#endif // CARD_H
