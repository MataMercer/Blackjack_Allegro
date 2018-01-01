#pragma once

#include "Player.h"
#include "Dealer.h"
#include <vector>
#include <allegro5/allegro.h>
using namespace std;
class BlackJack
{
public:
	BlackJack();
	~BlackJack();
	enum CHOICE { DEAL, HIT, SPLIT, STAND, QUIT, SURRENDER, START_NEW_HAND, BET_100, BET_250, BET_500, BET_1000 };
	enum SESSION_STATE { LOBBY, BETTING, DEAL_MODE, PLAYING, QUITTED };
	enum WINNER { PLAYER, DEALER, TIE, NONE };
	bool makeMove(CHOICE choice);
	bool calculate_who_won();
	bool checkBusted();
	bool check_21();
	void updateOptions();
	int getPlayerBalance();
	int getPlayerBet();
	int getDealerHandValue();
	int getPlayerHandValue();
	vector<ALLEGRO_BITMAP*> getPlayer_Hand_Card_Images();
	vector<ALLEGRO_BITMAP*> getDealer_Hand_Card_Images();

	bool* getCanHit(){ return &canHit;}
	bool* getCanDeal() { return &canDeal; }
	bool* getCanStand() { return &canStand; }
	bool* getCanSplit() { return &canSplit; }
	bool* getCanSurrender() { return &canSurrender; }
	bool* getCanBet() { return &canBet; }
	bool* getCanStartNewHand() { return &canStartNewHand; }

	string playerString();
	string dealerString();
	bool playerSplitted();
private:
	bool canHit;
	bool canStand;
	bool canSplit;
	bool canStartNewHand;
	bool canDeal;
	bool canSurrender;
	bool canBet;

	

	Player player;
	Dealer dealer;
	SESSION_STATE session_state;
	WINNER winner;
	WINNER buster;
};

