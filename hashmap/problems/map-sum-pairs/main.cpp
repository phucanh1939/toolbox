#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class HashMapPrefixSums
{
public:
    void insert(const std::string& key, int value)
    {
        auto it = _data.find(key);
        int oldValue = it != _data.end() ? it->second : 0;

        std::string prefix;
        prefix.reserve(key.size());

        for (char c : key)
        {
            prefix += c;
            _prefixSums[prefix] += value - oldValue;
        }

        _data[key] = value;
    }

    int sum(const std::string& prefix) const
    {
        auto it = _prefixSums.find(prefix);
        return it != _prefixSums.end() ? it->second : 0;
    }

private:
    std::unordered_map<std::string, int> _data;
    std::unordered_map<std::string, int> _prefixSums;
};

struct TrieNode
{
    TrieNode* children[26]{};
    int value = 0;
    int prefixSum = 0;
};

class Trie
{
public:
    Trie() : _root(new TrieNode) {}

    void insert(const std::string& key, int value)
    {
        TrieNode* node = _root;
        std::vector<TrieNode*> path;
        path.reserve(key.size());

        for (char c : key)
        {
            int index = c - 'a';

            if (!node->children[index])
                node->children[index] = new TrieNode;

            node = node->children[index];
            path.push_back(node);
        }

        int delta = value - node->value;
        node->value = value;

        for (TrieNode* current : path)
            current->prefixSum += delta;
    }

    int sum(const std::string& prefix) const
    {
        TrieNode* node = _root;

        for (char c : prefix)
        {
            int index = c - 'a';

            if (!node->children[index])
                return 0;

            node = node->children[index];
        }

        return node->prefixSum;
    }

private:
    TrieNode* _root;
};

std::vector<std::string> makeSharedPrefixData(int count)
{
    std::vector<std::string> data;
    data.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        std::string key = "commonprefix";

        int value = i;

        for (int j = 0; j < 6; ++j)
        {
            key += static_cast<char>('a' + (value % 26));
            value /= 26;
        }

        data.push_back(key);
    }

    return data;
}

std::vector<std::string> makeUniqueData(int count)
{
    std::vector<std::string> data;
    data.reserve(count);

    for (int i = 0; i < count; ++i)
    {
        int value = i;
        std::string key(12, 'a');

        for (int j = 11; j >= 0; --j)
        {
            key[j] = static_cast<char>('a' + (value % 26));
            value /= 26;
        }

        data.push_back(key);
    }

    return data;
}

long getPeakMemory()
{
    rusage usage{};
    getrusage(RUSAGE_SELF, &usage);

#if defined(__APPLE__)
    return usage.ru_maxrss;
#else
    return usage.ru_maxrss * 1024;
#endif
}

template <typename Structure>
long measureMemory(const std::vector<std::string>& data)
{
    int pipeFd[2];

    if (pipe(pipeFd) != 0)
        std::exit(1);

    pid_t pid = fork();

    if (pid == 0)
    {
        close(pipeFd[0]);

        Structure structure;

        for (const std::string& key : data)
            structure.insert(key, 1);

        long memory = getPeakMemory();

        write(pipeFd[1], &memory, sizeof(memory));
        close(pipeFd[1]);

        std::exit(0);
    }

    close(pipeFd[1]);

    long memory = 0;
    read(pipeFd[0], &memory, sizeof(memory));
    close(pipeFd[0]);

    waitpid(pid, nullptr, 0);

    return memory;
}

template <typename Structure>
long long measureInsert(const std::vector<std::string>& data)
{
    auto start = std::chrono::steady_clock::now();

    Structure structure;

    for (const std::string& key : data)
        structure.insert(key, 1);

    auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

template <typename Structure>
long long measureSum(const std::vector<std::string>& data)
{
    Structure structure;

    for (const std::string& key : data)
        structure.insert(key, 1);

    constexpr int iterations = 1000000;

    volatile long long result = 0;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < iterations; ++i)
        result += structure.sum(data[i % data.size()].substr(0, 5));

    auto end = std::chrono::steady_clock::now();

    (void)result;

    return std::chrono::duration_cast<std::chrono::nanoseconds>(
               end - start)
        .count() / iterations;
}

void printResult(
    const char* name,
    long memory,
    long long insertTime,
    long long sumTime)
{
    std::cout << name
              << "  "
              << memory / 1024.0 / 1024.0 << " MB"
              << "  "
              << insertTime << " us"
              << "  "
              << sumTime << " ns\n";
}

void runBenchmark(
    const char* name,
    const std::vector<std::string>& data)
{
    std::cout << "\n=== " << name << " ===\n\n";

    std::cout << "                              Memory       Insert       Sum\n";
    std::cout << "----------------------------------------------------------------\n";

    printResult(
        "HashMap + PrefixSums",
        measureMemory<HashMapPrefixSums>(data),
        measureInsert<HashMapPrefixSums>(data),
        measureSum<HashMapPrefixSums>(data));

    printResult(
        "Trie",
        measureMemory<Trie>(data),
        measureInsert<Trie>(data),
        measureSum<Trie>(data));
}

int main()
{
    constexpr int count = 100000;

    auto sharedData = makeSharedPrefixData(count);
    auto uniqueData = makeUniqueData(count);

    std::cout << "Memory + Time Benchmark\n";
    std::cout << "Keys: " << count << "\n";

    runBenchmark("High Prefix Sharing", sharedData);
    runBenchmark("Low Prefix Sharing", uniqueData);

    return 0;
}