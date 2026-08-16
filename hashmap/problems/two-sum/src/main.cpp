#include "TwoSum.h"

#include "../../../../common/Benchmark.h"

#include <fstream>
#include <iostream>
#include <random>
#include <vector>

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
    const int target = -1;

    std::vector<long long> v1Results;
    std::vector<long long> v2Results;
    std::vector<long long> v3Results;

    std::mt19937 rng(42);

    for (int size : sizes)
    {
        std::vector<int> data(size);

        for (int i = 0; i < size - 2; ++i)
            data[i] = static_cast<int>(rng());

        data[size - 2] = 100;
        data[size - 1] = target - 100;

        v1Results.push_back(
            benchmark::measure(twoSum_v1, data.data(), size, target));

        v2Results.push_back(
            benchmark::measure(twoSum_v2, data.data(), size, target));

        v3Results.push_back(
            benchmark::measure(twoSum_v3, data.data(), size, target));
    }

    std::cout << "\nTwo Sum Benchmark\n";
    std::cout << "Input contains exactly one valid pair.\n\n";

    file << "Two Sum Benchmark\n";
    file << "Input contains exactly one valid pair.\n\n";

    benchmark::printHeader(std::cout, sizes);
    benchmark::printHeader(file, sizes);

    benchmark::printRow(std::cout, "v1 - AllPairs", "O(n^2)", v1Results);
    benchmark::printRow(std::cout, "v2 - HashMap", "O(n)", v2Results);
    benchmark::printRow(std::cout, "v3 - SortedArray", "O(nlogn)", v3Results);

    benchmark::printRow(file, "v1 - AllPairs", "O(n^2)", v1Results);
    benchmark::printRow(file, "v2 - HashMap", "O(n)", v2Results);
    benchmark::printRow(file, "v3 - SortedArray", "O(nlogn)", v3Results);

    std::cout << "\nResults written to " << argv[1] << '\n';

    return 0;
}