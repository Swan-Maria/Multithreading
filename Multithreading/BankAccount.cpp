#include "BankAccount.h"

bool BankAccount::deposite(unsigned long long amount)
{
	std::lock_guard<std::mutex> lock(mtx);
	balance += amount;
	return true;
}

bool BankAccount::withdraw(unsigned long long amount)
{
	std::lock_guard<std::mutex> lock(mtx);
	if (amount < 0)
	{
		return false;
	}
	if (balance >= amount)
	{
		balance -= amount;
	}
	else
	{
		std::cout << "You have to few monet on balance...\n";
		return false;
	}
	return true;
}

long long BankAccount::get_balance()
{
	std::lock_guard<std::mutex> lock(mtx);
	//std::cout << "There is " << balance << " on your balance...\n";
	return balance;
}

// Ќебезопаснные дл€ многопоточности методы
bool BankAccount::deposite_unsafe(unsigned long long amount)
{
	balance += amount;
	return true;
}

bool BankAccount::withdraw_unsafe(unsigned long long amount)
{
	if (amount < 0)
	{
		return false;
	}
	if (balance >= amount)
	{
		balance -= amount;
	}
	else
	{
		std::cout << "You have too few money on balance...\n";
		return false;
	}
	return true;
}

long long BankAccount::get_balance_unsafe()
{
	return balance;
}