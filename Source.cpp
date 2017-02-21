#include <iostream>
#include "card.h"
int main() {

	Player player1(100);
	Dealer Dealer;
	RandomPlayer random1(100);
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
		std::cin >> player1.bet();
		std::cin.clear();
		std::cin.ignore(32767, '\n');
	} while (player1.bet() < 0 || player1.bet() > player1.money());
	if (player1.blackjack())//immediate blackjack
		std::cout << "BLACKJACK!!!\n";
	else {
		/************************************************
						PLAYERS PLAY
		*************************************************/
		player1.play();
		random1.play();
		bool bust = false;
		if (player1.bust() && random1.bust())
			bust = true;
		std::cout << random1.value_of_hand() << "\n";
		std::cout << bust << "\n";
		/************************************************
						DEALERS PLAY
		*************************************************/
		Dealer.play(player1);
		}


	/*********************************************
						OUTCOME
	**********************************************/
	std::vector<Hand*> paticipants = { &player1, &Dealer };//base class pointers to derived class objects(polymorphism)

	std::cout << "Dealer Cards: " << Dealer;
	std::cout << "Player: " << paticipants[0]->value_of_hand() << " Dealer:" << paticipants[1]->value_of_hand() << "\n";
	
	if (player1.bust())
	{
		std::cout << "BUST!!! DEALER WINS!!!\n";
		player1.money() -= player1.bet();
	}
	else if (Dealer.bust())
	{
		std::cout << "DEALER BUST!!! PLAYER WINS!!!\n";
		player1.money() += player1.bet();
	}
	else if (player1.value_of_hand() < Dealer.value_of_hand())
	{
		std::cout << "DEALER WINS!!!\n";
		player1.money() -= player1.bet();
	}
	else if (player1.value_of_hand() > Dealer.value_of_hand())
	{
		std::cout << "PLAYER WINS!!!\n";
		player1.money() += player1.bet();
		if (player1.blackjack())
			player1.money() += 0.5*player1.bet();
	}
	else
		std::cout << "TIE\n";
	std::cout << "Players Cash: " << player1.money();
	return 0;
}