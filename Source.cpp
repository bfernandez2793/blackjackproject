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
	bool bust = false;
	/********************************************
					PLAYERS PLAY
	*********************************************/
	do {
		std::cout << "Your Cards: \n";
		player1.print();
		if (player1.Hard_hand() > 21)
		{
			bust = true;
			break;
		}
		std::cout << "Would you like another card?\n";
		std::cin >> answer;
		if (answer == 'y')
			player1.update_hand();

	} while (answer == 'y');
	/************************************************
					DEALERS LOGIC
	*************************************************/
	while ((Dealer.Hard_hand() < 17) && (!bust))
	{
		if (Dealer.Soft_hand() <= 21 && Dealer.Soft_hand() >= 17)
			break;
		else
			Dealer.update_hand();
	}
	/*********************************************
						OUTCOME
	**********************************************/
	std::cout << "Dealer Cards: \n";
	Dealer.print();
	
	std::cout << "Player: " << player1.value_of_hand() << " Dealer:" << Dealer.value_of_hand() << "\n";
	return 0;
}