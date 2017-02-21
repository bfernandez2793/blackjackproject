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
		if (player1.bust() && random1.bust())//if all players bust
			bust = true;
		/************************************************
						DEALERS PLAY
		*************************************************/
		Dealer.play(bust);
		}


	/*********************************************
						OUTCOME
	**********************************************/
	std::vector<Hand*> paticipants = { &player1, &random1, &Dealer };//base class pointers to derived class objects(polymorphism)
	std::cout << "Random player Cards: " << random1;
	std::cout << "Dealer Cards: " << Dealer;
	std::cout << "Player: " << paticipants[0]->value_of_hand() << " Random: " << paticipants[1]->value_of_hand() << " Dealer: " << paticipants[2]->value_of_hand() <<"\n";
	for (int i = 0; i < paticipants.size()-1; ++i) {
		if (paticipants[i]->bust())
		{
			std::cout << "BUST!!!\n";
			paticipants[i]->money() -= paticipants[i]->bet();
		}
		else if (Dealer.bust())
		{
			//std::cout << "DEALER BUST!!! PLAYER WINS!!!\n";
			paticipants[i]->money() += paticipants[i]->bet();
		}
		else if (paticipants[i]->value_of_hand() < Dealer.value_of_hand())
		{
			//std::cout << "DEALER WINS!!!\n";
			paticipants[i]->money() -= paticipants[i]->bet();
		}
		else if (paticipants[i]->value_of_hand() > Dealer.value_of_hand())
		{
			//std::cout << "PLAYER WINS!!!\n";
			paticipants[i]->money() += paticipants[i]->bet();
			if (paticipants[i]->blackjack())
				paticipants[i]->money() += 0.5*paticipants[i]->bet();
		}
		//else
			//std::cout << "TIE\n";
		std::cout << "Player " << i << " Cash: " << paticipants[i]->money() << "\n";
	}
	
	return 0;
}