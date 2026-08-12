#include "ContainsDuplicates.h"

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

template <typename Func>
long long benchmark(Func function, const std::vector<int>& data)
{
    std::vector<int> copy = data;

    auto start = std::chrono::high_resolution_clock::now();

    volatile bool result = function(copy.data(), static_cast<int>(copy.size()));
    (void)result;

    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void printHeader(std::ostream& out, const std::vector<int>& sizes)
{
    out << std::left << std::setw(14) << "";

    for (int size : sizes)
        out << std::right << std::setw(11) << size << "    ";

    out << '\n';
    out << std::string(74, '-') << '\n';
}

void printRow(std::ostream& out, const char* name, const std::vector<long long>& results)
{
    out << std::left << std::setw(14) << name;

    for (long long result : results)
        out << std::right << std::setw(11) << result << " us";

    out << '\n';
}

int main(int argc, char* argv[])
{
    const std::vector<int> sizes = {100, 1000, 10000, 50000};

    if (argc < 2)
    {
        std::cerr << "Missing benchmark output path\n";
        return 1;
    }

    std::ofstream file(argv[1]);

    if (!file)
    {
        std::cerr << "Failed to open benchmark.txt\n";
        return 1;
    }

    std::vector<long long> v1Results;
    std::vector<long long> v2Results;
    std::vector<long long> v3Results;

    for (int size : sizes)
    {
        std::vector<int> data(size);

        for (int i = 0; i < size; ++i)
            data[i] = i;

        v1Results.push_back(benchmark(containDuplicates_v1, data));
        v2Results.push_back(benchmark(containDuplicates_v2, data));
        v3Results.push_back(benchmark(containDuplicates_v3, data));
    }

    std::cout << "\nContains Duplicate Benchmark\n";
    std::cout << "Input contains no duplicates.\n\n";

    file << "Contains Duplicate Benchmark\n";
    file << "Input contains no duplicates.\n\n";

    printHeader(std::cout, sizes);
    printHeader(file, sizes);

    printRow(std::cout, "v1 O(n^2)", v1Results);
    printRow(std::cout, "v2 O(nlogn)", v2Results);
    printRow(std::cout, "v3 O(n)", v3Results);

    printRow(file, "v1 O(n^2)", v1Results);
    printRow(file, "v2 O(nlogn)", v2Results);
    printRow(file, "v3 O(n)", v3Results);

    std::cout << "\nResults written to benchmark.txt\n";

    return 0;
}