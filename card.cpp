#include "card.h"


/********************************************
Card class
(class for a single card in a deck)
*********************************************/
Card::Card() {
	//intialize a card
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
		hand[i].print();
	return;
}
void Hand::update_hand()
{
	Card new_card;
	hand.push_back(new_card);
	return;
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


