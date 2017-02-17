#include <iostream>
#include "card.h"
int main() {

	Player player1(100);
	Dealer Dealer;
	int bet;
	char answer;
	do
	{
		std::cout << "Would you like to play a game of blackjack?";
		std::cin >> answer;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	} while (answer != 'y' && answer != 'n');
	do
	{
		std::cout << "Place your bet: ";
		std::cin >> bet;
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	} while (bet < 0 || bet > player1.money());
	player1.update_hand();
	Dealer.update_hand();
	if (player1.blackjack())//immediate blackjack
		std::cout << "BLACKJACK!!!\n";
	else {
		/************************************************
						PLAYERS PLAY
		*************************************************/
		do {
			std::cout << "Your Cards: " << player1;
			if (player1.bust())
				break;
			do {
				std::cout << "Would you like another card?\n";
				std::cin >> answer;
				std::cin.clear();
				std::cin.ignore(32767, '\n');
			} while (answer != 'n' && answer != 'y');
			if (answer == 'y')
				player1.update_hand();
		} while (answer == 'y');
		/************************************************
						DEALERS PLAY
		*************************************************/
		Dealer.play(player1);
	}
	/*********************************************
						OUTCOME
	**********************************************/
	std::cout << "Dealer Cards: " << Dealer;
	std::cout << "Player: " << player1.value_of_hand() << " Dealer:" << Dealer.value_of_hand() << "\n";
	if (player1.bust())
	{
		std::cout << "BUST!!! DEALER WINS!!!\n";
		player1.money() -= bet;
	}
	else if (Dealer.bust())
	{
		std::cout << "DEALER BUST!!! PLAYER WINS!!!\n";
		player1.money() += bet;
	}
	else if (player1.value_of_hand() < Dealer.value_of_hand())
	{
		std::cout << "DEALER WINS!!!\n";
		player1.money() -= bet;
	}
	else if (player1.value_of_hand() > Dealer.value_of_hand())
	{
		std::cout << "PLAYER WINS!!!\n";
		player1.money() += bet;
		if (player1.blackjack())
			player1.money() += 0.5*bet;
	}
	else
		std::cout << "TIE\n";

	
	std::cout << "Players Cash: " << player1.money();
	return 0;
}