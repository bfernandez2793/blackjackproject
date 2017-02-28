#include <iostream>
#include "card.h"
int main() {

	Player player1(100);
	Dealer Dealer;
	int players = 5;
	//Game game(2);
	RandomPlayer random1(100);
	RandomPlayer random2(200);
	std::vector<Hand*> participants = { &player1, &random1, &random2, &Dealer };//base class pointers to derived class objects(polymorphism)

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
		//random1.play();
		//random2.play();
		//game.play();
		bool bust = false;
		if (player1.bust() && game.bust())//if all players bust
			bust = true;
		/************************************************
						DEALERS PLAY
		*************************************************/
		Dealer.play(bust);
		}
	/*********************************************
						OUTCOME
	**********************************************/
	std::cout << "Random player 1 Cards: " << random1;
	std::cout << "Random player 2 Cards: " << random2;
	std::cout << "Dealer Cards: " << Dealer;
	std::cout << "Player: " << participants[0]->value_of_hand() << " Random1: " << participants[1]->value_of_hand() << " Random2: " << participants[2]->value_of_hand() << " Dealer: " << participants[3]->value_of_hand() <<"\n";
	
	for (size_t i = 0; i < participants.size()-1; ++i) {
		if (participants[i]->bust())
		{
			//player has a bust hand
			participants[i]->money() -= participants[i]->bet();
		}
		else if (Dealer.bust())
		{
			//dealer bust
			participants[i]->money() += participants[i]->bet();
		}
		else if (participants[i]->value_of_hand() < Dealer.value_of_hand())
		{
			//player has a losing hand
			participants[i]->money() -= participants[i]->bet();
		}
		else if (participants[i]->value_of_hand() > Dealer.value_of_hand())
		{
			//player has a winning hand
			participants[i]->money() += participants[i]->bet();
			if (participants[i]->blackjack())
				participants[i]->money() += 0.5*participants[i]->bet();
		}
		std::cout << "Player " << i << " Bet: "<< participants[i]->bet() << " Cash: " << participants[i]->money() << "\n";
	}
	
	return 0;
}