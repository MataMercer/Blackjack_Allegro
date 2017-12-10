#include "stdafx.h"
#include "Account.h"



Account::Account()
{
	bet = 0;
	balance = 0;
}


Account::~Account()
{
}

string Account::getAccountNumber() {
	return accountNumber;
}

void Account::setAccountNumber(string accountNumber) {
	this->accountNumber = accountNumber;
}
