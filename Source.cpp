#include <iostream>
#include "card.h"
int main() {

	
	Player player1(100);
	Player Dealer;
	char answer;
	std::cout << "Would you like to play a game of blackjack?";
	std::cin >> answer;
	player1.update_hand();
	do {
		std::cout << "Your Cards: \n";
		player1.print();
		std::cout << "Would you like another card?\n";
		std::cin >> answer;
		if (answer == 'y')
			player1.update_hand();
		else
			Dealer.update_hand();
	} while (answer == 'y');
	std::cout << "Dealer's Cards: \n";
	Dealer.print();
	return 0;
}