#include "ContainsDuplicates.h"

#include <algorithm>
#include <unordered_set>

bool containDuplicates_v1(const int array[], int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = i + 1; j < size; ++j)
            if (array[i] == array[j]) return true;

    return false;
}

bool containDuplicates_v2(int array[], int size)
{
    std::sort(array, array + size);

    for (int i = 0; i < size - 1; ++i)
        if (array[i] == array[i + 1]) return true;

    return false;
}

bool containDuplicates_v3(const int array[], int size)
{
    std::unordered_set<int> seen;
    seen.reserve(size);

    for (int i = 0; i < size; ++i)
    {
        if (seen.find(array[i]) != seen.end())
            return true;

        seen.emplace(array[i]);
    }

    return false;
}
