#include "card.h"

/********************************************
Card class
(class for a single card in a deck)
*********************************************/
Card::Card()
{
    //intialize a card
    static time_t timer;
    ++timer;
    srand(time(NULL) + timer);
    int r = 1 + rand() % 4;
    switch (r) {
    case 1: msuit = "clubs"; break;
    case 2: msuit = "diamonds"; break;
    case 3: msuit = "hearts"; break;
    case 4: msuit = "spades"; break;
    default: break;
    }

    r = 1 + rand() % 13;
    switch (r) {
    case  1:
        mrank = 1;
        mrank_name = "ace";
        break;
    case  2:
        mrank = 2;
        mrank_name = "2";
        break;
    case  3:
        mrank = 3;
        mrank_name = "3";
        break;
    case  4:
        mrank = 4;
        mrank_name = "4";
        break;
    case  5:
        mrank = 5;
        mrank_name = "5";
        break;
    case  6:
        mrank = 6;
        mrank_name = "6";
        break;
    case  7:
        mrank = 7;
        mrank_name = "7";
        break;
    case  8:
        mrank = 8;
        mrank_name = "8";
        break;
    case  9:
        mrank = 9;
        mrank_name = "9";
        break;
    case 10:
        mrank = 10;
        mrank_name = "10";
        break;
    case 11:
        mrank = 10;
        mrank_name = "jack";
        break;
    case 12:
        mrank = 10;
        mrank_name = "queen";
        break;
    case 13:
        mrank = 10;
        mrank_name = "king";
        break;
    default: break;
    }
}
int Card::get_rank() {
    return mrank;
}
std::string Card::get_card_name()
{
    return mrank_name + "_of_" + msuit;
}
/**********************************
Hand Class
(class for handling a players hand)
***********************************/
Hand::Hand()
{
}
size_t Hand::size()
{
    return mhand.size();
}
void Hand::update_hand()
{
    Card new_card;
    mcard_name = new_card.get_card_name();
    mhand.push_back(new_card);
    return;
}
int Hand::Soft_hand()
{
    msoft_val_hand = 0;
    for (size_t i = 0; i < mhand.size(); ++i)
        if(mhand[i].get_rank() == 1)
            msoft_val_hand += 11;
        else
            msoft_val_hand += mhand[i].get_rank();
    return msoft_val_hand;
}
int Hand::Hard_hand()
{
    mhard_val_hand = 0;
    for (size_t i = 0; i < mhand.size(); ++i)
        mhard_val_hand += mhand[i].get_rank();
    return mhard_val_hand;
}
int Hand::value_of_hand()
{//if my soft hand is under 21 use the soft count else use the hard count
    if (Soft_hand() <= 21)
        return Soft_hand();
    return Hard_hand();

}
bool Hand::bust()
{
    if (value_of_hand() > 21)
        return true;
    return false;
}
std::string Hand::get_card_name(){
    return mcard_name;
}
void Hand::reset(){
    mhand.clear();
}
Hand::~Hand()
{
}
/****************************
Dealer Class
*****************************/
Dealer::Dealer():mcash(0),mbet(0)
{
}
void Dealer::play()
{
    return;
}
double& Dealer::money()
{
    return mcash;
}
int& Dealer::bet()
{
    return mbet;
}
bool Dealer::blackjack()
{
    if (size() == 2 && value_of_hand() == 21)
        return true;
    return false;
}
/****************************
Random Player Class
*****************************/
RandomPlayer::RandomPlayer(int i):mcash(i)
{
    mbet = 1 + rand() % static_cast<int>(mcash/2);
}
void RandomPlayer::start(){

}
void RandomPlayer::play()
{
    update_hand();
    update_hand();
    while (Hard_hand() < 17)
    {//continue to get cards as long as hard count is under 17
        if (Soft_hand() <= 21 && Soft_hand() >= 17)
            break; //if player has a soft count that is >= 17 or <=21, stop getting cards
        else
            update_hand();
    }
}
double& RandomPlayer::money()
{
    return mcash;
}
int& RandomPlayer::bet()
{
    return mbet;
}
bool RandomPlayer::blackjack()
{
    if (size() == 2 && value_of_hand() == 21)
        return true;
    return false;
}

