#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>
#include <random>

std::atomic_int64_t counter = 0;
const long long ARRAY_SIZE = 1000000;

std::vector<int> arr(ARRAY_SIZE, 1);

//void increment_unsafe(volatile long long& c) 
//{
//    volatile long long temp = c;
//    {
//        temp++;
//    }
//    temp = temp + 1;
//    c = temp;
//}

void count(size_t start, size_t end) 
{
    for (size_t i = start; i < end; i++) 
    {
        // if (arr[i] % 2 == 0)
        //     counter++;
        /*increment_unsafe(counter);*/
        counter++;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

int main()
{
    /*std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 100);

    for (size_t i = 0; i < ARRAY_SIZE; i++) 
    {
        arr[i] = dist(gen);
    }*/

    auto threads_number = std::thread::hardware_concurrency();
    std::cout << "Threads number = " << threads_number << '\n';

    std::vector<std::thread> threads;

    for (unsigned int i = 0; i < threads_number; i++) 
    {
        threads.emplace_back(count, i * ARRAY_SIZE / threads_number, (i + 1) * ARRAY_SIZE / threads_number);
    }

    for (auto& th : threads) 
    {
        th.join();
    }

    std::cout << "Counter = " << counter << '\n';
    return 0;
}