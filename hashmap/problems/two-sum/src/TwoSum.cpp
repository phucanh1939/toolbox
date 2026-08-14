#include "TwoSum.h"

#include <unordered_map>
#include <utility>
#include <vector>

std::pair<int, int> twoSum_v1(const int array[], int size, int target)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = i + 1; j < size; ++j)
        {
            if (array[i] + array[j] == target)
                return {i, j};
        }
    }

    return {-1, -1};
}

std::pair<int, int> twoSum_v2(const int array[], int size, int target)
{
    std::unordered_map<int, int> seen;
    seen.reserve(size);

    for (int i = 0; i < size; ++i)
    {
        int number = array[i];
        int needed = target - number;

        auto it = seen.find(needed);

        if (it != seen.end())
            return {i, it->second};

        seen[number] = i;
    }

    return {-1, -1};
}

std::pair<int, int> twoSum_v3(const int array[], int size, int target)
{
    std::vector<std::pair<int, int>> values;
    values.reserve(size);

    for (int i = 0; i < size; ++i)
        values.emplace_back(array[i], i);

    std::sort(values.begin(), values.end());

    int left = 0;
    int right = size - 1;

    while (left < right)
    {
        int sum = values[left].first + values[right].first;

        if (sum == target)
            return {values[left].second, values[right].second};

        if (sum < target)
            ++left;
        else
            --right;
    }

    return {-1, -1};
}