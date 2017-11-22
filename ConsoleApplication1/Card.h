#pragma once
#include <allegro5/allegro.h>
class Card
{
public:
	enum SYMBOL { HEARTS, SPADES, DIAMONDS, CLUBS };
	enum CARD_TYPE { _2, _3, _4, _5, _6, _7, _8, _9, JACK, QUEEN, KING, ACE };

	Card(CARD_TYPE type, SYMBOL symbol);
	Card();
	~Card();


	int getValue() { return value; }
	SYMBOL getSymbol() { return symbol; }
	CARD_TYPE getType() { return type; }
	int get_deck_loc() { return deck_loc; }
	void set_deck_loc(int deck_loc) { this->deck_loc = deck_loc; }
	ALLEGRO_BITMAP * getImageFaceUp() { return imageFaceUp; }
	ALLEGRO_BITMAP * getImageFaceDown() { return imageFaceDown; }

	friend bool operator<(const Card& lhs, const Card& rhs)
	{
		return lhs.deck_loc < rhs.deck_loc;
	}







private:
	ALLEGRO_BITMAP *imageFaceUp;
	ALLEGRO_BITMAP *imageFaceDown;
	int value;
	SYMBOL symbol;
	CARD_TYPE type;
	int deck_loc = 0;

};

