#include "MapSum.h"

void MapSum_v0::insert(const std::string& key, int val)
{
    _data[key] = val;
}

int MapSum_v0::sum(const std::string& prefix) const
{
    int result = 0;

    for (const auto& [key, value] : _data)
    {
        if (key.size() < prefix.size())
            continue;

        if (key.compare(0, prefix.size(), prefix) == 0)
            result += value;
    }

    return result;
}

void MapSum_v1::insert(const std::string& key, int val)
{
    auto it = _data.find(key);
    int oldVal = it != _data.end() ? it->second : 0;

    std::string prefix;

    for (char c : key)
    {
        prefix += c;
        auto itPrefix = _prefixSums.find(prefix);
        int currentSum = itPrefix != _prefixSums.end() ? itPrefix->second : 0;
        _prefixSums[prefix] = currentSum - oldVal + val;
    }

    _data[key] = val;
}

int MapSum_v1::sum(const std::string& prefix) const
{
    auto it = _prefixSums.find(prefix);
    return it != _prefixSums.end() ? it->second : 0;
}

void MapSum_v2::insert(const std::string& key, int val)
{
    Node* node = _root;
    Node* path[50];
    int pathSize = 0;

    for (char c : key)
    {
        int index = c - 'a';

        if (!node->children[index])
            node->children[index] = new Node();

        node = node->children[index];
        path[pathSize++] = node;
    }

    int delta = val - node->value;
    node->value = val;

    for (int i = 0; i < pathSize; ++i)
        path[i]->prefixSum += delta;
}

int MapSum_v2::sum(const std::string& prefix) const
{
    Node* node = _root;

    for (char c : prefix)
    {
        int index = c - 'a';

        if (!node->children[index])
            return 0;

        node = node->children[index];
    }

    return node->prefixSum;
}
