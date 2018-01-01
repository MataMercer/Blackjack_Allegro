#include "stdafx.h"
#include "BlackJack.h"
#include "Player.h"
#include "Dealer.h"
#include <string>
#include <iostream>
#include "AssetManager.h"
using namespace std;

BlackJack::BlackJack()
{
	session_state = BETTING;
	buster = NONE;
	winner = NONE;
	updateOptions();
}


BlackJack::~BlackJack()
{
}

bool BlackJack::makeMove(CHOICE choice) {
	switch (choice) {
	case DEAL:
		if (canDeal) {
			dealer.deal_a_card(player);
			dealer.deal_a_card(player);
			dealer.deal_a_card();
			dealer.deal_a_card();
			dealer.setCardIsFacedDown(true);
			if (check_21()) {
				session_state = LOBBY;
			}
			else {
				session_state = PLAYING;
			}
		}
		break;
	case HIT:
		if (canHit) {
			dealer.deal_a_card(player);
			if (checkBusted()) {
				session_state = LOBBY;
			}
			else if (check_21()) {
				session_state = LOBBY;
			}

		}
		break;
	case STAND:
		if (canStand) {
			while (!dealer.choose_to_stand_or_not()) {
				dealer.deal_a_card();
			}
			if (checkBusted()) {
				session_state = LOBBY;
			}
			else if (check_21()) {
				session_state = LOBBY;
			}
			else if (calculate_who_won()) {
				session_state = LOBBY;
			}

		}
		break;
	case SPLIT:
		if (canSplit) {
			player.split();
		}
		break;
	case START_NEW_HAND:
		winner = NONE;
		buster = NONE;
		session_state = BETTING;

		break;
	case SURRENDER:
		if (canSurrender) {
			dealer.setCardIsFacedDown(false);
			winner = DEALER;
			buster = NONE;
			player.getAccount()->loseBet();
			session_state = LOBBY;
		}
		break;
	case QUIT:
		session_state = QUITTED;
		return false;
		break;
	case BET_100:
		if (canBet) {
			player.getAccount()->setBet(100);
			session_state = DEAL_MODE;
		}
		break;
	case BET_250:
		if (canBet) {
			player.getAccount()->setBet(250);
			session_state = DEAL_MODE;
		}
		break;
	case BET_500:
		if (canBet) {
			player.getAccount()->setBet(500);
			session_state = DEAL_MODE;
		}
		break;
	case BET_1000:
		if (canBet) {
			player.getAccount()->setBet(1000);
			session_state = DEAL_MODE;
		}
		break;


	}

	updateOptions();
	return true;
}


void BlackJack::updateOptions() {
	switch (session_state) {
	case BETTING:
		player.clearHand();
		player.clearHand_2();
		dealer.clearHand();
		player.getAccount()->setBet(0);
		dealer.shuffle();
		canStartNewHand = false;
		canHit = false;
		canStand = false;
		canSplit = false;
		canDeal = false;
		canSurrender = false;
		canBet = true;
		break;
	case DEAL_MODE:
		canStartNewHand = false;
		canHit = false;
		canStand = false;
		canSplit = false;
		canDeal = true;
		canSurrender = false;
		canBet = false;
		break;
	case PLAYING:
		canStartNewHand = false;
		canHit = true;
		canStand = true;
		canSplit = player.canSplit();
		canDeal = false;
		canSurrender = true;
		canBet = false;
		break;
	case LOBBY:
		canStartNewHand = true;
		canHit = false;
		canStand = false;
		canSplit = false;
		canDeal = false;
		canSurrender = false;
		canBet = false;
		break;
	case QUITTED:

		break;

	}
}

bool BlackJack::calculate_who_won() {
	if (player.isSplitted()) {
		if (player.getHandValue()<21 && player.getHandValue() > (dealer.getTrueHandValue()) && player.getHand_2_Value() < (dealer.getTrueHandValue())) {
			winner = PLAYER;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->winHalfBet();
			return true;
		}
		else if (player.getHandValue() < (dealer.getTrueHandValue()) && player.getHand_2_Value()< 21 && player.getHand_2_Value() > (dealer.getTrueHandValue())) {
			winner = PLAYER;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->winHalfBet();
			return true;
		}
		else if (player.getHandValue() > (dealer.getTrueHandValue()) && player.getHand_2_Value() > (dealer.getTrueHandValue())) {
			winner = PLAYER;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->winBet();
			return true;
		}
		else if (player.getHandValue() < (dealer.getTrueHandValue()) && player.getHand_2_Value() < (dealer.getTrueHandValue())) {
			cout << dealer.getTrueHandValue() << endl;
			winner = DEALER;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->loseBet();
			return true;
		}
		else if (player.getHandValue() == (dealer.getTrueHandValue()) && player.getHand_2_Value() != (dealer.getTrueHandValue())) {
			winner = TIE;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->tieHalfBet();
			return true;
		}
		else if (player.getHandValue() != (dealer.getTrueHandValue()) && player.getHand_2_Value() == (dealer.getTrueHandValue())) {
			winner = TIE;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->tieHalfBet();
			return true;
		}
		else if (player.getHandValue() == (dealer.getTrueHandValue()) && player.getHand_2_Value() == (dealer.getTrueHandValue())) {
			winner = TIE;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->tieBet();
			return true;
		}
		else {
			winner = NONE;
			buster = NONE;
			return false;
		}
	}
	else {
		if (player.getHandValue() > (dealer.getTrueHandValue())) {
			winner = PLAYER;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->winBet();
			return true;
		}
		else if (player.getHandValue() < dealer.getTrueHandValue()) {
			cout << dealer.getTrueHandValue() << endl;
			winner = DEALER;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->loseBet();
			return true;
		}
		else if (player.getHandValue() == (dealer.getTrueHandValue())) {
			winner = TIE;
			buster = NONE;
			dealer.setCardIsFacedDown(false);
			player.getAccount()->tieBet();
			return true;
		}
		else {
			winner = NONE;
			buster = NONE;
			return false;
		}
	}

}

