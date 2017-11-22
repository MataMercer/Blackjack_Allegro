#pragma once
#include "Participant.h"
#include "Account.h"
class Player : public Participant
{
public:
	Player();
	~Player();

	int getHandValue();
	int getHand_2_Value();
	bool canSplit();
	void split();
	bool isSplitted();
	Account* getAccount() { return &acc; }
	std::vector<Card> getHand_2() { return hand_2; }
	void addCardToHand_2(Card card);
	void clearHand_2();

private:
	std::vector<Card> hand_2;
	Account acc;
};

