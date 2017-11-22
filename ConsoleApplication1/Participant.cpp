#include "stdafx.h"
#include "Participant.h"


Participant::Participant()
{
}


Participant::~Participant()
{
}

void Participant::clearHand() {
	while(!hand.empty()) {
		hand.pop_back();
	}
}

void Participant::addCardToHand(Card card) {
	hand.push_back(card);
}