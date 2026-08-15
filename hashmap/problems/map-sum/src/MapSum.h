#pragma once

#include <string>
#include <string>
#include <unordered_map>

class MapSum_v0
{
public:
    void insert(const std::string& key, int val);
    int sum(const std::string& prefix) const;

private:
    std::unordered_map<std::string, int> _data;
};

class MapSum_v1
{
public:
    void insert(const std::string& key, int val);
    int sum(const std::string& prefix) const;

private:
    std::unordered_map<std::string, int> _data;
    std::unordered_map<std::string, int> _prefixSums;
};

class MapSum_v2
{
public:
    void insert(const std::string& key, int val);
    int sum(const std::string& prefix) const;

private:
    struct Node
    {
        Node* children[26]{};
        int value = 0;
        int prefixSum = 0;
    };

    Node* _root = new Node();
};