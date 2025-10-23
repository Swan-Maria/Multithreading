#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <chrono>
#include <queue>


std::queue<int> item_queue; //конвеер
std::mutex mtx;
std::condition_variable cv;

const int TOTAL_ITEMS{ 20 };

void producer_task()
{
	std::cout << "\n--Produser started its work ---\n";
	for (size_t i = 0; i < TOTAL_ITEMS; i++)
	{
		{
			std::lock_guard<std::mutex> lock(mtx);
			item_queue.push(i);
			std::cout << "Produser pushed packet # " << i << " intj queue. Its size = " <<
				item_queue.size() << "\n";
		}
		cv.notify_one();
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	std::cout << "\n--Produser finished its work ---\n";
}
int consumer_task(int consumer_id)
{

	int processed_count = 0;
	while (processed_count < TOTAL_ITEMS)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [] {return !item_queue.empty(); });
		if (item_queue.empty())
		{
			lock.unlock();
			continue;
		}

		int item = item_queue.front();
		item_queue.pop();
		processed_count++;
		std::cout << "Consumer # " << consumer_id << " took a paket # " << item << "...\n";
		lock.unlock();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	std::cout << "-- Consumer # " << consumer_id << " finished its work --\n";
	return processed_count;
}

int main()
{
	std::cout << "== MAIN THREAD STARTED ==\n";
	std::thread producer(producer_task);
	std::future<int> future1 = std::async(consumer_task, 1);
}