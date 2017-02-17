#include <iostream>
#include "card.h"
int main() {

	
	Player player1;
	Player Dealer;
	char answer;
	std::cout << "Would you like to play a game of blackjack?";
	std::cin >> answer;
	player1.update_hand();
	Dealer.update_hand();
	bool bust = false;//true if player busts
	/********************************************
					PLAYERS PLAY
	*********************************************/
	do {
		std::cout << "Your Cards: \n";
		player1.print();
		if (player1.bust())
			break;
		std::cout << "Would you like another card?\n";
		std::cin >> answer;
		if (answer == 'y')
			player1.update_hand();

	} while (answer == 'y');
	/************************************************
					DEALERS LOGIC
	*************************************************/
	//get another card if player did not bust
	while ((Dealer.Hard_hand() < 17) && (!player1.bust()))
	{//continue to get cards as long as my hard count is under 17
		if (Dealer.Soft_hand() <= 21 && Dealer.Soft_hand() >= 17)
			break; //if dealer has a soft count that is >= 17 or <=21, stop getting cards
		else
			Dealer.update_hand();
	}
	/*********************************************
						OUTCOME
	**********************************************/
	std::cout << "Dealer Cards: \n";
	Dealer.print();
	
	std::cout << "Player: " << player1.value_of_hand() << " Dealer:" << Dealer.value_of_hand() << "\n";
	std::cout << "Player: " << player1.bust() << " Dealer:" << Dealer.bust() << "\n";
	return 0;
}