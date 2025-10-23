#include <iostream>
#include <thread>
#include <vector>
#include "BankAccount.h"
#include "Timer.h"


const size_t ITERATIONS = 100;
const size_t NUM_THREADS = 100;	

void thread_task(BankAccount& acc, int iterations)
{
	for (size_t i = 0; i < iterations; i++)
	{
		acc.deposite(10);
		acc.withdraw(10);
	}
}

int main()
{
	{
		Timer timer;
		BankAccount account;
		std::cout << "Start: ";
		std::cout << account.get_balance();
		std::vector<std::thread> threads;
		for (size_t i = 0; i < NUM_THREADS; i++)
		{
			threads.emplace_back(thread_task, std::ref(account), ITERATIONS);
		}
		for (auto& t : threads)
		{
			t.join();
		}
		std::cout << "\nFinish: ";
		std::cout << account.get_balance();
	}

	{
		Timer timer;
		BankAccount account;
		std::cout << "\n\nStart (unsafe): ";
		std::cout << account.get_balance_unsafe();

		// Вызываем последовательно в цикле, а не в потоках
		for (size_t i = 0; i < ITERATIONS * NUM_THREADS; i++)
		{
			account.deposite_unsafe(10);
			account.withdraw_unsafe(10);
		}

		std::cout << "\nFinish (unsafe): ";
		std::cout << account.get_balance_unsafe();
	}

	return 0;
}