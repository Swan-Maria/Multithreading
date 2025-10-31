#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>


std::string check_assignment(std::string student_name, int score_to_get)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return "Student " + student_name + " received " + std::to_string(score_to_get) + " points.";
}

int main() 
{
    srand(time(NULL));

    std::future<std::string> result1 = async(std::launch::async, check_assignment, "Stephan", 60 + rand() % (100 - 60 + 1));
    std::future<std::string> result2 = async(std::launch::async, check_assignment, "Paul", 60 + rand() % (100 - 60 + 1));

    std::cout << "Main thread: It`s evaluaiting the next task...\n";

    std::string r1 = result1.get();
    std::string r2 = result2.get();

    std::cout << r1 << std::endl;
    std::cout << r2 << std::endl;

    return 0;
}
