#include "card.h"

/********************************************
Card class
(class for a single card in a deck)
*********************************************/
Card::Card() {
	//intialize a card
	static time_t timer;
	++timer;
	srand(time(NULL) + timer);
	int r = 1 + rand() % 4;
	switch (r) {
	case 1: suit = "CLUBS"; break;
	case 2: suit = "DIAMONDS"; break;
	case 3: suit = "HEARTS"; break;
	case 4: suit = "SPADES"; break;
	default: break;
	}

	r = 1 + rand() % 10;
	switch (r) {
	case  1: rank = 1; break;
	case  2: rank = 2; break;
	case  3: rank = 3; break;
	case  4: rank = 4; break;
	case  5: rank = 5; break;
	case  6: rank = 6; break;
	case  7: rank = 7; break;
	case  8: rank = 8; break;
	case  9: rank = 9; break;
	case 10: rank = 10; break;
	default: break;
	}
}
int Card::get_rank() {
	return rank;
}
std::ostream& operator<<(std::ostream& out, const Card& c)
{
	out << c.rank << "~" << c.suit << " ";
	return out;
}
/**********************************
Hand Class
(class for handling a players hand)
***********************************/
Hand::Hand()
{
	Card new_card;
	hand.push_back(new_card);
}
int Hand::size()
{
	return hand.size();
}
std::ostream& operator<<(std::ostream& out, const Hand& h)
{
	for (size_t i = 0; i < h.hand.size(); ++i)
		out << h.hand[i];
	out << "\n";
	return out;
}
void Hand::update_hand()
{
	Card new_card;
	hand.push_back(new_card);
	return;
}
int Hand::Soft_hand()
{
	soft_val_hand = 0;
	for (size_t i = 0; i < hand.size(); ++i)
		if(hand[i].get_rank() == 1)
			soft_val_hand += 11;
		else
			soft_val_hand += hand[i].get_rank();
	return soft_val_hand;
}
int Hand::Hard_hand()
{
	hard_val_hand = 0;
	for (size_t i = 0; i < hand.size(); ++i)
		hard_val_hand += hand[i].get_rank();
	return hard_val_hand;
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
/****************************
Player Class
(Class to handle player)
*****************************/
Player::Player(int i ):mcash(i),mbet(i)
{
}
bool Player::blackjack()
{
	if (size()==2 && value_of_hand() == 21)
		return true;
	return false;
}
double& Player::money()
{
	return mcash;
}
int& Player::bet()
{
	return mbet;
}
bool Player::double_down()
{
	if (size() == 2)
	{
		char answer;
		std::cout << "Your Cards: " << *this;

		do {
			std::cout << "Would you like to double down?\n";
			std::cin >> answer;
			std::cin.clear();
			std::cin.ignore(32767, '\n');
		} while (answer != 'n' && answer != 'y');

		if (answer == 'y')
		{
			mbet = 2 * mbet;
			update_hand();
			std::cout << "Your Cards: " <<*this;
			return true;
		}
	}
	return false;
}
/****************************
Dealer Class
*****************************/

Dealer::Dealer()
{
}

void Dealer::play( Player& player)
{
	//get another card if player did not bust
	while ((Hard_hand() < 17) && (!player.bust()))
	{//continue to get cards as long as my hard count is under 17
		if (Soft_hand() <= 21 && Soft_hand() >= 17)
			break; //if dealer has a soft count that is >= 17 or <=21, stop getting cards
		else
			update_hand();
	}
}
