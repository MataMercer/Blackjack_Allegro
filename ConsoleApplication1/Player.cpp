#include "stdafx.h"
#include "Player.h"



Player::Player()
{
}


Player::~Player()
{
}

int Player::getHandValue() {
	if (hand.size() == 0) {
		return 0;
	}

	int total = 0;
	int aceCounter = 0;
	for (int a = 0; a < hand.size(); a++) {
		if (hand[a].getType() == Card::ACE) {
			aceCounter++;
		}
		total += hand[a].getValue();
	}

	while (total > 21 && aceCounter > 0) {
		total -= 10;
		aceCounter--;
	}

	return total;
}

int Player::getHand_2_Value() {
	if (hand_2.size() == 0) {
		return 0;
	}


	int total = 0;
	int aceCounter = 0;
	for (int a = 0; a < hand_2.size(); a++) {
		if (hand_2[a].getType() == Card::ACE) {
			aceCounter++;
		}
		total += hand_2[a].getValue();
	}

	while (total > 21 && aceCounter > 0) {
		total -= 10;
		aceCounter--;
	}

	return total;
}

bool Player::canSplit() {
	if (hand.size() == 2 && hand_2.size() == 0 &&
		hand[0].getValue() == hand[1].getValue()) {
		return true;
	}
	return false;
}

void Player::split() {
	if (canSplit()) {
		Card card(hand[0]);
		hand.pop_back();
		hand_2.push_back(card);
	}
}

bool Player::isSplitted() {
	if (hand_2.size() == 0) {
		return false;
	}
	else {
		return true;
	}
}

void Player::addCardToHand_2(Card card) {
	hand_2.push_back(card);
}

void Player::clearHand_2() {
	while (!hand_2.empty()) {
		hand_2.pop_back();
	}
}