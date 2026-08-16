#include "MapSum.h"

#include "../../../../common/Benchmark.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

template <typename Map>
long long benchmarkMapSum(const std::vector<std::string>& keys)
{
    return benchmark::measure([&]()
    {
        Map map;

        for (const auto& key : keys)
            map.insert(key, 1);

        int result = 0;

        for (const auto& key : keys)
            result += map.sum(key.substr(0, 3));

        return result;
    });
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Missing benchmark output path\n";
        return 1;
    }

    std::ofstream file(argv[1]);

    if (!file)
    {
        std::cerr << "Failed to open " << argv[1] << '\n';
        return 1;
    }

    const std::vector<int> sizes = {100, 1000, 10000, 50000};

    std::vector<long long> v0Results;
    std::vector<long long> v1Results;
    std::vector<long long> v2Results;

    for (int size : sizes)
    {
        std::vector<std::string> keys;
        keys.reserve(size);

        for (int i = 0; i < size; ++i)
            keys.push_back("commonprefix" + std::to_string(i));

        v0Results.push_back(
            benchmarkMapSum<MapSum_v0>(keys));

        v1Results.push_back(
            benchmarkMapSum<MapSum_v1>(keys));

        v2Results.push_back(
            benchmarkMapSum<MapSum_v2>(keys));
    }

    std::cout << "\nMap Sum Benchmark\n";
    std::cout << "Insert all keys, then query a 3-character prefix for every key.\n\n";

    file << "Map Sum Benchmark\n";
    file << "Insert all keys, then query a 3-character prefix for every key.\n\n";

    benchmark::printHeader(std::cout, sizes);
    benchmark::printHeader(file, sizes);

    benchmark::printRow(std::cout, "v0 - Naive", "O(NP)", v0Results);
    benchmark::printRow(std::cout, "v1 - HashMap", "O(L)", v1Results);
    benchmark::printRow(std::cout, "v2 - Trie", "O(L)", v2Results);

    benchmark::printRow(file, "v0 - Naive", "O(NP)", v0Results);
    benchmark::printRow(file, "v1 - HashMap", "O(L)", v1Results);
    benchmark::printRow(file, "v2 - Trie", "O(L)", v2Results);

    std::cout << "\nResults written to " << argv[1] << '\n';

    return 0;
}