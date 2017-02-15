#include <iostream>
#include "card.h"
int main() {

	
	Player player1(100);
	Player Dealer;
	char answer;
	std::cout << "Would you like to play a game of blackjack?";
	std::cin >> answer;
	player1.update_hand();
	Dealer.update_hand();
	do {
		std::cout << "Your Cards: \n";
		player1.print();
		if (player1.Soft_hand() > 21)
			break;
		std::cout << "Would you like another card?\n";
		std::cin >> answer;
		if (answer == 'y')
			player1.update_hand();

	} while (answer == 'y');
	
	while ((Dealer.Soft_hand() < 17) && (player1.Soft_hand() < 21))
	{
		if (Dealer.Soft_hand() > 21)
			break;
		else if (Dealer.Hard_hand() <= 21 && Dealer.Hard_hand() >= 17)
			break;
		else
			Dealer.update_hand();
	}
	
	if (player1.Soft_hand() > 21)
		std::cout << "BUST!!! Dealer Wins\n";
	else if (Dealer.Hard_hand() > player1.Soft_hand())
	{
		std::cout << "Dealer wins!!!\nDealer's Cards: \n";
		Dealer.print();
	}
	else
	{
		std::cout << "Player Wins!!";
		std::cout << "Player Cards: \n";
		player1.print();
		std::cout << "Dealer Cards: \n";
		Dealer.print();

	}
	return 0;
}