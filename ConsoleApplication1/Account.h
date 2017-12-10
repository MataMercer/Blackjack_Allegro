#pragma once
#include <string>

using namespace std;
class Account
{
public:
	Account();
	~Account();

	int getBet() { return bet; }
	int getBalance() { return balance; }

	void loseBet() {
		return;//balance -= bet;
	}
	void winBet() { balance += bet; }
	void tieBet() { balance += bet / 2; }
	void setBet(int amount) { bet = amount; }
	void resetBalance() { balance = 0; }
	string getAccountNumber();
	void setAccountNumber(string accountNumber);
	
private:
	int bet;
	int balance;
	string accountNumber;
};

