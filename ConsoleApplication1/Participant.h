#pragma once
#include "Card.h"
#include <vector>
class Participant
{
public:
	Participant();
	~Participant();

	virtual int getHandValue() = 0;
	std::vector<Card> getHand() { return hand; }
	void clearHand();
	void addCardToHand(Card card);

protected:
	
	std::vector<Card> hand;
};

