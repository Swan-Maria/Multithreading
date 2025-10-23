#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

const size_t SIZE = 1'000'000;
int counter{ 0 };

void count(const std::vector<int>& arr, size_t start, size_t end)
{
	for (size_t i = start; i < end; ++i) {
		if (arr[i] % 2 == 0) {
			++counter;
		}
	}
	std::this_thread::sleep_for(std::chrono::microseconds(100));
}
int main()
{
	srand(time(NULL));
	std::vector<int> array(SIZE);
	for (size_t i = 0; i < SIZE; i++)
	{
		array[i] = rand();
	}

	unsigned int threads_number = std::thread::hardware_concurrency();

	std::vector<std::thread> threads(threads_number);

	for (unsigned int i = 0; i < threads_number; ++i)
	{
		threads.emplace_back(count, i/threads_number*SIZE, (i+1)/threads_number*SIZE);
	}

	for (auto& t : threads)
	{
		t.join();
	}

	std::cout << threads_number << std::endl;
	std::cout << counter << std::endl;
}