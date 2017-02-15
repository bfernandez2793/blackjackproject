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

void Card::print()
{
	std::cout << "Rank: " << rank << " Suit: " << suit << "\n";
}
int Card::get_rank() {
	return rank;
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

void Hand::print()
{
	for (size_t i = 0; i < hand.size(); ++i)
	{
		hand[i].print();
		std::cout << hand[i].get_rank() << "\n";
	}
	return;
}
void Hand::update_hand()
{
	Card new_card;
	hand.push_back(new_card);
	return;
}

int Hand::Hard_hand()
{
	value_of_hand = 0;
	for (size_t i = 0; i < hand.size(); ++i)
		if(hand[i].get_rank() == 1)
			value_of_hand += 11;
		else
			value_of_hand += hand[i].get_rank();
	return value_of_hand;
}

int Hand::Soft_hand()
{
	soft_val_hand = 0;
	for (size_t i = 0; i < hand.size(); ++i)
		soft_val_hand += hand[i].get_rank();
	return soft_val_hand;
}

/************************
Player Class
(Class to handle player)
*************************/
Player::Player(int i) :cash(i)
{
}
int& Player::get_cash() {
	return cash;
}


