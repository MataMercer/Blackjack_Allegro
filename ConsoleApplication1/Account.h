#pragma once
class Account
{
public:
	Account();
	~Account();

	int getBet() { return bet; }
	int getBalance() { return balance; }

	void loseBet() { balance -= bet; }
	void winBet() { balance += bet; }
	void tieBet() { balance += bet / 2; }
	void setBet(int amount) { bet = amount; }
	void resetBalance() { balance = 0; }
private:
	int bet;
	int balance;
};

