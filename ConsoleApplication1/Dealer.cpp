
#include "stdafx.h"
#include "Dealer.h"
#include <time.h> 


Dealer::Dealer()
{
}


Dealer::~Dealer()
{
}

int Dealer::getHandValue() {
	if (hand.size() == 0) {
		return 0;
	}

	int total = 0;
	int aceCounter = 0;
	for (int a = 0; a < hand.size(); a++) {
		if (hand[a].getType() == Card::ACE) {
			aceCounter++;
		}
		if (!(cardIsFacedDown && a == 0)) {

			total += hand[a].getValue();
		}

	}

	while (total > 21 && aceCounter > 0) {
		total -= 10;
		aceCounter--;
	}

	return total;
}

int Dealer::getTrueHandValue() {
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

void Dealer::shuffle() {
	srand(time(NULL));
	clearDeck();
	std::vector<int> locvec;

	for (int a = 0; a < DECK_REFERENCE_SIZE; a++) {
		Card card(deck_reference[a]);

		int randloc = -1;
		while (randloc == -1) {
			randloc = rand() % DECK_REFERENCE_SIZE;
			for (int b = 0; b < locvec.size(); b++) {
				if (locvec[b] == randloc) {
					randloc = -1;
				}
			}
		}

		card.set_deck_loc(randloc);
		locvec.push_back(randloc);
		deck.push(card);

	}
}

void Dealer::deal_a_card(Player& p) {
	Card card(deck.top());
	deck.pop();

	p.addCardToHand(card);
	if (p.isSplitted()) {
		Card card2(deck.top());
		deck.pop();
		p.addCardToHand_2(card2);
	}

}

void Dealer::deal_a_card() {
	Card card(deck.top());
	deck.pop();
	hand.push_back(card);
}

bool Dealer::choose_to_stand_or_not() {
	if (getTrueHandValue() >= 17) {
		return true;
	}
	else {
		return false;
	}

}

int Dealer::getHiddenCardValue() {
	if (cardIsFacedDown) {
		return hand[0].getValue();
	}
	else {
		return 0;
	}
}

void Dealer::clearDeck() {
	for (int a = 0; a < deck.size(); a++) {
		deck.pop();
	}
}