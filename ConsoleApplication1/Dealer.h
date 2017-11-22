#pragma once
#include "Participant.h"
#include <queue>
#include <vector>
#include "Player.h"

class Dealer : public Participant
{
public:
	Dealer();
	~Dealer();

	void shuffle();
	void deal_a_card(Player &p);
	void deal_a_card();
	int getHandValue();
	void setCardIsFacedDown(bool cond) { cardIsFacedDown = cond; }
	bool getCardIsFacedDown() { return cardIsFacedDown; }
	int getHiddenCardValue();
	bool choose_to_stand_or_not();

private:
	const static int DECK_REFERENCE_SIZE = 48;

	Card deck_reference[DECK_REFERENCE_SIZE] = {
		Card(Card::_2, Card::HEARTS),
		Card(Card::_2, Card::SPADES),
		Card(Card::_2, Card::DIAMONDS),
		Card(Card::_2, Card::CLUBS),

		Card(Card::_3, Card::HEARTS),
		Card(Card::_3, Card::SPADES),
		Card(Card::_3, Card::DIAMONDS),
		Card(Card::_3, Card::CLUBS),

		Card(Card::_4, Card::HEARTS),
		Card(Card::_4, Card::SPADES),
		Card(Card::_4, Card::DIAMONDS),
		Card(Card::_4, Card::CLUBS),

		Card(Card::_5, Card::HEARTS),
		Card(Card::_5, Card::SPADES),
		Card(Card::_5, Card::DIAMONDS),
		Card(Card::_5, Card::CLUBS),

		Card(Card::_6, Card::HEARTS),
		Card(Card::_6, Card::SPADES),
		Card(Card::_6, Card::DIAMONDS),
		Card(Card::_6, Card::CLUBS),

		Card(Card::_7, Card::HEARTS),
		Card(Card::_7, Card::SPADES),
		Card(Card::_7, Card::DIAMONDS),
		Card(Card::_7, Card::CLUBS),

		Card(Card::_8, Card::HEARTS),
		Card(Card::_8, Card::SPADES),
		Card(Card::_8, Card::DIAMONDS),
		Card(Card::_8, Card::CLUBS),

		Card(Card::_9, Card::HEARTS),
		Card(Card::_9, Card::SPADES),
		Card(Card::_9, Card::DIAMONDS),
		Card(Card::_9, Card::CLUBS),

		Card(Card::KING, Card::HEARTS),
		Card(Card::KING, Card::SPADES),
		Card(Card::KING, Card::DIAMONDS),
		Card(Card::KING, Card::CLUBS),

		Card(Card::QUEEN, Card::HEARTS),
		Card(Card::QUEEN, Card::SPADES),
		Card(Card::QUEEN, Card::DIAMONDS),
		Card(Card::QUEEN, Card::CLUBS),

		Card(Card::JACK, Card::HEARTS),
		Card(Card::JACK, Card::SPADES),
		Card(Card::JACK, Card::DIAMONDS),
		Card(Card::JACK, Card::CLUBS),

		Card(Card::ACE, Card::HEARTS),
		Card(Card::ACE, Card::SPADES),
		Card(Card::ACE, Card::DIAMONDS),
		Card(Card::ACE, Card::CLUBS),
	};

	std::priority_queue<Card> deck;
	bool cardIsFacedDown;
	void clearDeck();
};

