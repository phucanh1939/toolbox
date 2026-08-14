#pragma once

#include <chrono>
#include <iomanip>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

namespace benchmark
{
    template <typename Func, typename... Args>
    long long measure(Func function, Args &&...args)
    {
        auto start = std::chrono::high_resolution_clock::now();

        volatile auto result = function(std::forward<Args>(args)...);
        (void)result;

        auto end = std::chrono::high_resolution_clock::now();

        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    inline void printHeader(std::ostream &out, const std::vector<int> &sizes)
    {
        out << std::left << std::setw(30) << "";

        for (int size : sizes)
            out << std::right << std::setw(15) << size;

        out << '\n';
        out << std::string(90, '-') << '\n';
    }

    inline void printRow(std::ostream &out, const char *name, const char *complexity, const std::vector<long long> &results)
    {
        out << std::left << std::setw(20) << name;
        out << std::left << std::setw(10) << complexity;

        for (long long result : results)
            out << std::right << std::setw(12) << result << " us";

        out << '\n';
    }
}