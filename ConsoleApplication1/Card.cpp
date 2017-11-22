#include "stdafx.h"
#include "Card.h"
#include <string>
#include "AssetManager.h"

using namespace std;
Card::Card(CARD_TYPE type, SYMBOL symbol) {
	this->type = type;
	this->symbol = symbol;
	string assetname;
	switch (type) {
	case _2:
		value = 2;
		assetname = "2";
		break;
	case _3:
		value = 3;
		assetname = "3";
		break;
	case _4:
		value = 4;
		assetname = "4";
		break;
	case _5:
		value = 5;
		assetname = "5";
		break;
	case _6:
		value = 6;
		assetname = "6";
		break;
	case _7:
		value = 7;
		assetname = "7";
		break;
	case _8:
		value = 8;
		assetname = "8";
		break;
	case _9:
		value = 9;
		assetname = "9";
		break;
	case JACK:
		value = 10;
		assetname = "jack";
		break;
	case QUEEN:
		value = 10;
		assetname = "queen";
		break;
	case KING:
		value = 10;
		assetname = "king";
		break;
	case ACE:
		value = 11;
		assetname = "ace";
		break;
	}

	switch (symbol) {
	case CLUBS:
		assetname.append("_clubs");
		break;
	case DIAMONDS:
		assetname.append("_diamonds");
		break;
	case HEARTS:
		assetname.append("_hearts");
		break;
	case SPADES:
		assetname.append("_spades");
		break;
	}

	imageFaceUp = AssetManager::getTexture(assetname);
	imageFaceDown = AssetManager::getTexture("facedowncard");
}

Card::Card() {

}


Card::~Card()
{
}

