#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <chrono>
#include <random>
#include <mutex>
#include "Timer.h"

std::queue<std::string> orders;
std::mutex mtx;

const int ITEM_NUMBERS = 20;

const int PRODUCERS_NUMBER = 5;

const int CONSUMERS_NUMBERS = 4;

void producer(int id)
{
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(50, 200);

	for (int i = 0; i < ITEM_NUMBERS; i++)
	{
		auto rand_number = dist(gen);
		std::this_thread::sleep_for(std::chrono::milliseconds(rand_number));
		auto order = "Order # " + std::to_string(id) + " " + std::to_string(i) + " " + std::to_string(rand_number);
		{
			std::lock_guard<std::mutex> lock(mtx);
			orders.push(order);
		}
		//виміряти загальний час виконання програми при такому способі блокування;
		//змінити точку блокування таким чином, щоб блокувався весь цикл відразу, порівняти час виконання
		std::cout << "Producer # " << id << " pushed " << order << '\n';
	}
}


void consumer(int id)
{

	while (true)
	{
		std::string order;

		{
			std::lock_guard<std::mutex> lock(mtx);
			if (!orders.empty())
			{
				order = orders.front();
				orders.pop();
			}
		}

		if (!orders.empty())
		{
			std::cout << "Consumer # " << id << " popped " << order << '\n';

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
		else
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
		//.....
	}
}


int main()
{
	Timer timer;

	std::vector<std::thread> produsers, consumers;

	for (int i = 0; i < PRODUCERS_NUMBER; i++)
	{
		produsers.emplace_back(producer, i + 1);
	}

	for (int i = 0; i < CONSUMERS_NUMBERS; i++)
	{
		consumers.emplace_back(consumer, i + 1);
	}

	for (auto& p : produsers)
	{
		p.join();
	}

	for (auto& c : consumers)
	{
		c.join();
	}

	return 0;
}