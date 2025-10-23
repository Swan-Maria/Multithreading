#pragma once
#include <iostream>
#include <mutex>

class BankAccount
{
private:
	unsigned long long balance{ 1000 };
	std::mutex mtx;
public:
	bool deposite(unsigned long long);
	bool withdraw(unsigned long long);
	long long get_balance();

	// ������������� ��� ��������������� ������
	bool deposite_unsafe(unsigned long long);
	bool withdraw_unsafe(unsigned long long);
	long long get_balance_unsafe();
};

