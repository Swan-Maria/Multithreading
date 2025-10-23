#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include "Timer.h"

using WordCountMap = std::unordered_map<std::string, size_t>;

void countWordsPart(const std::string& filename, std::streampos start, std::streampos end,
    const std::vector<std::string>& words, WordCountMap& localResult)
{
    std::ifstream file(filename, std::ios::in);
    if (!file)
    {
        std::cerr << "Failed to open file\n";
        return;
    }

    file.seekg(start);

    std::string line;
    while (file.tellg() < end && std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word)
        {
            for (const auto& target : words)
            {
                if (word == target)
                {
                    localResult[word]++;
                }
            }
        }
    }
}

int main() 
{
    Timer timer;
    std::string filename = "LoremIpsum.txt";
    std::vector<std::string> wordsToFind = { "Lorem", "ipsum", "est" };

    std::ifstream file(filename, std::ios::ate | std::ios::binary);
    if (!file) 
    {
        std::cerr << "Failed to open file\n";
        return 1;
    }
    auto filesize = file.tellg();
    file.close();

    int numThreads = std::thread::hardware_concurrency();
    std::vector<std::thread> threads;
    std::vector<WordCountMap> results(numThreads); //separate dictionary for each thread

    std::streampos chunkSize = filesize / numThreads;
    std::streampos start = 0;

    for (int i = 0; i < numThreads; ++i) 
    {
        std::streampos end = (i == numThreads - 1) ? filesize : start + chunkSize;
        threads.emplace_back(countWordsPart, filename, start, end, wordsToFind, std::ref(results[i]));
        start += chunkSize;
    }

    for (auto& t : threads) 
    {
        t.join();
    }

    WordCountMap totalCount;
    for (const auto& localMap : results) 
    {
        for (const auto& pair : localMap) 
        {
            totalCount[pair.first] += pair.second;
        }
    }

    std::cout << "Results:\n";
    for (const auto& w : wordsToFind) 
    {
        std::cout << w << ": " << totalCount[w] << "\n";
    }

    return 0;
}