bool BlackJack::checkBusted() {
	if (player.isSplitted()) {
		if (player.getHandValue() > 21 && player.getHand_2_Value() > 21) {
			winner = DEALER;
			buster = PLAYER;
			player.getAccount()->loseBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (dealer.getTrueHandValue() > 21) {
			winner = PLAYER;
			buster = DEALER;
			player.getAccount()->winBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
	}
	else {
		if (player.getHandValue() > 21) {
			winner = DEALER;
			buster = PLAYER;
			player.getAccount()->loseBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (dealer.getTrueHandValue() > 21) {
			winner = PLAYER;
			buster = DEALER;
			player.getAccount()->winBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
	}
	return false;
}

bool BlackJack::check_21() {
	if (player.isSplitted()) {
		if ((player.getHandValue() == 21 || player.getHand_2_Value() == 21) && dealer.getTrueHandValue() == 21) {
			winner = TIE;
			buster = NONE;
			player.getAccount()->tieHalfBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if ((player.getHandValue() == 21 && player.getHand_2_Value() == 21) && dealer.getTrueHandValue() == 21) {
			winner = TIE;
			buster = NONE;
			player.getAccount()->tieBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (player.getHandValue() == 21 || player.getHand_2_Value() == 21) {
			winner = PLAYER;
			buster = NONE;
			player.getAccount()->winHalfBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (player.getHandValue() == 21 && player.getHand_2_Value() == 21) {
			winner = PLAYER;
			buster = NONE;
			player.getAccount()->winBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (dealer.getTrueHandValue() == 21) {
			winner = DEALER;
			buster = NONE;
			player.getAccount()->loseBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
	}
	else {
		if ((player.getHandValue() == 21 && dealer.getTrueHandValue() == 21)) {
			winner = TIE;
			buster = NONE;
			player.getAccount()->tieBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (player.getHandValue() == 21) {
			winner = PLAYER;
			buster = NONE;
			player.getAccount()->winBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
		else if (dealer.getTrueHandValue() == 21) {
			winner = DEALER;
			buster = NONE;
			player.getAccount()->loseBet();
			dealer.setCardIsFacedDown(false);
			return true;
		}
	}
	return false;
}

int BlackJack::getPlayerBalance() {
	return player.getAccount()->getBalance();
}

int BlackJack::getPlayerBet() {
	return player.getAccount()->getBet();
}

vector<ALLEGRO_BITMAP*> BlackJack::getPlayer_Hand_Card_Images() {
	vector<ALLEGRO_BITMAP *> vec;
	if (player.getHand().size() == 0) {
		return vec;
	}
	for (int a = 0; a < player.getHand().size(); a++) {
		vec.push_back(player.getHand()[a].getImageFaceUp());
	}
	if (player.isSplitted()) {
		vec.push_back(AssetManager::getTexture("divider"));
		for (int a = 0; a < player.getHand_2().size(); a++) {
			vec.push_back(player.getHand_2()[a].getImageFaceUp());
		}
	}
	return vec;
}


vector<ALLEGRO_BITMAP*> BlackJack::getDealer_Hand_Card_Images() {
	vector<ALLEGRO_BITMAP *> vec;

	for (int a = 0; a < dealer.getHand().size(); a++) {
		if (a == 0 && dealer.getCardIsFacedDown()) {
			vec.push_back(dealer.getHand()[a].getImageFaceDown());
		}
		else {
			vec.push_back(dealer.getHand()[a].getImageFaceUp());
		}
	}
	return vec;
}

string BlackJack::playerString() {
	string output = "";
	output.append("Hand: ");

	output.append(to_string(player.getHandValue()));
	
	if(player.getHand_2().size()>0) {
		output.append(", Hand 2: ");
		output.append(to_string(player.getHand_2_Value()));
	}
	output.append("\nBet: $");
	output.append(to_string(player.getAccount()->getBet()));
	output.append("\nBalance: $");
	output.append(to_string(player.getAccount()->getBalance()));
	return output;

}

string BlackJack::dealerString() {
	string output ="";
	output.append("Hand: ");
	output.append(to_string(dealer.getHandValue()));
	

	output.append("\nWinner: ");
	switch (winner) {
	case PLAYER:
		output.append("Player");
		break;
	case DEALER:
		output.append("Dealer");
		break;
	case TIE:
		output.append("TIE!");
		break;
	case NONE:
		output.append("Nobody yet");
		break;
	}

	if (buster != NONE) {
		switch (buster) {
		case PLAYER:
			output.append("\nPlayer busted!");
			break;
		case DEALER:
			output.append("\nDealer busted!");
			break;
		}
	}
	return output;
}

bool BlackJack::playerSplitted() {
	return player.isSplitted();
}